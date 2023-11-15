#include "shell.h"

/**
 * unsetenv_command - Remove an environment variable
 * @command: Pointer to the command structure
 *
 * Return: None
 * Updates command structure with output status and message if needed.
 */

void unsetenv_command(str_cmd *command)
{
	int result;

	if (command->arg[1] == NULL)
	{
		command->output_message = "Usage: unsetenv VARIABLE";
		return;
	}

	result = _unsetenv(command->arg[1]);
	if (result == -1)
	{
		command->output_message = "Variable not found";
	}
}

/**
 * _addenv - Add a new environment variable
 * @name: Name of the environment variable
 * @value: Value of the environment variable
 *
 * Return: 0 on success, -1 on failure
 */

int _addenv(const char *name, const char *value)
{
	int env_size = 0;
	char *new_var = NULL;

	while (environ[env_size] != NULL)
		env_size++;
	new_var = malloc(_strlen(name) + _strlen(value) + 2);
	if (!new_var)
	{
		perror("Error in _addenv");
		return (-1);
	}
	_strcpy(new_var, name);
	_strcpy(new_var + _strlen(name), "=");
	_strcpy(new_var + _strlen(name) + 1, value);
	environ[env_size] = new_var;
	environ[env_size + 1] = NULL;
	return (0);
}

/**
 * _setenv - Set the value of an environment variable or create a new one
 * @name: Name of the environment variable
 * @value: Value of the environment variable
 *
 * Return: 0 on success, -1 on failure
 */

int _setenv(char *name, char *value)
{
	char *var;

	var = _getenv(name);

	if (name == NULL || name[0] == '\0' || value == NULL)
	{
		return (-1);
	}

	if (var)
	{
		_replaceenv(name, value);
	}
	else
	{
		_addenv(name, value);
	}
	return (0);
}

/**
 * _replaceenv - Replaces or adds an environment variable with a new value.
 * @name: The name of the environment variable.
 * @new_value: The new value for the environment variable.
 */

void _replaceenv(const char *name, const char *new_value)
{
	char *new_var;
	int i;

	if (name == NULL || name[0] == '\0' || new_value == NULL)
	{
		return;
	}
	new_var = malloc(_strlen(name) + _strlen(new_value) + 2);
	if (!new_var)
	{
		perror("Error in _replaceenv");
		return;
	}
		_strcpy(new_var, name);
		_strcat(new_var, "=");
		_strcat(new_var, new_value);
		for (i = 0; environ[i] != NULL; i++)
		{
			if (_strncmp(environ[i], name, _strlen(name)) == 0 &&
			environ[i][_strlen(name)] == '=')
			{
				free(environ[i]);
				environ[i] = new_var;
				return;
			}
		}
}
