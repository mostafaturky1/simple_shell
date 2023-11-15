#include "shell.h"
#include <string.h>


/**
 * notFounderr - Sets "not found" as the output message
 * and marks the command as failed.
 *
 * @command: The command structure.
 */

void notFounderr(str_cmd *command)
{
	command->output_message = "not found";
	command->output_status = STATUS_FAILED_FULL;
}

/**
 * execute - Execute the given command
 * @command: Pointer to the command structure
 *
 * Return: None
 * Updates command structure with output status and message if needed.
 */

void execute(str_cmd *command)
{
	void (*command_executor)(str_cmd *) = default_command;

	command->output_status = STATUS_SUCCESS;
	findExecutablePath(command);
	if (_strcmp(command->arg[0], "exit") == 0)
	{
		command_executor = exit_command;
	}
	if (_strcmp(command->arg[0], "cd") == 0)
	{
		command_executor = cd_command;
	}
	if (_strcmp(command->arg[0], "setenv") == 0)
	{
		command_executor = setenv_command;
	}
	if (_strcmp(command->arg[0], "unsetenv") == 0)
	{
		command_executor = unsetenv_command;
	}
	if (_strcmp(command->arg[0], "env") == 0)
	{
		command_executor = env_command;
	}
	if (_strchr(command->arg[0], '/') != NULL)
	{
		command->executablePath = _strdup(command->arg[0]);
	}
	if (command_executor == default_command && command->executablePath == NULL)
	{
		notFounderr(command);
		return;
	}
	if (command_executor == default_command &&
	access(command->executablePath, X_OK) != 0)
	{
		notFounderr(command);
		return;
	}
	(*command_executor)(command);
}
