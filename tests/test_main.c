#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "main.c"  // Include the header or the source file containing your code

// Test addition
void test_add() {
    CU_ASSERT_EQUAL(add(3, 2), 5); // 3 + 2 = 5
    CU_ASSERT_EQUAL(add(-1, 1), 0); // -1 + 1 = 0
}

// Test subtraction
void test_subtract() {
    CU_ASSERT_EQUAL(subtract(5, 3), 2); // 5 - 3 = 2
    CU_ASSERT_EQUAL(subtract(3, 5), -2); // 3 - 5 = -2
}

// Test multiplication
void test_multiply() {
    CU_ASSERT_EQUAL(multiply(3, 2), 6); // 3 * 2 = 6
    CU_ASSERT_EQUAL(multiply(-1, 5), -5); // -1 * 5 = -5
}

// Test division
void test_divide() {
    CU_ASSERT_EQUAL(divide(6, 2), 3); // 6 / 2 = 3
    CU_ASSERT_EQUAL(divide(10, 0), -1); // Error case, division by 0
}

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add a suite to the registry
    CU_pSuite pSuite = CU_add_suite("Calculator Test Suite", 0, 0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add tests to the suite
    if (NULL == CU_add_test(pSuite, "Test Add", test_add) ||
        NULL == CU_add_test(pSuite, "Test Subtract", test_subtract) ||
        NULL == CU_add_test(pSuite, "Test Multiply", test_multiply) ||
        NULL == CU_add_test(pSuite, "Test Divide", test_divide)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests
    CU_basic_set_mode(CU_BASIC_VERBOSE);
    CU_basic_run_tests();

    // Clean up and return
    CU_cleanup_registry();
    return CU_get_error();
}
