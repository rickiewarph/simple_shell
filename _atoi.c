#include "shell.h"

/**
 * interactive - to return true where shell is interactive mode
 * @info: address of struct
 * Return: 1(interactive mode) or 0(otherwise)
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - to check if a char is a delimeter
 * @c: character to be checked
 * @delim: delimeter string
 * Return: 1(true) or  0(false)
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - to check for an alphabetic char
 *@c: char to input
 *Return: 1(alphabet) or 0(otherwise)
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - function to convert a string to an int
 *@s: the string that should be converted
 *Return: 0(no numbers in string) or converted number(otherwise)
 */

int _atoi(char *s)
{
	int m, sign = 1, flag = 0, put;
	unsigned int result = 0;

	for (m = 0;  s[m] != '\0' && flag != 2; m++)
	{
		if (s[m] == '-')
			sign *= -1;

		if (s[m] >= '0' && s[m] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[m] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		put = -result;
	else
		put = result;

	return (put);
}
