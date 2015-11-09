/********************************************************************************
*  Copyright (c) 2013-2015 Ken Yourek
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*  THE SOFTWARE.
*******************************************************************************/

#ifndef     UCMD_INTERNAL_H
#define     UCMD_INTERNAL_H

#include    <assert.h>
#include    <string.h>
#include    "ucmd.h"

typedef     struct ucArgOptOwner                ucArgOptOwner;
typedef     const char                          ucArgTok;
typedef     const char                          ucArgTokOwner;
typedef     struct ucCmdParser                  ucCmdParser;
typedef     const char                          ucCmdTok;
typedef     const char                          ucSwitchTok;

            struct                              ucCmdParser {
            char                                placeholder; };

uc_EXPORTED ucOpt*                              ucOpt_init(ucOpt*, const char *name, const char *desc, ucBool is_required);
uc_EXPORTED void                                ucOpt_send_help(ucOpt*, ucCmd *cmd, const char *prefix);
            struct                              ucOpt {
            const char*                         name;
            const char*                         desc;
            ucBool                              is_required; };

uc_EXPORTED const char*                         ucArgOpt_format_validation_err(ucArgOpt*, ucCmd *cmd, ucArgTok *arg_tok, const char *switch_name);
uc_EXPORTED ucArgOpt*                           ucArgOpt_init(ucArgOpt*, const char *name, const char *desc, ucBool is_required, int min_tok_count, int max_tok_count, ucBool is_boolean, ucBool is_numeric, ucBool is_integer, double numeric_min, double numeric_max, ucArgOpt *next);
            struct                              ucArgOpt {
            ucOpt                               base;
            ucBool                              is_boolean;
            ucBool                              is_numeric;
            ucBool                              is_integer;
            double                              numeric_min;
            double                              numeric_max;
            int                                 max_tok_count;
            int                                 min_tok_count;
            ucArgOpt*                           next; };            

uc_EXPORTED const char*                         ucArgOptOwner_format_validation_err(ucArgOptOwner*, ucCmd *cmd, ucArgTok *arg_tok, const char *switch_name);
uc_EXPORTED ucArgOpt*                           ucArgOptOwner_get_arg_opt(ucArgOptOwner*);
uc_EXPORTED ucArgOptOwner*                      ucArgOptOwner_init(ucArgOptOwner*, const char *name, const char *desc, ucBool is_required, ucArgOpt *arg_opt);
            struct                              ucArgOptOwner {
            ucOpt                               base;
            ucArgOpt*                           arg_opt; };

uc_EXPORTED ucArgTok*                           ucArgTok_get_next(ucArgTok*);
uc_EXPORTED ucArgTok*                           ucArgTok_get_index(ucArgTok*, int index);
uc_EXPORTED int                                 ucArgTok_count(ucArgTok*);
uc_EXPORTED ucArgTok*                           ucArgTok_find(ucArgTok*, const char *arg_value);
uc_EXPORTED ucBool                              ucArgTok_contains(ucArgTok*, const char *arg_value);

uc_EXPORTED ucArgTok*                           ucArgTokOwner_get_arg(ucArgTokOwner*);

uc_EXPORTED ucCmdParser*                        ucCmdParser_create(void);
uc_EXPORTED void                                ucCmdParser_destroy(ucCmdParser *p);
uc_EXPORTED ucCmdTok*                           ucCmdParser_parse(ucCmdParser*, char *cmd);

uc_EXPORTED ucArgTok*                           ucCmdTok_get_arg(ucCmdTok*);
uc_EXPORTED ucSwitchTok*                        ucCmdTok_get_switch(ucCmdTok*);

uc_EXPORTED const char*                         ucSwitchOpt_format_validation_err(ucSwitchOpt*, ucCmd *cmd, ucSwitchTok *switch_tok);
uc_EXPORTED ucSwitchOpt*                        ucSwitchOpt_init(ucSwitchOpt*, const char *name, const char *desc, ucBool is_required, ucArgOpt *arg_opt, ucSwitchOpt *next);
            struct                              ucSwitchOpt {
            ucArgOptOwner                       base;
            ucSwitchOpt*                        next; };

uc_EXPORTED ucSwitchTok*                        ucSwitchTok_get_index(ucSwitchTok*, int index);
uc_EXPORTED ucSwitchTok*                        ucSwitchTok_get_next(ucSwitchTok*);
uc_EXPORTED int                                 ucSwitchTok_count(ucSwitchTok*);
uc_EXPORTED ucSwitchTok*                        ucSwitchTok_find(ucSwitchTok*, const char *switch_name);
uc_EXPORTED ucBool                              ucSwitchTok_contains(ucSwitchTok*, const char *switch_name);
uc_EXPORTED ucArgTok*                           ucSwitchTok_get_arg(ucSwitchTok*);

