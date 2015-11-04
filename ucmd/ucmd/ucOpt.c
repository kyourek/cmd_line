#include "ucmd_internal.h"

const char *ucOpt_get_name(ucOpt *p) {
    assert(p);
    return p->name;
}

const char *ucOpt_get_desc(ucOpt *p) {
    assert(p);
    return p->desc;
}

ucBool ucOpt_is_required(ucOpt *p) {
    assert(p);
    return p->is_required;
}

void ucOpt_send_help(ucOpt *p, ucCmdLine *cmd, const char *prefix) {
    static const char *required_format = "%s%s: %s";
    static const char *optional_format = "%s[%s]: %s";
    const char *format = ucOpt_is_required(p) 
        ? required_format 
        : optional_format;
    ucCmdLine_respond(cmd, ucCmdLine_format_response(
        cmd,
        format,
        prefix,
        ucOpt_get_name(p),
        ucOpt_get_desc(p)
    ));
}

ucOpt *ucOpt_init(ucOpt *p, const char *name, const char *desc, ucBool is_required) {
    if (NULL == p) return NULL;
    p->name = name;
    p->desc = desc;
    p->is_required = is_required;
    return p;
}
