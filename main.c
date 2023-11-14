#include "shell.h"

/**
 * isInteractiveMode - Check if the shell is in interactive mode
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */

int isInteractiveMode(void)
{
	return (isatty(STDIN_FILENO));
}

/**
 * handleFailed - Handle the case when the command execution status is FAILED
 * @command: Pointer to the str_cmd structure representing the command
 * @i: Index of the current command in the lines array
 * @status: Pointer to the status variable to be updated
 */

void handleFailed(str_cmd *command, size_t i, int *status)
{
	_printErr("./hsh: ");   /*  need to be hsh */
	_printIntErr(i + 1);
	_printErr(": ");
	_printErr(command->arg[0]);
	_printErr(": ");
	_printErr(command->output_message);
	_printErr("\n");
	*status = _EXIT_FAILURE;
}

/**
 * is_Exit - Checks if the command is the exit command and performs actions.
 *
 * This function is responsible for checking if the given
 * command corresponds to the exit command.
 * If it does, the function frees the allocated memory,
 * sets the appropriate status, and exits the shell.
 *
 * @lines: Array of input lines.
 * @command: Pointer to the structure containing command information.
 * @i: Index of the current line in the array.
 * @status: Pointer to the overall status of the shell.
 */

void is_Exit(char **lines, str_cmd *command, size_t i, int *status)
{
	free(lines[i]);
	free(lines);
	if (*status == STATUS_ERROR)
	{
		command->output_status = STATUS_ERROR;
	}
	exit_command(command);
}

/**
 * run - Execute the given command lines handle shell behavior and free memory.
 *
 * This function iterates through input lines,
 * parses and executes each command,
 * and handles the shell behavior based on the results.
 * It also frees allocated memory.
 *
 * @lines: Array of input lines.
 * @line_count: Number of lines in the array.
 *
 * Return: Overall shell status.
 */
int run(char **lines, size_t line_count)
{
	str_cmd command;
	size_t i;
	int status = EXIT_SUCCESS;

	if (!lines)
	{
		return (-1);
	}
	for (i = 0; i < line_count; i++)
	{
		command.output_message = NULL;
		command.output_status = STATUS_SUCCESS;
		command.input = _strdup(lines[i]);
		Parser(&command);
		if (!command.arg || !command.arg[0])
		{
			command.executablePath = NULL;
			free_struct(&command);
			free(lines[i]);
			continue;
		}
		if (_strcmp(command.arg[0], "exit") == 0)
		{
			is_Exit(lines, &command, i, &status);
		}
		execute(&command);
		if (command.output_status == STATUS_FAILED_FULL)
		{
			handleFailed(&command, i, &status);
		}
		if (command.output_status == STATUS_ERROR)
		{
			status = STATUS_ERROR;
		}
		free_struct(&command);
		free(lines[i]); /*  Free individual lines */
	}
	free(lines); /*  Free the array of lines */
	return (status); /* Return status */
}

/**
 * main - Entry point of the custom shell program.
 *
 * This function sets up the shell environment, processes user commands,
 * and executes them accordingly. It runs an infinite loop for interactive
 * mode, prompting the user for input and handling the commands.
 *
 * Return: Returns the exit status of the shell program.
 */

int main(void)
{
	size_t line_count = 0;
	char **lines = NULL;
	int status = EXIT_SUCCESS;
	char **(*input_func)(size_t *) = _getAll;

	signal(SIGINT, contol_C);
	while (1)
	{
		if (isInteractiveMode())
		{
			_print("($) ");
			input_func = _getline;
		}

		lines = (*input_func)(&line_count);
		status = run(lines, line_count);

		if (status || !isInteractiveMode())
		{
			break;
		}
	}
	return (status);
}

