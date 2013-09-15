#include <stdlib.h>
#include <string.h>
#include "cl_arg_opt.h"
#include "cl_arg_opt_p.h"
#include "cl_arg_opt_owner.h"
#include "cl_arg_opt_owner_p.h"
#include "cl_cmd_line.h"
#include "cl_memory_manager_p.h"
#include "cl_opt.h"
#include "cl_opt_p.h"
#include "cl_switch_opt.h"
#include "cl_switch_opt_p.h"

CL_MEMORY_MANAGER_INIT(cl_switch_opt, CL_CMD_COUNT_MAX * CL_SWITCH_COUNT_MAX);

static cl_switch_opt *create_switch_opt(void) {
    return cl_memory_manager_create();
}

cl_arg_opt *cl_switch_opt_get_arg_opt(cl_switch_opt *p) {
    return cl_arg_opt_owner_get_arg_opt((cl_arg_opt_owner*)p);
}

cl_switch_opt *cl_switch_opt_get_next(cl_switch_opt *p) {
    if (NULL == p) return NULL;
    return p->next;
}

cl_switch_opt *cl_switch_opt_find(cl_switch_opt *p, const char *name) {
    while (NULL != p) {
        if (0 == strcmp(cl_opt_get_name((cl_opt*)p), name)) {
            return p;
        }
        p = cl_switch_opt_get_next(p);
    }
    return NULL;
}

cl_switch_opt *cl_switch_opt_init(cl_switch_opt *p, const char *name, const char *desc, CL_BOOL is_required, cl_arg_opt *arg_opt, cl_switch_opt *next) {
    if (NULL == p) return NULL;
    if (NULL == cl_arg_opt_owner_init((cl_arg_opt_owner*)p, name, desc, is_required, arg_opt)) return NULL;

    p->next = next;
    return p;
}

cl_switch_opt *cl_switch_opt_create(const char *name, const char *desc, cl_arg_opt *arg_opt, cl_switch_opt *next) {
    return cl_switch_opt_init(create_switch_opt(), name, desc, CL_FALSE, arg_opt, next);
}

cl_switch_opt *cl_switch_opt_create_required(const char *name, const char *desc, cl_arg_opt *arg_opt, cl_switch_opt *next) {
    return cl_switch_opt_init(create_switch_opt(), name, desc, CL_TRUE, arg_opt, next);
}

void cl_switch_opt_destroy(cl_switch_opt *p) {
    cl_memory_manager_destroy(p);
}

void cl_switch_opt_destroy_chain(cl_switch_opt *p) {
    cl_switch_opt *next = p;
    while (NULL != next) {
        p = next;
        next = cl_switch_opt_get_next(p);
        cl_arg_opt_destroy_chain(cl_switch_opt_get_arg_opt(p));
        cl_switch_opt_destroy(p);
    }
}

const char *cl_switch_opt_format_validation_err(cl_switch_opt *p, cl_cmd_line *cmd, cl_switch_tok *switch_tok) {

    /* check if the switch option is required */
    if (cl_opt_is_required((cl_opt*)p)) {

        /* check if the switch token is missing */
        if (NULL == switch_tok) {

            /* the switch is required, but it is not
               present, so send the error */
            return cl_cmd_line_format_response(cmd, "%sthe switch \"%s\" is required.", cl_opt_validation_err_invalid_switch_prefix, cl_opt_get_name((cl_opt*)p));
        }
    }

    /* return the result of the argument validation */
    return cl_arg_opt_owner_format_validation_err(
        (cl_arg_opt_owner*)p, 
        cmd, 
        cl_switch_tok_get_arg(switch_tok), 
        cl_opt_get_name((cl_opt*)p)
    );
}
