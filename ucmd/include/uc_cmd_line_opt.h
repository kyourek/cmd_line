#ifndef UC_CMD_LINE_OPT_H
#define UC_CMD_LINE_OPT_H

#include "uc_arg_opt_owner.h"
#include "uc_cmd_line.h"
#include "uc_cmd_tok.h"
#include "uc_switch_opt.h"

/*
 * Summary:
 *   A command option. This type is a child of the
 *   base option type.
 */
typedef struct uc_cmd_line_opt uc_cmd_line_opt;

/*
 * Summary:
 *   Defines the signature of the function called when a command option is processed.
 * Parameters:
 *   cmd: The parsed command structure that represents the function parameters.
 *   state: The state pointer with which the command option was created.
 * Returns:
 *   A message that can be used to respond to the command.
 */
typedef const char *(uc_cmd_line_opt_func)(uc_cmd_line *cmd, void *state);

/*
 * Summary:
 *   Creates a new command option.
 * Parameters:
 *   func: A pointer to the function that is called when this command is invoked or selected.
 *   state: A pointer that gets passed to the function to maintain state.
 *   name: The name of the command.
 *   desc: The description of the command.
 *   arg_opt: The argument options available to the command.
 *   switch_opt: The switch options available to the command.
 *   next: The next command that the created command precedes, or NULL if no further commands exist.
 * Returns:
 *   A pointer to the newly created command option.
 */
UC_EXPORTED uc_cmd_line_opt *uc_cmd_line_opt_create(uc_cmd_line_opt_func *func, void *state, const char *name, const char *desc, uc_arg_opt *arg_opt, uc_switch_opt *switch_opt, uc_cmd_line_opt* next);

/*
 * Summary:
 *   Gets the next command option after the given option.
 * Parameters:
 *   p: The command option that precedes the option to be returned.
 * Returns:
 *   A pointer to the next command option.
 */
UC_EXPORTED uc_cmd_line_opt *uc_cmd_line_opt_get_next(uc_cmd_line_opt *p);

/*
 * Summary:
 *   Gets the first argument option of the command.
 * Parameters:
 *   p: A pointer to the command option.
 * Returns:
 *   A pointer to the first argument option of the command,
 *   or NULL if no argument options exist.
 */
UC_EXPORTED uc_arg_opt *uc_cmd_line_opt_get_arg_opt(uc_cmd_line_opt *p);

/*
 * Summary:
 *   Gets the first switch option of the command option.
 * Parameters:
 *   p: A pointer to the command option whose switch argument is to be returned.
 * Returns:
 *   A pointer to the first switch option of the command option,
 *   or NULL if no switch options exist.
 */
UC_EXPORTED uc_switch_opt *uc_cmd_line_opt_get_switch_opt(uc_cmd_line_opt *p);

/*
 * Summary:
 *   Finds the command option that matches the given name.
 * Parameters:
 *   p: A pointer to the first command option in the list of options.
 *   name: The name of the command whose option is to be found.
 * Returns:
 *   A pointer to the command option that matches the given name, or NULL
 *   if no option is found.
 */
UC_EXPORTED uc_cmd_line_opt *uc_cmd_line_opt_find_by_name(uc_cmd_line_opt *p, const char *name);

/*
 * Summary:
 *   Gets the pointer to the function invoked when the command option
 *   is processed.
 * Parameters:
 *   p: A pointer to the command option whose function is to be returned.
 * Returns:
 *   A pointer to the function invoked when the command option is processed.
 */
UC_EXPORTED uc_cmd_line_opt_func *uc_cmd_line_opt_get_func(uc_cmd_line_opt *p);

/*
 * Summary:
 *   Gets the state pointer that is passed to the command option's function
 *   when it is invoked.
 * Parameters:
 *   p: A pointer to the command option.
 * Returns:
 *   A pointer to the command option's state.
 */
UC_EXPORTED void *uc_cmd_line_opt_get_state(uc_cmd_line_opt *p);

/*
 * Summary:
 *   Releases memory used by the command option.
 * Parameters:
 *   p: A pointer to the command option whose memory is released.
 */
UC_EXPORTED void uc_cmd_line_opt_destroy(uc_cmd_line_opt *p);

/*
 * Summary:
 *   Releases memory used by the command option and all proceeding options
 *   in the list. All memory used by any argument options, switch options,
 *   and switch-argument options is also released.
 * Parameters:
 *   p: A pointer to the first command option in the list to be released.
 */
UC_EXPORTED void uc_cmd_line_opt_destroy_chain(uc_cmd_line_opt *p);

/*
 * Summary:
 *   Invokes the function of the command option that matches the command structure.
 * Parameters:
 *   p: A pointer to the first command option in a list. The list will
 *      be traversed until the appropriate option is found for the given
 *      command.
 *   cmd: The command structure whose option is invoked.
 * Returns:
 *   The response to the command.
 */
UC_EXPORTED const char *uc_cmd_line_opt_process(uc_cmd_line_opt *p, uc_cmd_line *cmd);

/*
 * Summary:
 *   Uses the provided command structure to respond with a usage string 
 *   for this command option.
 * Parameters:
 *   p: A pointer to the option whose usage string will be sent.
 *   cmd: The command structure used to respond with the usage string.
 */
UC_EXPORTED void uc_cmd_line_opt_send_usage(uc_cmd_line_opt *p, uc_cmd_line *cmd);

/*
 * Summary:
 *   Uses the provided command structure to respond with help information
 *   for the this command option.
 * Parameters:
 *   p: A pointer to the command option for which help is sent.
 *   cmd: The command structure used to respond with the help information.
 */
UC_EXPORTED void uc_cmd_line_opt_send_help(uc_cmd_line_opt *p, uc_cmd_line *cmd);

#endif