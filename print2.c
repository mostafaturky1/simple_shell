#include "shell.h"

/**
 * _strrchr - Locate the last occurrence of a character in a string
 * @str: Pointer to the string
 * @character: Character to locate
 *
 * Return: Pointer to the last occurrence of the character or NULL if not found
 */

char *_strrchr(const char *str, int character)
{
	const char *last = NULL;

	while (*str)
	{
		if (*str == character)
		{
			last = str;
		}
		str++;
	}

	return ((char *)last);
}

/**
 * _printErr - prints a string to stderr
 * @str: Pointer to string
 */

void _printErr(char *str)
{
	int i = 0;

	while (str[i])
	{
		_printcharFile(stderr, str[i]);
		i++;
	}
}
