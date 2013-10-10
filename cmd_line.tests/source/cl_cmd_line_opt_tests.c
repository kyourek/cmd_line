#include <string.h>
#include "cl_cmd_line_opt_p.h"
#include "cl_cmd_line_opt_tests.h"
#include "cl_test.h"

static const char *transmit_func_one_response = NULL;
static void transmit_func_one(const char *response, void *state) {
    transmit_func_one_response = response;
}

static const char *uart_func_one(cl_cmd_line *p, void *state) {
    return CL_TEST_ERR_NONE;
}

static const char *uart_func_two(cl_cmd_line *p, void *state) {
    return "The result of uart_func_two.";
}

static cl_test_err cl_cmd_line_opt_create_creates_structure(cl_test_group *p) {
    int state;
    cl_arg_opt *arg_opt;
    cl_switch_opt* switch_opt;
    cl_cmd_line_opt *ptr;

    ptr = cl_cmd_line_opt_create(
        uart_func_one, &state, "uart_func_one", "The first function.",
            cl_arg_opt_create("arg1", "The first arg.",
            cl_arg_opt_create("arg2", "The second arg.", NULL)),
            cl_switch_opt_create("sw1", "The first switch.",
                cl_arg_opt_create("sw1arg1", "The first arg of sw1.",
                cl_arg_opt_create("sw1arg2", "The second arg of sw1.", NULL)),
            cl_switch_opt_create("sw2", "The second switch.",
                cl_arg_opt_create("sw2arg1", "The first arg of sw2.",
                cl_arg_opt_create("sw2arg2", "The second arg of sw2.", NULL)),
            NULL)),
        NULL
    );

    CL_TEST_ASSERT(NULL != ptr);
    CL_TEST_ASSERT(uart_func_one == cl_cmd_line_opt_get_func(ptr));
    CL_TEST_ASSERT(&state == cl_cmd_line_opt_get_state(ptr));
    CL_TEST_ASSERT(CL_TRUE == cl_opt_is_required((cl_opt*)ptr));

    arg_opt = cl_arg_opt_owner_get_arg_opt((cl_arg_opt_owner*)ptr);
    CL_TEST_ASSERT(cl_opt_get_name((cl_opt*)arg_opt));
    CL_TEST_ASSERT(cl_opt_get_desc((cl_opt*)arg_opt));

    arg_opt = cl_arg_opt_get_next(arg_opt);
    CL_TEST_ASSERT(cl_opt_get_name((cl_opt*)arg_opt));
    CL_TEST_ASSERT(cl_opt_get_desc((cl_opt*)arg_opt));

    CL_TEST_ASSERT(NULL == cl_arg_opt_get_next(arg_opt));

    switch_opt = cl_cmd_line_opt_get_switch_opt(ptr);
    CL_TEST_ASSERT(cl_opt_get_name((cl_opt*)switch_opt));
    CL_TEST_ASSERT(cl_opt_get_desc((cl_opt*)switch_opt));

    arg_opt = cl_arg_opt_owner_get_arg_opt((cl_arg_opt_owner*)switch_opt);
    CL_TEST_ASSERT(cl_opt_get_name((cl_opt*)arg_opt));
    CL_TEST_ASSERT(cl_opt_get_desc((cl_opt*)arg_opt));

    // TODO: Finish making assertions here.

    cl_cmd_line_opt_destroy_chain(ptr);

    return CL_TEST_ERR_NONE;
}

static cl_test_err cl_cmd_line_opt_process_calls_func(cl_test_group *p) {
    cl_cmd_line *cmd;
    cl_cmd_line_opt *cmd_opt;

    cmd = cl_cmd_line_get_instance();
    cmd_opt = cl_cmd_line_opt_create(uart_func_two, NULL, "uart_func", "The UART function.", NULL, NULL, NULL);
    cl_cmd_line_set_cmd_tok(cmd, "uart_func\0\n");
     
    CL_TEST_ASSERT(cl_cmd_line_opt_process(cmd_opt, cmd));

    cl_cmd_line_opt_destroy_chain(cmd_opt);

    return CL_TEST_ERR_NONE;
}

