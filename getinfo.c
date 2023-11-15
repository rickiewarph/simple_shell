#include "shell.h"

/**
 * clear_info - program to initialize info_t struct
 * @info: address of the structure
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - program initialize info_t struct
 * @info: address of structure
 * @av: arg vector
 */

void set_info(info_t *info, char **av)
{
	int m = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (m = 0; info->argv && info->argv[m]; m++)
			;
		info->argc = m;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - progrm to free info_t struct fields
 * @info: address of structure
 * @all: true(free all fields)
 */

void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

