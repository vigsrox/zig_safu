// SPDX-License-Identifier: MIT
#include "safuRingBufferWrite_utest.h"

TEST_SUITE_FUNC_PROTOTYPES(_testSuite)

int main() {
    const struct CMUnitTest tests[] = {
        TEST_CASE(safuTestSafuRingBufferWriteErrParam),
        TEST_CASE(safuTestSafuRingBufferWriteSuccessThreaded),
        TEST_CASE(safuTestSafuRingBufferWriteSuccess),
    };

    return RUN_TEST_SUITE(tests, _testSuite);
}

static int _testSuiteSetup(void **state) {
    safuUnitTestState_t *test;

    test = calloc(1, sizeof(safuUnitTestState_t));
    assert_non_null(test);

    *state = test;

    return 0;
}

static int _testSuiteTeardown(void **state) {
    free(*state);
    *state = NULL;

    return 0;
}
