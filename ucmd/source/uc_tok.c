#include <string.h>
#include "uc_tok_p.h"

#ifndef UC_TOK_LENGTH_MAX
#define UC_TOK_LENGTH_MAX       200
#endif

const char uc_tok_separator = '\0';
const char uc_cmd_terminator = '\n';

static uc_bool is_char_digit(char c) {
    /* The native isdigit function in ctype.h was giving some weird behavior in the uVision simulator */
    static char *digits = "0123456789";
    char *d;
    for (d = digits; *d; d++) {
        if (*d == c) {
            return UC_TRUE;
        }
    }
    return UC_FALSE;
}

int uc_tok_get_length(uc_tok *p) {
    int length;
    if (NULL == p) return 0;

    for (length = 0; *p != uc_tok_separator; length++, p++);

    return length;
}

const char *uc_tok_get_value(uc_tok *p) {
    if (NULL == p) return NULL;
    return (const char*)p;
}

uc_bool uc_tok_equals(uc_tok *p, const char *value) {
    int i, len;

    /* check if these pointers are the same */
    if (value == p) return UC_TRUE;

    /* make sure neither arg is null */
    if (NULL == p) return UC_FALSE;
    if (NULL == value) return UC_FALSE;

    /* check if the string lengths are the same */
    len = uc_tok_get_length(p);
    if (strlen(value) != len) return UC_FALSE;

    /* check for character equality */
    for (i = 0; i < len; i++) {
        if (p[i] != value[i]) {
            return UC_FALSE;
        }
    }

    /* if we got here, then the strings are equal */
    return UC_TRUE;
}

uc_bool uc_tok_is_numeric(uc_tok *p) {
    int i, len;
    uc_bool dec_found;

    /* check if p is NULL */
    if (NULL == p) return UC_FALSE;
    
    /* get the length of the string */
    len = uc_tok_get_length(p);
    
    /* numbers need to have at least 1 character */
    if (len < 1) return UC_FALSE;
    
    /* we are allowed to start with a '-' or '.' for negative numbers and decimals */
    if ((p[0] == '-') || (p[0] == '.')) {
        
        /* but we need more than 1 char if we do */
        if (len < 2) return UC_FALSE;
    }

    // initialize vars
    dec_found = UC_FALSE;

    /* loop through the chars */
    for (i = 0; i < len; i++) {
        
        switch(p[i]) {
        
            /* allow a dash only at the beginning */
            case '-':
                if (i != 0) return UC_FALSE;
                break;
                
            /* allow only 1 dot */
            case '.':
                if (dec_found) return UC_FALSE;
                dec_found = UC_TRUE;
                break;
                
            /* everything else has to be a number */
            default:
                if (is_char_digit(p[i]) == UC_FALSE) return UC_FALSE;
                break;
        }
    }
    
    /* if we got here, it's a number */
    return UC_TRUE;
}

uc_bool uc_tok_is_switch(uc_tok* p) {
    int len = 0;

    /* check for a null pointer */
    if (NULL == p) return UC_FALSE;
    
    /* get the length so we can use it */
    len = uc_tok_get_length(p);
    
    /* check for at least 2 characters (one '-' and at least another char) */
    if (len < 2) return UC_FALSE;
    
    /* check if it starts with a '-' */
    if (p[0] != '-') return UC_FALSE;
    
    /* check if this is a numeric argument (negative numbers aren't switches) */
    if (uc_tok_is_numeric(p)) return UC_FALSE;

    /* ok, it's a switch */
    return UC_TRUE;
}

uc_tok *uc_tok_get_next(uc_tok *p) {
    int i;
    if (NULL == p) return NULL;

    /* loop until we've hit the max length */
    i = 0;
    while (UC_TOK_LENGTH_MAX > ++i) {

        /* check if the previous character was a separator */
        if (uc_tok_separator == p[i - 1]) {

            /* check if this character is the terminator */
            if (uc_cmd_terminator == p[i]) {

                /* it is, so no more tokens exist */
                return NULL;
            }

            /* make sure this character isn't another separator */
            if (uc_tok_separator == p[i]) {
                continue;
            }

            /* the previous character was a separator,
               and this character is NOT the terminator,
               OR another separator, so this character is 
               the start of a new token */
            return (uc_tok*)&p[i];
        }
    }

    /* the max length was exceeded,
       which probably means something
       went wrong. */
    return NULL;
}

int uc_tok_count(uc_tok *p) {
    int count;

    /* make sure we have a pointer */
    if (NULL == p) return 0;

    /* if the first character is the terminator, then we have no tokens */
    if (p[0] == uc_cmd_terminator) return 0;

    /* start off the count according to whether or not
       we're starting at a token */
    count = uc_tok_separator == p[0] ? -1 : 0;

    /* count the tokens in the chain */
    while (NULL != p) {
        count++;
        p = uc_tok_get_next(p);
    }
    return count;
}