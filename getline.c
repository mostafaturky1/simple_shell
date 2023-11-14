#include "shell.h"

/**
 * _isspace - Check if a character is a whitespace character
 * @c: The character to check
 *
 * Return: 1 if the character is a whitespace character, 0 otherwise
 */

int _isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
	c == '\v' || c == '\f');
}

/**
 * readLine - Read a line from standard input
 *
 * Return: Pointer to the read line
 * Memory is dynamically allocated for the line and should be freed.
 */

char *readLine(void)
{
	char buffer[1024];
	ssize_t bytesRead;
	size_t totalSize = 0;
	char *input = NULL;
	char *newlinePos;

	while ((bytesRead = read(0, buffer, sizeof(buffer))) > 0)
	{
		char *temp = (char *)_realloc(input, totalSize + bytesRead + 1);

		if (temp == NULL)
		{
			perror("Memory allocation error");
			free(input);
			return (NULL);
		}
		input = temp;
		_memcpy(input + totalSize, buffer, bytesRead);
		totalSize += bytesRead;
		input[totalSize] = '\0';

		newlinePos = _strchr(input, '\n');
		if (newlinePos != NULL)
		{
			newlinePos = "\0";  /* Replace newline with null terminator */
			break;
		}
	}

	return (input);
}

/**
 * readAll - Read all input from standard input
 *
 * Return: Pointer to the read input
 * Memory is dynamically allocated for the input and should be freed.
 */

char *readAll(void)
{
	char buffer[BUFFER_SIZE];
	char *result = NULL;
	size_t totalSize = 0;
	ssize_t i = 0;
	ssize_t bytesRead;

	while ((bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
	{
		/*  Allocate memory for the result buffer */
		result = realloc(result, totalSize + bytesRead + 1);
		if (result == NULL)
		{
			exit(EXIT_FAILURE);
		}

		/*  Copy the current buffer to the result buffer */
		for (i = 0; i < bytesRead; ++i)
		{
			result[totalSize + i] = buffer[i];
		}

		/* // Update the total size */
		totalSize += bytesRead;
	}

	/* // Check for read errors */
	if (bytesRead == -1)
	{
		exit(EXIT_FAILURE);
	}

	/* // Null-terminate the result string */
	result[totalSize] = '\0';

	return (result);
}

/**
 * finalizeLines - Finalize the lines array by adding the last line
 * @lines: Array of lines
 * @lineCount: Pointer to the number of lines
 * @input: The input string
 *
 * Return: None
 */

void finalizeLines(char **lines, size_t *lineCount, const char *input)
{
	const char *start = input + _strlen(input) - 1;

	if (*start != '\n')
	{
		size_t length = _strlen(input);

		lines[*lineCount] = malloc((length + 1) * sizeof(char));
		if (lines[*lineCount] == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		strncpy(lines[*lineCount], start, length);
		lines[*lineCount][length] = '\0'; /* Null-terminate the last line */

		(*lineCount)++;
	}
}

/**
 * splitLines - Split the input string into an array of lines
 * @input: The input string
 * @lineCount: Pointer to the number of lines
 *
 * Return: Array of lines
 * Memory is dynamically allocated for the lines and should be freed.
 */

char **splitLines(const char *input, size_t *lineCount)
{
	size_t bufferSize = 1, length, count = 0;
	const char *start = input, *end;
	char **lines = malloc(bufferSize * sizeof(char *));

	if (lines == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	while ((end = _strchr(start, '\n')) != NULL)
	{
		length = end - start;
		if (length == 0)
		{
			start = end + 1;
			continue;
		}
		lines[count] = malloc((length + 1) * sizeof(char));
		if (lines[count] == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		_strncpy(lines[count], start, length);
		lines[count][length] = '\0'; /* Null-terminate the line */
		count++;
		if (count == bufferSize)
		{
			bufferSize++;
			lines = _realloc(lines, bufferSize * sizeof(char *));
			if (lines == NULL)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}
		}
		start = end + 1;
	}
	*lineCount = count;
	return (lines);
}