static cl_test_err cl_cmd_line_opt_create_creates_different_instances(cl_test_group *p) {
    cl_cmd_line_opt *c1, *c2, *c3;

    c1 = cl_cmd_line_opt_create(NULL, NULL, "c1", "c1", NULL, NULL, NULL);
    c2 = cl_cmd_line_opt_create(NULL, NULL, "c2", "c2", NULL, NULL, NULL);
    c3 = cl_cmd_line_opt_create(NULL, NULL, "c3", "c3", NULL, NULL, NULL);

    CL_TEST_ASSERT(c1 != c2);
    CL_TEST_ASSERT(c2 != c3);

    cl_cmd_line_opt_destroy(c1);
    cl_cmd_line_opt_destroy(c2);
    cl_cmd_line_opt_destroy(c3);

    return CL_TEST_ERR_NONE;
}

static cl_test_err cl_cmd_line_opt_destroy_releases_instance(cl_test_group *p) {
    cl_cmd_line_opt *c1, *c2, *c3, *c4;

    c1 = cl_cmd_line_opt_create(NULL, NULL, "c1", "c1", NULL, NULL, NULL);
    c2 = cl_cmd_line_opt_create(NULL, NULL, "c2", "c2", NULL, NULL, NULL);
    c3 = cl_cmd_line_opt_create(NULL, NULL, "c3", "c3", NULL, NULL, NULL);

    cl_cmd_line_opt_destroy(c3);

    c4 = cl_cmd_line_opt_create(NULL, NULL, "c4", "c4", NULL, NULL, NULL);

    CL_TEST_ASSERT(c4 == c3);
    
    cl_cmd_line_opt_destroy(c1);
    cl_cmd_line_opt_destroy(c2);
    cl_cmd_line_opt_destroy(c4);

    return CL_TEST_ERR_NONE;
}

static cl_test_err cl_cmd_line_opt_destroy_chain_releases_all_instances(cl_test_group *p) {
    cl_arg_opt *a1, *a2, *a3, *a4, *a4_2;
    cl_switch_opt *s1, *s2, *s3, *s3_2;
    cl_cmd_line_opt *c1, *c2, *c3, *c3_2;

    a4 = cl_arg_opt_create("a4", "a4", NULL);
    a3 = cl_arg_opt_create("a3", "a3", a4);
    s3 = cl_switch_opt_create("-s3", "-s3", a3, NULL);
    c3 = cl_cmd_line_opt_create(NULL, NULL, "c3", "c3", NULL, s3, NULL);

    a2 = cl_arg_opt_create("a2", "a2", NULL);
    s2 = cl_switch_opt_create("-s2", "-s2", a2, NULL);
    s1 = cl_switch_opt_create("-s1", "-s1", NULL, s2);
    c2 = cl_cmd_line_opt_create(NULL, NULL, "c2", "c2", NULL, s1, c3);

    a1 = cl_arg_opt_create("a1", "a1", NULL);
    c1 = cl_cmd_line_opt_create(NULL, NULL, "c1", "c1", a1, NULL, c2);

    cl_cmd_line_opt_destroy_chain(c1);

    a4_2 = cl_arg_opt_create("a4_2", "a4_2", NULL);
    CL_TEST_ASSERT(a4_2 == a4);

    s3_2 = cl_switch_opt_create("-s3_2", "-s3_2", NULL, NULL);
    CL_TEST_ASSERT(s3_2 == s3);

    c3_2 = cl_cmd_line_opt_create(NULL, NULL, "c3_2", "c3_2", NULL, NULL, NULL);
    CL_TEST_ASSERT(c3_2 == c3);

    cl_arg_opt_destroy(a4_2);
    cl_switch_opt_destroy(s3_2);
    cl_cmd_line_opt_destroy(c3_2);

    return CL_TEST_ERR_NONE;
}

