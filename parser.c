#include "shell.h"

/**
 * Parser - Parse the input command into arguments
 * @command: Pointer to the str_cmd structure
 *
 * Return: None
 * Updates the command structure with parsed arguments.
 */

void Parser(str_cmd *command)
{
	int argCount = 0;
	char *cmd = _strdup(command->input);
	char *token = _strtok(cmd, DELIM_COMMAND);

	command->arg = NULL;
	while (token != NULL)
	{
		command->arg = (char **)_realloc(command->arg,
		(argCount + 1) * sizeof(char *));
		if (command->arg == NULL)
		{
			perror("Memory allocation error");
			exit(1);
		}


		command->arg[argCount] = _strdup(token);
		if (command->arg[argCount] == NULL)
		{
			perror("Memory allocation error");
			exit(1);
		}

		argCount++;
		token = _strtok(NULL, DELIM_COMMAND);
	}

	command->arg = (char **)_realloc(command->arg,
	(argCount + 1) * sizeof(char *));
	if (command->arg == NULL)
	{
		perror("Memory allocation error");
		exit(1);
	}
	command->arg[argCount] = NULL;  /* Null-terminate the arguments list */
	free(cmd);
}
