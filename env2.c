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

	if (command->arg[2] == NULL)
	{
		command->output_message = "Usage: unsetenv VARIABLE";
		return;
	}

	result = _unsetenv(command->arg[2]);
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
	int env_size = 0, i;
	char *new_var = NULL;

	while (environ[env_size] != NULL)
		env_size++;
	new_var = malloc(_strlen(name) + _strlen(value) + 2);
	if (!new_var)
	{
		perror("Error in _addenv");
		return (-1);
	}
	_strcpy(new_var, name); /* Copy name to new_var */
	_strcpy(new_var + _strlen(name), "="); /* Concatenate "=" */
	_strcpy(new_var + _strlen(name) + 1, value); /*  Concatenate value */

	/* Shift existing variables to make room for the new one */
	for (i = env_size; i >= 0; i--)
	{
		environ[i + 1] = environ[i];
	}
	environ[0] = new_var;
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
		/* Variable exists, so we need to replace it */
		_unsetenv(name);
		_addenv(name, value);
	}
	else
	{
		/* Variable does not exist, so we create a new one */
		_addenv(name, value);
	}
	return (0);
}
