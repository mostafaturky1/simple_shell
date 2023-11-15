#include "shell.h"

/**
 * exit_command - Handle the exit command
 * @command: Pointer to the command structure
 *
 * Return: None
 * Exits the shell with the specified status or 0 if no argument is provided.
 */

void exit_command(str_cmd *command)
{
	int status = 0;

	if (command->output_status == STATUS_ERROR)
		status = command->output_status;

	command->executablePath = NULL;
	/* No argument provided, exit with status 0 */
	free_struct(command);
	exit(status);
}

/**
 * contol_C - Handle the SIGINT signal (Ctrl+C)
 * @sig_num: Signal number
 *
 * Return: None
 * Prints a new prompt if Ctrl+C is received.
 */

void contol_C(int sig_num)
{
	char *prompt = "\n($) ";

	if (sig_num == SIGINT)
	{
		_print(prompt);
	}
}
