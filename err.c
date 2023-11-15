#include "shell.h"

/**
 *_eputs - func printing an input string
 * @str: string to print
 * Return: Nothing
 */

void _eputs(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_eputchar(str[m]);
		m++;
	}
}

/**
 * _eputchar - func to write char c to stderr
 * @c: char to be printed
 * Return: 1(success) or -1(fail)
 */

int _eputchar(char c)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(2, buf, m);
		m = 0;
	}
	if (c != BUF_FLUSH)
		buf[m++] = c;
	return (1);
}

/**
 * _putfd - func writing char c to a particluar filedescriptor
 * @c: char to be printed
 * @fd: filedescriptor to write to
 * Return: 1(success) or -1(fail)
 */

int _putfd(char c, int fd)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(fd, buf, m);
		m = 0;
	}
	if (c != BUF_FLUSH)
		buf[m++] = c;
	return (1);
}

/**
 *_putsfd -func printing an input string
 * @str: string to print
 * @fd: filedescriptor to write to
 * Return: no. of chars put
 */

int _putsfd(char *str, int fd)
{
	int m = 0;

	if (!str)
		return (0);
	while (*str)
	{
		m += _putfd(*str++, fd);
	}
	return (m);
}
