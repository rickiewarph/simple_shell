#include "shell.h"

/**
 **_strncpy - function to copy a string
 *@dest: dest string to copy to
 *@src: source string
 *@n: amount of chars to copy
 *Return: concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int m, p;
	char *s = dest;

	m = 0;
	while (src[m] != '\0' && m < n - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < n)
	{
		p = m;
		while (p < n)
		{
			dest[p] = '\0';
			p++;
		}
	}
	return (s);
}

/**
 **_strncat - function to concatenate strings
 *@dest: the 1st string
 *@src: the 2nd string
 *@n: maximum no. of bytes use
 *Return: concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int m, p;
	char *s = dest;

	m = 0;
	p = 0;
	while (dest[m] != '\0')
		m++;
	while (src[p] != '\0' && p < n)
	{
		dest[m] = src[p];
		m++;
		p++;
	}
	if (p < n)
		dest[m] = '\0';
	return (s);
}

/**
 **_strchr - to locate a char within a string
 *@s: string to parse
 *@c: char to locate
 *Return: (s) a pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

