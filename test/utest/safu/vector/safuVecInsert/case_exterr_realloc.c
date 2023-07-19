// SPDX-License-Identifier: MIT
#include "cmocka_mocks/mock_libc.h"
#include "safuVecInsert_utest.h"

void safuTestSafuVecInsertExterrRemalloc(UNUSED void **state) {
    safuVec_t vec = {0};
    safuTdata_t tdata[2] = {0};
    safuTdata_t expectedTdata[] = {
        {420, "420"},
        {421, "421"},
    };

    MOCK_FUNC_AFTER_CALL(malloc, 0);
    expect_value(__wrap_malloc, size, sizeof(safuTdata_t));
    will_return(__wrap_malloc, tdata);

    int retval = safuVecCreate(&vec, 1, sizeof(safuTdata_t));
    assert_int_equal(retval, 0);

    retval = safuVecInsert(&vec, 0, &expectedTdata[0]);
    assert_int_equal(retval, 0);

    MOCK_FUNC_AFTER_CALL(realloc, 0);
    expect_value(__wrap_realloc, ptr, tdata);
    expect_value(__wrap_realloc, newSize, sizeof(safuTdata_t) * 2);
    will_return(__wrap_realloc, NULL);

    retval = safuVecInsert(&vec, 0, &expectedTdata[1]);
    assert_int_equal(retval, -1);
    assert_int_equal(vec.elementSize, sizeof(safuTdata_t));
    assert_int_equal(vec.memorySize, sizeof(safuTdata_t));
    assert_int_equal(vec.elementCount, 1);
    assert_ptr_equal(vec.data, &tdata);
}
