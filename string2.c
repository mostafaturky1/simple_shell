#include "shell.h"



/**
 * _strtok - Tokenize a string using delimiters
 * @str: The string to tokenize
 * @delim: The delimiters
 *
 * Return: Pointer to the next token, or NULL if no more tokens
 */

char *_strtok(char *str, const char *delim)
{
	static char *nextToken;
	char *tokenStart;

	if (str != NULL)
	{
		nextToken = str;
	}
	if (nextToken == NULL || delim == NULL || *nextToken == '\0')
	{
		return (NULL);
	}
	while (*nextToken != '\0' && _strchr(delim, *nextToken) != NULL)
	{
		nextToken++;
	}
	if (*nextToken == '\0')
	{
		return (NULL);
	}
	tokenStart = nextToken;
	while (*nextToken != '\0' && _strchr(delim, *nextToken) == NULL)
	{
		nextToken++;
	}
	if (*nextToken != '\0')
	{
		*nextToken = '\0';
		nextToken++;
	}
	return (tokenStart);
}

/**
 * _strdup - Duplicate a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string, or NULL on failure
 */

char *_strdup(const char *str)
{
	size_t len;
	char *copy;

	if (str == NULL)
	{
		return (NULL);  /*  Handle the case of a NULL input string. */
	}

	len = _strlen(str) + 1;  /* +1 for the null terminator */

	copy = (char *)malloc(len);
	if (copy != NULL)
	{
		_strcpy(copy, str);
	}

	return (copy);
}

/**
 * _strncmp - Compare two strings up to a specified number of characters
 * @str1: Pointer to the first string
 * @str2: Pointer to the second string
 * @n: Number of characters to compare
 *
 * Return: 0 if equal, negative if str1 < str2, positive if str1 > str2
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0 && *str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
		n--;
	}

	if (n == 0)
	{
		return (0);
	}
	else
	{
		return (*(unsigned char *)str1 - *(unsigned char *)str2);
	}
}
/**
 * _strstr - Locate a substring within a string
 * @haystack: Pointer to the string to search
 * @needle: Pointer to the substring to find
 *
 * Return: Pointer to first occurrence of the substring or NULL if not found
 */

char *_strstr(const char *haystack, const char *needle)
{
	while (*haystack)
	{
		const char *hay_ptr = haystack;
		const char *needle_ptr = needle;

		while (*hay_ptr && *needle_ptr && (*hay_ptr == *needle_ptr))
		{
			hay_ptr++;
			needle_ptr++;
		}

		if (!(*needle_ptr))
		{
			return ((char *)haystack);
		}

		haystack++;
	}
	return (NULL);
}

/**
 * _strncpy - Copy up to n characters from one string to another
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 * @n: Maximum number of characters to copy
 *
 * Return: Pointer to the destination string
 */

char *_strncpy(char *dest, const char *src, size_t n)
{
	char *dest_ptr = dest;
	const char *src_ptr = src;
	size_t i;

	for (i = 0; i < n && src_ptr[i] != '\0'; i++)
	{
		dest_ptr[i] = src_ptr[i];
	}

	for (; i < n; i++)
	{
		dest_ptr[i] = '\0';
	}

	return (dest);
}
