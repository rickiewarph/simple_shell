#include "shell.h"

/**
 * _strcpy - func to copy a string
 * @dest: destination
 * @src: source
 * Return: pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int m = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[m])
	{
		dest[m] = src[m];
		m++;
	}
	dest[m] = 0;
	return (dest);
}

/**
 * _strdup - func to duplicate a string
 * @str: string to duplicate
 * Return: pointer to duplicated string
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *rets;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	rets = malloc(sizeof(char) * (len + 1));
	if (!rets)
		return (NULL);
	for (len++; len--;)
		rets[len] = *--str;
	return (rets);
}

/**
 *_puts - func printing an input string
 *@str: string to print
 * Return: Nothing
 */

void _puts(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_putchar(str[m]);
		m++;
	}
}

/**
 * _putchar - func to writes c to stdout
 * @c: char to be printed
 * Return: 1(success), -1(error)
 */

int _putchar(char c)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(1, buf, m);
		m = 0;
	}
	if (c != BUF_FLUSH)
		buf[m++] = c;
	return (1);
}
