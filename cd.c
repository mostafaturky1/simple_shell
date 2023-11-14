#include "shell.h"

/**
 * cd_command - Change current directory based on input command
 * @command: Pointer to the command structure
 *
 * Return: None
 * Updates command structure with output status and message if needed.
 */

void cd_command(str_cmd *command)
{

	if (command->arg[1] == NULL)
	return;

	if (chdir(command->arg[1]) == -1)
	{
		command->output_status = -1;
		command->output_message = "No Such file or directory";
	}
}
