#include <stdlib.h>
#include <stdarg.h>
#include "cl_arg_opt.h"
#include "cl_arg_opt_p.h"
#include "cl_arg_opt_owner.h"
#include "cl_arg_opt_owner_p.h"
#include "cl_cmd_line.h"
#include "cl_common.h"
#include "cl_opt.h"
#include "cl_opt_p.h"
#include "cl_tok.h"

cl_arg_opt *cl_arg_opt_owner_get_arg_opt(cl_arg_opt_owner *p) {
    if (NULL == p) return NULL;
    return p->arg_opt;
}

cl_arg_opt_owner *cl_arg_opt_owner_init(cl_arg_opt_owner *p, const char *name, const char *desc, CL_BOOL is_required, cl_arg_opt *arg_opt) {
    if (NULL == p) return NULL;
    if (NULL == cl_opt_init((cl_opt*)p, name, desc, is_required)) return NULL;
    p->arg_opt = arg_opt;
    return p;
}

const char *cl_arg_opt_owner_format_validation_err(cl_arg_opt_owner *p, cl_cmd_line *cmd, cl_arg_tok *arg_tok, const char *switch_name) {
    const char *validation, *prefix = switch_name == NULL ? "Invalid argument: " : "Invalid switch argument: ";

    cl_arg_opt *arg_opt = cl_arg_opt_owner_get_arg_opt(p);

    if (NULL == arg_opt) {
        if (NULL != arg_tok) {
            if (NULL == switch_name) {
                return cl_cmd_line_format_response(cmd, "%sno argument options exist for command \"%s\".", prefix, cl_tok_get_value(cl_cmd_line_get_cmd_tok(cmd)));
            }
            return cl_cmd_line_format_response(cmd, "%sno argument options exist for switch \"%s\".", prefix, switch_name);
        }
        return CL_FALSE;
    }

    while (NULL != arg_opt) {

        validation = cl_arg_opt_format_validation_err(arg_opt, cmd, arg_tok, switch_name);
        if (NULL != validation) return validation;

        arg_opt = cl_arg_opt_get_next(arg_opt);
        arg_tok = cl_arg_tok_get_next(arg_tok);
    }

    if (NULL != arg_tok) {
        if (NULL == switch_name) {
            return cl_cmd_line_format_response(cmd, "%sno option exists for argument \"%s\".", prefix, cl_tok_get_value(arg_tok));
        }
        return cl_cmd_line_format_response(cmd, "%sno option exists for \"%s\" argument \"%s\".", prefix, switch_name, cl_tok_get_value(arg_tok));
    }

    return CL_FALSE;
}
