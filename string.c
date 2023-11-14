#include "shell.h"

/**
 * _strlen - Calculate the length of a string
 * @str: Pointer to the string
 *
 * Return: Length of the string
 */

size_t _strlen(const char *str)
{
	const char *temp = str;

	if (str == NULL)
	{
		return (0);
	}
	while (*temp)
	{
		temp++;
	}
	return ((size_t)(temp - str));
}

/**
 * _strcpy - Copy a string from source to destination
 * @dest: Pointer to the destination
 * @src: Pointer to the source
 *
 * Return: Pointer to the destination
 */

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	if (dest == NULL || src == NULL)
	{
		return (NULL);
	}

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strcmp - Compare two strings
 * @str1: Pointer to the first string
 * @str2: Pointer to the second string
 *
 * Return: 0 if equal, -1 if str1 < str2, 1 if str1 > str2
 */

int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 == *str2)
	{
		return (0);
	}
	else if
	(*str1 < *str2)
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}

/**
 * _strcat - Concatenate two strings
 * @dest: Pointer to the destination
 * @src: Pointer to the source
 *
 * Return: Pointer to the destination
 */

char *_strcat(char *dest, const char *src)
{
	/* Find the null terminator of dest */
	size_t dest_len = 0, i;

	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}

	i = 0;
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}

	/*  Null-terminate the resulting string */
	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * _strchr - Locate the first occurrence of a character in a string
 * @str: Pointer to the string
 * @ch: Character to locate
 *
 * Return: Pointer to the first occurrence the character or NULL if not found
 */

char *_strchr(const char *str, int ch)
{
	while (*str != '\0')
	{
		if (*str == (char)ch)
		{
			return ((char *)str);
		}
		str++;
	}

	if (ch == '\0')
	{
		return ((char *)str);
	}

	return (NULL);
}
