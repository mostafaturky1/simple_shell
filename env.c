#include "shell.h"

/**
 * _getenv - Retrieve the value of an environment variable
 * @varname: Name of the environment variable
 *
 * Return: Pointer to the value of the variable, or NULL if not found
 */

char *_getenv(const char *varname)
{
	size_t varname_len;
	char **env;

	if (varname == NULL)
	{
		return (NULL);
	}
	varname_len = _strlen(varname);
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, varname, varname_len) == 0 && (*env)[varname_len] == '=')
		{
			return (&(*env)[varname_len + 1]);
		}
	}
	return (NULL); /*  Variable not found in the environment */
}

/**
 * findExecutablePath - Find the executable path for a given command
 * @command: Pointer to the command structure
 *
 * Return: Pointer to the command structure with updated executablePath,
 *         or NULL if not found.
 */

void *findExecutablePath(str_cmd *command)
{
	char *path = _getenv("PATH");
	char *pathCopy;
	char *token;
	char *fullPath;

	command->executablePath = NULL;
	if (path == NULL)
	{
		return (NULL);
	}
	pathCopy = _strdup(path);
	token = _strtok(pathCopy, ":");
	while (token != NULL)
	{
		/*  Check if the executable file exists in the current directory */
		fullPath = (char *)malloc(_strlen(token) + 1 + _strlen(command->arg[0]) + 1);
		_strcpy(fullPath, token);
		_strcat(fullPath, "/");
		_strcat(fullPath, command->arg[0]);

		if (access(fullPath, X_OK) == 0)
		{
			command->executablePath = _strdup(fullPath);
			free(fullPath);
			free(pathCopy);
			return (command);
		}

		free(fullPath);
		token = _strtok(NULL, ":");
	}
	free(pathCopy);
	return (NULL);
}

/**
 * env_command - Print the environment variables to the standard output.
 * @command: Pointer to the command structure
 *
 * Return: None
 * Updates command structure with output status and message if needed.
 */

void env_command(str_cmd *command)
{
	char **env_var = environ;

	command->output_message = NULL;
	command->output_status = 0;

	while (*env_var != NULL)
	{
		_print(*env_var);
		_print("\n");
		env_var++;
	}
}

/**
 * _unsetenv - Remove an environment variable
 * @name: Name of the environment variable to remove
 *
 * Return: 0 on success, -1 if the variable is not found or invalid
 */

int _unsetenv(const char *name)
{
	char **current = environ;
	char **previous = NULL;

	if (name == NULL || name[0] == '\0')
		return (-1);

	while (*current != NULL)
	{
		if (_strstr(*current, name) == *current)
		{
			/* Found the environment variable, remove it */
			if (previous == NULL)
			{
				/* Variable to be removed is at the beginning of the environment */
				environ++;
			}
			else
			{
				/* Variable to be removed is not at the beginning */
				*previous = *(current + 1); /* Shift the environment array */
			}
			/* Free the memory */
			free(*current);
			return (0);
		}
		previous = current;
		current++;
	}
	return (-1); /* Variable not found */
}

/**
 * setenv_command - Set the value of an environment variable
 * @command: Pointer to the command structure
 *
 * Return: None
 * Updates command structure with output status and message if needed.
 */

void setenv_command(str_cmd *command)
{
	int result;

	if (command->arg[2] == NULL || command->arg[3] == NULL)
	{
		command->output_message = "Usage: setenv VARIABLE VALUE";
		return;
	}
	result = _setenv(command->arg[2], command->arg[3]);
	if (result == -1)
	{
		command->output_message = "_setenv error";
	}
}
