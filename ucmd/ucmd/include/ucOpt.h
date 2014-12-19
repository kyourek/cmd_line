#ifndef UCOPT_H
#define UCOPT_H

#include "ucCmdLine.h"

/*
 * Summary:
 *   Base type for command, argument, and switch options.
 */
typedef struct ucOpt ucOpt;

/*
 * Summary:
 *   Gets the name of the option.
 * Parameters:
 *   p: A pointer to the option.
 * Returns:
 *   The name of the option.
 */
UC_EXPORTED const char* ucOpt_get_name(ucOpt *p);

/*
 * Summary:
 *   Gets the description of the option.
 * Parameters:
 *   p: A pointer to the option.
 * Returns:
 *   The description of the option.
 */
UC_EXPORTED const char *ucOpt_get_desc(ucOpt *p);

/*
 * Summary:
 *   Gets a flag that indicates whether or not the option
 *   is required.
 * Parameters:
 *   p: A pointer to the option in question.
 * Returns:
 *   ucBool_true if the option is required. Otherwise, ucBool_false.
 */
UC_EXPORTED ucBool ucOpt_is_required(ucOpt *p);

/*
 * Summary:
 *   Uses the provided command structure to send help information
 *   for this option.
 * Parameters:
 *   p: A pointer to the option for which help is sent.
 *   cmd: A pointer to the command structure used to respond
 *        with the help information.
 *   prefix: A string used to prefix the help information.
 */
UC_EXPORTED void ucOpt_send_help(ucOpt *p, ucCmdLine *cmd, const char *prefix);

#endif
