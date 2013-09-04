#ifndef CL_CMD_LINE_APP_H
#define CL_CMD_LINE_APP_H

#include "cl_cmd_parser.h"
#include "cl_common.h"
#include "cl_cmd_line_opt.h"

/*
 * Summary:
 *   An application that runs with a set of command options.
 */
typedef struct cl_cmd_line_app cl_cmd_line_app;

/*
 * Summary:
 *   The type of the function used by an application to
 *   receive data.
 */
typedef char *(cl_cmd_line_app_receive_func)(char *buf, int buf_size);

/*
 * Summary:
 *   The type of function used by an application to
 *   determine if it is ready to receive data.
 */
typedef CL_BOOL (cl_cmd_line_app_ready_func)(void);

/*
 * Summary:
 *   Sets the escape string that will cause the app to exit.
 * Parameters:
 *   p: A pointer to the app whose property is set.
 *   value: The escape string that, when returned in a response,
 *          causes the app to exit.
 */
CL_EXPORTED void cl_cmd_line_app_set_escape_response(cl_cmd_line_app *p, const char *value);

/*
 * Summary:
 *   Gets the escape string that causes the app to exit.
 * Parameters:
 *   p: A pointer to the app whose property is returned.
 * Returns:
 *   The escape string that, when returned in a response,
 *   causes the app to exit.
 */
CL_EXPORTED const char *cl_cmd_line_app_get_escape_response(cl_cmd_line_app *p);

/*
 * Summary:
 *   Runs the application with the given options.
 * Parameters:
 *   p: A pointer to the app to run.
 *   cmd_opt: A pointer to the first command option for the app.
 * Returns:
 *   An error code, if one occurred.
 */ 
CL_EXPORTED CL_ERR cl_cmd_line_app_run(cl_cmd_line_app *p, cl_cmd_line_opt *cmd_opt);

/*
 * Summary:
 *   Gets a static, default instance of the application.
 * Returns:
 *   The static, default instance of the application.
 */
CL_EXPORTED cl_cmd_line_app *cl_cmd_line_app_get_instance(void);

/*
 * Summary:
 *   Sets the function that the app uses to receive data.
 * Parameters:
 *   p: A pointer to the app whose property is set.
 *   value: A pointer to the function used to receive data.
 */
CL_EXPORTED void cl_cmd_line_app_set_receive(cl_cmd_line_app *p, cl_cmd_line_app_receive_func *value);

/*
 * Summary:
 *   Gets the function that the app uses to receive data.
 * Parameters:
 *   p: A pointer to the app whose property is returned.
 * Returns:
 *   A pointer to the function used to receive data.
 */ 
CL_EXPORTED cl_cmd_line_app_receive_func *cl_cmd_line_app_get_receive(cl_cmd_line_app *p);

/*
 * Summary:
 *   Sets the command used to quit the application.
 * Parameters:
 *   p: A pointer to the application.
 *   value: The value of the command that quits the application.
 */
CL_EXPORTED void cl_cmd_line_app_set_quit_command(cl_cmd_line_app *p, const char *value);

/*
 * Summary:
 *   Gets the value of the command that quits the application.
 * Parameters:
 *   p: A pointer to the application.
 * Returns:
 *   The value of the command that quits the application.
 */
CL_EXPORTED const char *cl_cmd_line_app_get_quit_command(cl_cmd_line_app *p);

/*
 * Summary:
 *   Sets the value of the command that shows help information.
 * Parameters:
 *   p: A pointer to the application whose property is set.
 *   value: The value of the command that shows help information.
 */
CL_EXPORTED void cl_cmd_line_app_set_help_command(cl_cmd_line_app *p, const char *value);

/*
 * Summary:
 *   Gets the value of the command that shows help information.
 * Parameters:
 *   p: A pointer to the app whose property is returned.
 * Returns:
 *   The value of the command that shows help information.
 */
CL_EXPORTED const char *cl_cmd_line_app_get_help_command(cl_cmd_line_app *p);

/*
 * Summary:
 *   Sets the command structure that the application uses.
 * Parameters:
 *   p: A pointer to the application.
 *   value: The command structure to be used by the application.
 */
CL_EXPORTED void cl_cmd_line_app_set_cmd(cl_cmd_line_app *p, cl_cmd_line *value);

/*
 * Summary:
 *   Gets the command structure used by the application.
 * Parameters:
 *   p: A pointer to the application.
 * Returns:
 *   A pointer to the command structure used by the application.
 */
CL_EXPORTED cl_cmd_line *cl_cmd_line_app_get_cmd(cl_cmd_line_app *p);

/*
 * Summary:
 *   Gets the command parser used by the application.
 * Parameters:
 *   p: A pointer to the application.
 * Returns:
 *   A pointer to the command parser used by the application.
 */
CL_EXPORTED cl_cmd_parser *cl_cmd_line_app_get_cmd_parser(cl_cmd_line_app *p);

/*
 * Summary:
 *   Sets the function used by the application to determine if it is ready to
 *   receive data.
 * Parameters:
 *   p: A pointer to the app whose property is set.
 *   value: A callback to be used to determine if the application is ready to receive data.
 */
CL_EXPORTED void cl_cmd_line_app_set_ready(cl_cmd_line_app *p, cl_cmd_line_app_ready_func *value);

/*
 * Summary:
 *   Gets the function used by the application to determine if it is ready to
 *   receive data.
 * Parameters:
 *   p: A pointer to the app whose property is returned.
 * Returns:
 *   A pointer to the function used to determine if the application is ready
 *   to receive data.
 */
CL_EXPORTED cl_cmd_line_app_ready_func *cl_cmd_line_app_get_ready(cl_cmd_line_app *p);

#endif
