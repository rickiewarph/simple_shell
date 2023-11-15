#include "shell.h"

/**
 * _erratoi - conversion of a string to an int
 * @s: string to convert
 * Return: 0(no nos. in string or converted no.) or -1(otherwise)
 */

int _erratoi(char *s)
{
	int m = 0;
	unsigned long int outcome = 0;

	if (*s == '+')
		s++;
	for (m = 0;  s[m] != '\0'; m++)
	{
		if (s[m] >= '0' && s[m] <= '9')
		{
			outcome *= 10;
			outcome += (s[m] - '0');
			if (outcome > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (outcome);
}

/**
 * print_error - to print error message
 * @info: parameter and return information structure
 * @estr: string with specified error type
 * Return: 0( no numbers in string, converted number otherwise) or -1(error)
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - func printing a decimal no. (base 10)
 * @input: input
 * @fd: filedescriptor to write to
 * Return: no. of char printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int m, counter = 0;
	unsigned int _abs_, cur;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	cur = _abs_;
	for (m = 1000000000; m > 1; m /= 10)
	{
		if (_abs_ / m)
		{
			__putchar('0' + cur / m);
			counter++;
		}
		cur %= m;
	}
	__putchar('0' + cur);
	counter++;

	return (counter);
}

/**
 * convert_number - conversion function, itoa's clone
 * @num: no.
 * @base: base
 * @flags: arg flags
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long h = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		h = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[h % base];
		h /= base;
	} while (h != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replacing first instance of '#' with '\0'
 * @buf: address of the string to be modified
 * Return: Always 0
 */

void remove_comments(char *buf)
{
	int m;

	for (m = 0; buf[m] != '\0'; m++)
		if (buf[m] == '#' && (!m || buf[m - 1] == ' '))
		{
			buf[m] = '\0';
			break;
		}
}
