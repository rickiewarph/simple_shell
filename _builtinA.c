#include "shell.h"

/**
 * _myhistory - function to display history list
 * @info: Struct with potential args maintaining constant function prototype
 *  Return: 0(always)
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - function to set alias to string
 * @info: parameter structucture
 * @str: string alias
 * Return: 0(success) or  1(fail)
 */

int unset_alias(info_t *info, char *str)
{
	char *b, s;
	int ret;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	s = *b;
	*b = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = s;
	return (ret);
}

/**
 * set_alias - function that sets alias to string
 * @info: parameter structucture
 * @str: string alias
 * Return: Always 0(success) or  1(fail)
 */

int set_alias(info_t *info, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - function printing an alias string
 * @node: the alias node
 * Return: Always 0(success) or 1(failure)
 */

int print_alias(list_t *node)
{
	char *b = NULL, *z = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (z = node->str; z <= b; z++)
			_putchar(*z);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - function to mimic the alias builtin
 * @info: Struct with potential arguments maintaining
 * constant function prototype
 * Return: 0(always)
 */

int _myalias(info_t *info)
{
	int j = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		b = _strchr(info->argv[j], '=');
		if (b)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}