static cl_test_err cl_cmd_line_opt_send_usage_responds_with_usage_string(cl_test_group *p) {
    const char *expected;
    cl_cmd_line *cmd = cl_cmd_line_get_instance();
    cl_cmd_line_transmit_func *prev_transmit_func = cl_cmd_line_get_transmit(cmd);

    cl_cmd_line_opt *cmd_opt = 
        cl_cmd_line_opt_create(NULL, NULL, "dothis", NULL,
            cl_arg_opt_create("firstarg", NULL,
            cl_arg_opt_create_required("secondarg", NULL,
            cl_arg_opt_create_numeric(NULL, 0, 5,
            NULL))),
            cl_switch_opt_create("-s1", NULL, 
                cl_arg_opt_create_required_numeric(NULL, 0, 10,
                NULL),
            cl_switch_opt_create("-s2", NULL,
                NULL,
            cl_switch_opt_create_required("-sthree", NULL,
                cl_arg_opt_create("s3arg", NULL,
                NULL),
            NULL))),
        cl_cmd_line_opt_create(NULL, NULL, "boringcmd", NULL, NULL, NULL, NULL));

    cl_cmd_line_set_transmit(cmd, transmit_func_one);
    
    cl_cmd_line_opt_send_usage(cmd_opt, cmd);
    expected = "dothis [firstarg] secondarg [<number>] [-s1] <number> [-s2] -sthree [s3arg]";
    CL_TEST_ASSERT(0 == strcmp(expected, transmit_func_one_response));

    cl_cmd_line_opt_send_usage(cl_cmd_line_opt_get_next(cmd_opt), cmd);
    expected = "boringcmd";
    CL_TEST_ASSERT(0 == strcmp(expected, transmit_func_one_response));

    cl_cmd_line_opt_destroy_chain(cmd_opt);
    cl_cmd_line_set_transmit(cmd, prev_transmit_func);
    return CL_TEST_ERR_NONE;
}

static cl_test_err cl_cmd_line_opt_format_validation_err_catches_required_arg(cl_test_group *p) {
    const char *err;
    cl_cmd_line *cmd = cl_cmd_line_get_instance();
    cl_cmd_line_opt *opt = cl_cmd_line_opt_create(NULL, NULL, "opt", NULL, cl_arg_opt_create_required("a", NULL, NULL), NULL, NULL);

    cl_cmd_line_set_cmd_tok(cmd, "opt\0\n");
    err = cl_cmd_line_opt_format_validation_err(opt, cmd);
    CL_TEST_ASSERT(NULL != err);

    cl_cmd_line_set_cmd_tok(cmd, "opt\0arg\0\n");
    err = cl_cmd_line_opt_format_validation_err(opt, cmd);
    CL_TEST_ASSERT(NULL == err);

    cl_cmd_line_opt_destroy_chain(opt);
    return CL_TEST_ERR_NONE;
}

static cl_test_err cl_cmd_line_opt_format_validation_err_catches_required_switch(cl_test_group *p) {
    const char *err;
    cl_cmd_line *cmd = cl_cmd_line_get_instance();
    cl_cmd_line_opt *opt = cl_cmd_line_opt_create(NULL, NULL, "opt", NULL, NULL, cl_switch_opt_create_required("-s", NULL, NULL, NULL), NULL);

    cl_cmd_line_set_cmd_tok(cmd, "opt\0-z\0\n");
    err = cl_cmd_line_opt_format_validation_err(opt, cmd);
    CL_TEST_ASSERT(NULL != err);

    cl_cmd_line_set_cmd_tok(cmd, "opt\0-s\0\n");
    err = cl_cmd_line_opt_format_validation_err(opt, cmd);
    CL_TEST_ASSERT(NULL == err);

    cl_cmd_line_opt_destroy_chain(opt);
    return CL_TEST_ERR_NONE;
}

cl_test_group *cl_cmd_line_opt_tests_get_group(void) {
    static cl_test_group group;
    static cl_test_group_test_func *tests[] = {
        cl_cmd_line_opt_create_creates_structure,
        cl_cmd_line_opt_process_calls_func,
        cl_cmd_line_opt_create_creates_different_instances,
        cl_cmd_line_opt_destroy_releases_instance,
        cl_cmd_line_opt_destroy_chain_releases_all_instances,
        cl_cmd_line_opt_send_usage_responds_with_usage_string,
        cl_cmd_line_opt_format_validation_err_catches_required_arg,
        cl_cmd_line_opt_format_validation_err_catches_required_switch,
        NULL
    };

    return cl_test_group_init(&group, NULL, NULL, NULL, NULL, tests);
}
