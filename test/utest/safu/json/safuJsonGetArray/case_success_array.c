// SPDX-License-Identifier: MIT
#include "safuJsonGetArray_utest.h"

SETUP(safuTestSafuJsonGetArraySuccessArray)
TEARDOWN(safuTestSafuJsonGetArraySuccessArray)

static void _testCase(const struct json_object *jobj, size_t idx, const struct json_object *array, size_t len) {
    size_t resultLen;

    struct json_object *resultArray = safuJsonGetArray(jobj, NULL, idx, &resultLen);

    assert_non_null(resultArray);
    assert_ptr_equal(resultArray, array);
    assert_int_equal(resultLen, len);
    assert_int_equal(resultLen, json_object_array_length(resultArray));
}

void safuTestSafuJsonGetArraySuccessArray(void **state) {
    TEST("safuJsonGetArray");
    SHOULD("%s", "successfully get a json array from a json array");

    *(struct json_object **)state = json_object_new_array();
    struct json_object *jobj = *(struct json_object **)state;

    struct {
        size_t len;
        struct json_object *array;
    } testRows[] = {{0, NULL}, {1, NULL}, {17, NULL}, {50, NULL}};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        testRows[i].array = json_object_new_array();
        for (size_t len = 0; len < testRows[i].len; len++) {
            safuJsonAddNewObject(testRows[i].array, NULL);
        }
        safuJsonAddObject(jobj, NULL, testRows[i].array);
    }

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jobj, i, testRows[i].array, testRows[i].len);
    }
}
