#include "shell.h"

/**
 * **strtow - func breaks string into words, ignoring repeat delimiters
 * @str: input string
 * @d: delimeter string
 * Return: a pointer to an array of strings, or NULL(failure)
 */

char **strtow(char *str, char *d)
{
	int p, q = 0;
	int k, m = 0;
	int nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (p = 0; str[p] != '\0'; p++)
		if (!is_delim(str[p], d) && (is_delim(str[p + 1], d) || !str[p + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (p = 0, q = 0; p < nw; q++)
	{
		while (is_delim(str[p], d))
			p++;
		k = 0;
		while (!is_delim(str[p + k], d) && str[p + k])
			k++;
		s[q] = malloc((k + 1) * sizeof(char));
		if (!s[q])
		{
			for (k = 0; k < q; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[q][m] = str[p++];
		s[q][m] = 0;
	}
	s[q] = NULL;
	return (s);
}

/**
 * **strtow2 - func breaks a string into words
 * @str: input string
 * @d: delimeter
 * Return: a pointer to an array of strings, or NULL(failure)
 */

char **strtow2(char *str, char d)
{
	int p = 0;
	int q = 0;
	int k = 0;
	int m = 0;
	int nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (p = 0; str[p] != '\0'; p++)
		if ((str[p] != d && str[p + 1] == d) ||
		    (str[p] != d && !str[p + 1]) || str[p + 1] == d)
			nw++;
	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (p = 0, q = 0; q < nw; q++)
	{
		while (str[p] == d && str[p] != d)
			p++;
		k = 0;
		while (str[p + k] != d && str[p + k] && str[p + k] != d)
			k++;
		s[q] = malloc((k + 1) * sizeof(char));
		if (!s[q])
		{
			for (k = 0; k < q; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[q][m] = str[p++];
		s[q][m] = 0;
	}
	s[q] = NULL;
	return (s);
}
