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
	int i;

	if (name == NULL || name[0] == '\0')
	{
		perror("Invalid variable name");
		return (-1);
	}
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0
		&& environ[i][_strlen(name)] == '=')
		{
			free(environ[i]);
			while (environ[i] != NULL)
			{
				environ[i] = environ[i + 1];
				i++;
			}
			return (0);
		}
	}
	perror("Variable not found");
	return (-1);
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

	if (command->arg[1] == NULL || command->arg[2] == NULL)
	{
		command->output_message = "Usage: setenv VARIABLE VALUE";
		return;
	}
	result = _setenv(command->arg[1], command->arg[2]);
	if (result == -1)
	{
		command->output_message = "_setenv error";
	}
}
