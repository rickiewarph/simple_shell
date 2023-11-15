#include "shell.h"

/**
 * hsh -  the shell's main loop
 * @info: par & return info structure
 * @av: arg vector from main()
 * Return: 0(success) or 1(error or error code)
 */

int hsh(info_t *info, char **av)
{
	ssize_t v = 0;
	int builtin_return = 0;

	while (v != -1 && builtin_return != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		v = get_input(info);
		if (v != -1)
		{
			set_info(info, av);
			builtin_return = find_builtin(info);
			if (builtin_return == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_return);
}

/**
 * find_builtin - func to locate builtin command
 * @info: parameter and return info structure
 * Return: -1(not found), 0(executed successfully)
 * 1(found but not successful) -2(builtin signals exit())
 */

int find_builtin(info_t *info)
{
	int m, built_in_return = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (m = 0; builtintbl[m].type; m++)
		if (_strcmp(info->argv[0], builtintbl[m].type) == 0)
		{
			info->line_count++;
			built_in_return = builtintbl[m].func(info);
			break;
		}
	return (built_in_return);
}

/**
 * find_cmd - func to locate a command in PATH
 * @info: parameter and return info structure
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int m, n;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (m = 0, n = 0; info->arg[m]; m++)
		if (!is_delim(info->arg[m], " \t\n"))
			n++;
	if (!n)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - func to fork an executable thread to run cmd
 * @info: par and return info structure
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
