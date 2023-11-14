#include "shell.h"

/**
 * _printchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _printchar(char c)
{
	return (write(fileno(stdout), &c, 1));
}

/**
 * _printcharFile - writes the character c to the specified stream
 * @stream: The file stream to print to
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _printcharFile(FILE *stream, char c)
{
	return (write(fileno(stream), &c, 1));
}

/**
 * _printInt - writes the integer c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _printInt(size_t c)
{
	char buffer[20]; /* Assuming a maximum of 20 digits */
	int i = 0;
	int j;

	if (c == 0)
	{
		_printchar('0'); /* If the size_t value is 0, print '0' */
		return (0);
	}

	/* Extract and store the digits in reverse order */
	while (c > 0)
	{
		buffer[i] = '0' + (c % 10); /* Convert the digit to a character */
		c /= 10;
		i++;
	}

	/* Print the digits in reverse order */
	for (j = i - 1; j >= 0; j--)
	{
		_printcharFile(stdout, buffer[j]);
	}

	return (0);
}

/**
 * _printIntErr - writes the integer c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _printIntErr(size_t c)
{
	char buffer[20]; /*  Assuming a maximum of 20 digits */
	int i = 0;
	int j;

	if (c == 0)
	{
		_printcharFile(stderr, '0'); /* If the size_t value is 0, print '0' */
		return (0);
	}

	/* Extract and store the digits in reverse order */
	while (c > 0)
	{
		buffer[i] = '0' + (c % 10); /* Convert the digit to a character */
		c /= 10;
		i++;
	}

	/* Print the digits in reverse order */
	for (j = i - 1; j >= 0; j--)
	{
		_printcharFile(stderr, buffer[j]);
	}

	return (0);
}

/**
 * _print - prints a string to stdout
 * @str: Pointer to string
 */

void _print(char *str)
{
	int i = 0;

	while (str[i])
	{
		_printcharFile(stdout, str[i]);
		i++;
	}
}
