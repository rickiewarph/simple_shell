#include "shell.h"

/**
 * get_environ - func to return string array copy of the environ
 * @info: Struct with potential args maintaining
 * constant function prototype
 * Return: Always 0
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - func removes an envirn variable
 * @info: Struct with potential args maintaining
 * constant function prototype
 * Return: 1(delete) or 0(otherwise)
 * @var: string env variable property
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *nod = info->env;
	size_t m = 0;
	char *q;

	if (!nod || !var)
		return (0);

	while (nod)
	{
		q = starts_with(nod->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), m);
			m = 0;
			nod = info->env;
			continue;
		}
		nod = nod->next;
		m++;
	}
	return (info->env_changed);
}

/**
 * _setenv - to nitialize a new environ
 * variable or modify an existing one
 * @info: struct with potential args maintaining
 * constant function prototype
 * @var: string environ variable property
 * @value: string environ variable value
 *  Return: Always 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *nod;
	char *q;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	nod = info->env;
	while (nod)
	{
		q = starts_with(nod->str, var);
		if (q && *q == '=')
		{
			free(nod->str);
			nod->str = buf;
			info->env_changed = 1;
			return (0);
		}
		nod = nod->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

