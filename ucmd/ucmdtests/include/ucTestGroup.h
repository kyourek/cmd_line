#ifndef UC_TEST_GROUP_H
#define UC_TEST_GROUP_H

#include "ucTestState.h"
#include "ucTestErr.h"

/*
 * Summary:
 *   Structure for holding information about a group
 *   of unit tests.
 */
typedef struct ucTestGroup ucTestGroup;

/*
 * Summary:
 *   The type of function that is used as a callback at certain times
 *   while running a group of unit tests.
 * Parameters:
 *   p: A pointer to the running test group.
 * Returns:
 *   An error number to cancel pending tests, or no error to continue.
 */
typedef ucTestErr (ucTestGroup_callback_func)(ucTestGroup *p);

/*
 * Summary:
 *   The type of function that runs a unit test.
 * Parameters:
 *   p: A pointer to the running test group.
 * Returns:
 *   The error number resulting from the test, or no
 *   error if an error did not occur.
 */
typedef ucTestErr (ucTestGroup_test_func)(ucTestGroup *p);

/*
 * Summary:
 *   Performs actions that should be performed before any tests are
 *   run in a group.
 * Parameters:
 *   p: A pointer to the running test group.
 * Returns:
 *   An error number to cancel pending tests, or no error to continue.
 */
UC_EXPORTED ucTestErr ucTestGroup_before_all_tests(ucTestGroup *p);

/*
 * Summary:
 *   Performs actions that should be performed after all tests have
 *   been run in a group.
 * Parameters:
 *   p: A pointer to the running test group.
 * Returns:
 *   An error number to cancel pending tests, or no error to continue.
 */
UC_EXPORTED ucTestErr ucTestGroup_after_all_tests(ucTestGroup *p);

/*
 * Summary:
 *   Performs actions that should be performed before each test
 *   is run in a group.
 * Parameters:
 *   p: A pointer to the running test group.
 * Returns:
 *   An error number to cancel pending tests, or no error to continue.
 */
UC_EXPORTED ucTestErr ucTestGroup_before_each_test(ucTestGroup *p);

/*
 * Summary:
 *   Performs actions that should be performed after each test
 *   is run in a group.
 * Parameters:
 *   p: A pointer to the running test group.
 * Returns:
 *   An error number to cancel pending tests, or no error to continue.
 */
UC_EXPORTED ucTestErr ucTestGroup_after_each_test(ucTestGroup *p);

/*
 * Summary:
 *   Gets a NULL-terminated list of tests in the group.
 * Parameters:
 *   p: A pointer to the running test group.
 * Returns:
 *   The lists of tests to run for the group.
 */
UC_EXPORTED ucTestGroup_test_func **ucTestGroup_get_tests(ucTestGroup *p);

/*
 * Summary:
 *   Initializes a test group structure.
 * Parameters:
 *   p: A pointer to the test group to be initialized.
 *   before_all_tests: A function that is run before any tests in the group.
 *   after_all_tests: A function that is run after all tests in the group.
 *   before_each_test: A function that is run before each test in the group.
 *   after_each_test: A function that is run after each test in the group.
 *   tests: A NULL-terminated list of tests in the group.
 * Returns:
 *   A pointer to the initialized test group.
 */
UC_EXPORTED ucTestGroup *ucTestGroup_init(
    ucTestGroup *p, 
    ucTestGroup_callback_func *before_all_tests, 
    ucTestGroup_callback_func *after_all_tests, 
    ucTestGroup_callback_func *before_each_test, 
    ucTestGroup_callback_func *after_each_test,
    ucTestGroup_test_func **tests
);

/*
 * Summary:
 *   Runs the tests in the group.
 * Parameters:
 *   p: A pointer to the test group.
 *   state: The object that maintains test state.
 * Returns:
 *   The error number of the failed test, or no error if all
 *   tests passed.
 */
UC_EXPORTED ucTestErr ucTestGroup_run(ucTestGroup *p, ucTestState *state);

/*
 * Summary:
 *   Structure for holding information about a group
 *   of unit tests.
 */
struct ucTestGroup {
    ucTestGroup_callback_func *before_all_tests;
    ucTestGroup_callback_func *after_all_tests;
    ucTestGroup_callback_func *before_each_test;
    ucTestGroup_callback_func *after_each_test;
    ucTestGroup_test_func **tests;
};

#endif