uc_EXPORTED void                                ucCmd_acknowledge_command(ucCmd*);
uc_EXPORTED ucBool                              ucCmd_handle_invalid_command(ucCmd*, const char *invalid_command);
uc_EXPORTED ucCmd*                              ucCmd_init(ucCmd*);
uc_EXPORTED void                                ucCmd_terminate_response(ucCmd*);
            struct                              ucCmd {
            ucCmdTok*                           command;
            ucCmd_TransmitFunc*                 transmit;
            ucCmd_IsCanceledFunc*               is_canceled;
            ucCmd_HandleInvalidCommandFunc*     handle_invalid_command;
            void*                               transmit_state;
            void*                               is_canceled_state;
            void*                               handle_invalid_command_state;
            const char*                         response_terminator;
            const char*                         command_acknowledgment;
            char                                response[ucCmd_RESPONSE_SIZE];
	        char                                response_buffer[ucCmd_RESPONSE_SIZE];
            ucBool                              is_quiet; };

uc_EXPORTED const char*                         ucCmdOpt_format_validation_err(ucCmdOpt*, ucCmd *cmd);
uc_EXPORTED ucCmdOpt*                           ucCmdOpt_init(ucCmdOpt*, ucCmdOpt_WorkFunc *func, void* state, const char *name, const char *desc, ucArgOpt* arg_opt, ucSwitchOpt *switch_opt, ucCmdOpt *next);
uc_EXPORTED const char*                         ucCmdOpt_process(ucCmdOpt*, ucCmd *cmd);
uc_EXPORTED void                                ucCmdOpt_send_help(ucCmdOpt*, ucCmd *cmd);
uc_EXPORTED void                                ucCmdOpt_send_usage(ucCmdOpt*, ucCmd *cmd);
            struct                              ucCmdOpt {
            ucArgOptOwner                       base;
            ucCmdOpt_WorkFunc*                  work;
            void*                               state;
            ucSwitchOpt*                        switch_opt;
            ucCmdOpt*                           next; };

uc_EXPORTED ucCmdParser*                        ucCmdApp_get_cmd_parser(ucCmdApp*);
uc_EXPORTED ucCmdApp*                           ucCmdApp_init(ucCmdApp*, ucCmdParser*, ucCmd*);
uc_EXPORTED char*                               ucCmdApp_receive(ucCmdApp*);
            struct                              ucCmdApp {
            ucCmd*                              cmd;
            ucCmdParser*                        cmd_parser;
            ucCmdApp_ReceiveFunc*               receive;
            void*                               receive_state;
            const char*                         help_command;
            const char*                         quit_command;
            const char*                         escape_response;            
            char                                cmd_str[ucCmdApp_CMD_STR_SIZE + 1]; };

/** @brief Determines if two strings are equal.
 *  @param [in] S1 The first string to compare.
 *  @param [in] S2 The second string to compare.
 *
 *  This macro results in a truthy value if the string arguments are equal. It
 *  results in a falsey value if they are unequal.
 */
#define     uc_STR_EQ(S1, S2)                   (((S1) == (S2)) ? ucBool_true : ((!(S1)) || (!(S2))) ? ucBool_false : (0 == strcmp((S1), (S2))) ? ucBool_true : ucBool_false)

/* 
 * Summary:
 *   Defines a macro that is used to provide a dynamic
 *   feel to static-memory allocation. Calling it in a
 *   source file exposes functions to create and destroy
 *   objects of the specified type.
 * Parameters:
 *   TYPE: The type of the object instances that are
 *         created and destroyed using the manager.
 *   COUNT: The number of object instances that is
 *          available to the program. Once this number
 *          is exceeded, NULL is returned from the
 *          create function until instances are released
 *          using the destroy function.
 */
#define ucInstance_INIT(TYPE, COUNT)                                                \
    typedef struct {                                                                \
        char used;                                                                  \
        TYPE inst;                                                                  \
    } ucInstance;                                                                   \
                                                                                    \
    static ucInstance ucInstance_array[COUNT] = { 0 };                              \
                                                                                    \
    static TYPE *ucInstance_create(void) {                                          \
        int i;                                                                      \
        ucInstance *inst;                                                           \
        for (i = 0; i < COUNT; i++) {                                               \
            inst = &ucInstance_array[i];                                            \
            if (inst->used == 0) {                                                  \
                inst->used = 1;                                                     \
                return &inst->inst;                                                 \
            }                                                                       \
        }                                                                           \
        return NULL;                                                                \
    }                                                                               \
                                                                                    \
    static void ucInstance_destroy(TYPE *p) {                                       \
        int i;                                                                      \
        ucInstance *inst;                                                           \
        for (i = 0; i < COUNT; i++) {                                               \
            inst = &ucInstance_array[i];                                            \
            if (p == (&inst->inst)) {                                               \
                inst->used = 0;                                                     \
            }                                                                       \
        }                                                                           \
    }

#endif /* #ifndef UCMD_INTERNAL_H */
