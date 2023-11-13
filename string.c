#include "shell.h"

/**
 * _strlen - func to return string len
 * @s: string whose length is to be checked
 * Return: int len of string
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - func to lexicogarphically compare two string.
 * @s1: 1st string
 * @s2: 2nd string
 * Return: negative(s1 < s2) ,positive(s1 > s2), or zero(s1 == s2)
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - func to check whether needle starts with haystack
 * @haystack: string to be searched
 * @needle: the substring to locate
 * Return: address of next character of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - func that concatenates two strings
 * @dest: buffer destination
 * @src: source buffer
 * Return: pointer to destination buffer
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
