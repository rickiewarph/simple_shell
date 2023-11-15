#include "shell.h"

/**
 * is_chain - func to test if current char
 * in buffer is a chain delimeter
 * @info: parameter structure
 * @buf: char buffer
 * @p: address of the current position in buf
 * Return: 1(chain delimeter) or 0(otherwise)
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t n = *p;

	if (buf[n] == '|' && buf[n + 1] == '|')
	{
		buf[n] = 0;
		n++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[n] == '&' && buf[n + 1] == '&')
	{
		buf[n] = 0;
		n++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[n] == ';')
	{
		buf[n] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = n;
	return (1);
}

/**
 * check_chain - func to check if to continue chaining
 * on the basis of the last status
 * @info: parameter structure
 * @buf: char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: buf length
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t n = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[n] = 0;
			n = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			n = len;
		}
	}

	*p = n;
}

/**
 * replace_alias - replaceing an aliases
 * @info: parameter structure
 * Return: 1(replaced) or 0(otherwise)
 */

int replace_alias(info_t *info)
{
	int m;
	list_t *nod;
	char *q;

	for (m = 0; m < 10; m++)
	{
		nod = node_starts_with(info->alias, info->argv[0], '=');
		if (!nod)
			return (0);
		free(info->argv[0]);
		q = _strchr(nod->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * replace_vars - func to replace variables
 * @info: parameter structure
 * Return: 1(replaced) or 0(otherwise)
 */

int replace_vars(info_t *info)
{
	int m = 0;
	list_t *nod;

	for (m = 0; info->argv[m]; m++)
	{
		if (info->argv[m][0] != '$' || !info->argv[m][1])
			continue;

		if (!_strcmp(info->argv[m], "$?"))
		{
			replace_string(&(info->argv[m]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[m], "$$"))
		{
			replace_string(&(info->argv[m]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nod = node_starts_with(info->env, &info->argv[m][1], '=');
		if (nod)
		{
			replace_string(&(info->argv[m]),
				_strdup(_strchr(nod->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[m], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - func to replace a string
 * @old: address of previous string
 * @new: new string
 * Return: 1(replaced) or 0(otherwise)
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
