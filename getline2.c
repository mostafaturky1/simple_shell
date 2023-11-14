#include "shell.h"

/**
 * trimSpaces - Trim leading and trailing spaces from a string
 * @input: The input string
 *
 * Return: Trimmed string
 * Memory is dynamically allocated for the trimmed string and should be freed.
 */

char *trimSpaces(const char *input)
{
	size_t length = _strlen(input);
	size_t endIndex = 0;
	size_t trimmedLength = 0;
	char *trimmedString;
	size_t startIndex = 0;

	while (startIndex < length && _isspace(input[startIndex]))
	{
		startIndex++;
	}

	/* // Find the end index of non-space character */
	endIndex = length - 1;
	while (endIndex > startIndex && _isspace(input[endIndex]))
	{
		endIndex--;
	}

	/* // Calculate the size of the trimmed string */
	trimmedLength = (startIndex <= endIndex) ? (endIndex - startIndex + 1) : 0;

	/* // Allocate memory for the trimmed string */
	trimmedString = malloc(trimmedLength + 1); /* // +1 for the null terminator */
	if (trimmedString == NULL)
	{
		perror("Memory allocation error");
		return (trimmedString);
	}

	/* // Copy the trimmed part to the new string */
	if (trimmedLength > 0)
	{
		_strncpy(trimmedString, input + startIndex, trimmedLength);
	}

	/* // Null-terminate the trimmed string */
	trimmedString[trimmedLength] = '\0';

	return (trimmedString);
}

/**
 * _getAll - Read all input lines and trim leading and trailing spaces
 * @lineCount: Pointer to the number of lines
 *
 * Return: Array of trimmed lines
 * Memory is dynamically allocated for the lines and should be freed.
 */

char **_getAll(size_t *lineCount)
{
	char *input, **lines;
	size_t i;
	char *timmedLine;

	input = readAll();
	lines = splitLines(input, lineCount);
	for (i = 0; i < *lineCount; ++i)
	{
		timmedLine = lines[i];
		lines[i] = trimSpaces(timmedLine);
		free(timmedLine);
	}

	free(input);
	return (lines);
}

/**
 * _getline - Read a single input line and trim leading and trailing spaces
 * @lineCount: Pointer to the number of lines
 *
 * Return: Array containing a single trimmed line
 * Memory is dynamically allocated for the line and should be freed.
 */

char **_getline(size_t *lineCount)
{
	char *input, **lines;
	size_t i;
	char *timmedLine;

	input = readLine();
	if (input == NULL)
		return (NULL);

	lines = splitLines(input, lineCount);
	for (i = 0; i < *lineCount; ++i)
	{
		timmedLine = lines[i];
		lines[i] = trimSpaces(timmedLine);
		free(timmedLine);
	}

	free(input);
	return (lines);
}

/**
 * getCommand - Extract the command from a file path
 * @path: The file path
 *
 * Return: Pointer to the extracted command
 * Memory is dynamically allocated for the command and should be freed.
 */

char *getCommand(const char *path)
{
	/* // Find the last occurrence of the directory separator */
	const char *lastSeparator = _strrchr(path, '/');

	/* // If the separator is found, return the substring after it */
	if (lastSeparator != NULL)
	{
		return (_strdup(lastSeparator + 1));
	}
	else
	{
		/* // If no separator is found, the whole path is the last part */
		return (_strdup(path));
	}
}
