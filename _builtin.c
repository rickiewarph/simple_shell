#include "shell.h"

/**
 * _myexit - function to exit shell
 * @info: Struct with potential arguments
 * Return: will exit with a particular exit status
 *         0(info.argv[0] != "exit")
 */

int _myexit(info_t *info)
{
	int xcheck;

	if (info->argv[1])
	{
		xcheck = _erratoi(info->argv[1]);
		if (xcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - function that changes current directory
 * @info: Struct with potential arguments
 * maintaining constant function prototype.
 *  Return: 0(Always)
 */

int _mycd(info_t *info)
{
	char *m, *dirt, buffer[1024];
	int chdir_ret;

	m = getcwd(buffer, 1024);
	if (!m)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirt = _getenv(info, "HOME=");
		if (!dirt)
			chdir_ret = chdir((dirt = _getenv(info, "PWD=")) ? dirt : "/");
		else
			chdir_ret = chdir(dirt);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(m);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dirt = _getenv(info, "OLDPWD=")) ? dirt : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - function that changes the current directory
 * @info: Struct with potential arguments
 * maintaining constant function prototype.
 * Return: 0(always)
 */

int _myhelp(info_t *info)
{
	char **ar_array;

	ar_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ar_array);
	return (0);
}

