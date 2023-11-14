#include "shell.h"

/**
 * default_command - Execute the given command using exec,
 * updating the command status.
 *
 * This function attempts to execute the specified command using exec.
 * If the execution fails, it updates the command status accordingly.
 *
 * @command: Pointer to the command structure.
 */

void default_command(str_cmd *command)
{
	if (exec(command->executablePath,
	command->arg, environ))
	{
		command->output_status = STATUS_ERROR;
	}
}

/**
 * exec - Execute the specified command with arguments
 * and environment variables.
 *
 * This function creates a child process to execute
 * the given command with the provided arguments
 * and environment variables using the execve system call.
 * It waits for the child process to complete
 * and returns the exit status of the child process.
 *
 * @command: The command to be executed.
 * @arguments: The array of arguments for the command.
 * @env: The environment variables for the command.
 *
 * Return: The exit status of the executed command.
 */

int exec(char *command, char *arguments[], char *const env[])
{
	int status;
	pid_t child_pid;

	if (command == NULL)
	{
		return (-1);
	}
	if (arguments == NULL)
	{
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
	{
		status = execve(command, arguments, env);
		exit(EXIT_FAILURE);
	}
	else if (child_pid > 0)
	{
		wait(&status);
	}
	else
	{
		exit(1);
	}
	return (status);
}
