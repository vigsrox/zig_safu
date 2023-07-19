// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_jsonc.h"
#include "safuJsonGetUint32_utest.h"

SETUP(safuTestSafuJsonGetUint32NumberOutOfBoundsObject)
TEARDOWN(safuTestSafuJsonGetUint32NumberOutOfBoundsObject)

static void _testCase(struct json_object *jobj, char *key, uint64_t val) {
    PARAM("key = \"%s\"", key);
    PARAM("val = %lu", val);
    uint32_t result;

    expect_value(safuJsonGetUint64, jobj, jobj);
    expect_value(safuJsonGetUint64, name, key);
    expect_value(safuJsonGetUint64, idx, 0);
    will_return(safuJsonGetUint64, val);
    will_return(safuJsonGetUint64, 0);

    int retval = safuJsonGetUint32(jobj, key, 0, &result);

    assert_int_equal(retval, 0);
    assert_int_equal(result, UINT32_MAX);
}

void safuTestSafuJsonGetUint32NumberOutOfBoundsObject(void **state) {
    TEST("safuJsonGetUint32");
    SHOULD("%s", "successfully get an uint32 from a json object");

    *(struct json_object **)state = json_object_new_object();
    struct json_object *jobj = *(struct json_object **)state;

    struct {
        char *key;
        uint64_t val;
    } testRows[] = {{"Max", (uint64_t)UINT32_MAX + 1}, {"way to big", UINT64_MAX}};

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        safuJsonAddNewUint64(jobj, testRows[i].key, testRows[i].val);
    }

    for (size_t i = 0; i < ARRAY_SIZE(testRows); i++) {
        _testCase(jobj, testRows[i].key, testRows[i].val);
    }
}
