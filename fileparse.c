#include "shell.h"

/**
 * is_cmd - determination if a file can be executed
 * @info: structure information
 * @path: file path
 * Return: 1(if true) or 0(otherwise)
 */

int is_cmd(info_t *info, char *path)
{
	struct stat state;

	(void)info;
	if (!path || stat(path, &state))
		return (0);

	if (state.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplication of characters
 * @pathstr: string path
 * @start: starting index
 * @stop: stopping index
 * Return: points to new buffer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int m = 0, n = 0;

	for (n = 0, m = start; m < stop; m++)
		if (pathstr[m] != ':')
			buf[n++] = pathstr[m];
	buf[n] = 0;
	return (buf);
}

/**
 * find_path - func locates this cmd in string PATH
 * @info: info structure
 * @pathstr: the PATH string
 * @cmd: the cmd to locate
 * Return: full path of cmd when found or NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int m = 0, x_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[m] || pathstr[m] == ':')
		{
			path = dup_chars(pathstr, x_position, m);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[m])
				break;
			x_position = m;
		}
		m++;
	}
	return (NULL);
}
