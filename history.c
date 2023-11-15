#include "shell.h"

/**
 * get_history_file - function to fetch history file
 * @info: structure parameter
 * Return: allocated string with history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dirt;

	dirt = _getenv(info, "HOME=");
	if (!dirt)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dirt) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dirt);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - func creating a file or appending it to existing file
 * @info: structure parameter
 * Return: 1(success) or -1(fail)
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *nod = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nod = info->history; nod; nod = nod->next)
	{
		_putsfd(nod->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - func that reads history from file
 * @info: structure parameter
 * Return: histcount(success) or  0(otherwise)
 */

int read_history(info_t *info)
{
	int m, z = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (m = 0; m < fsize; m++)
		if (buf[m] == '\n')
		{
			buf[m] = 0;
			build_history_list(info, buf + z, linecount++);
			z = m + 1;
		}
	if (z != m)
		build_history_list(info, buf + z, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - func to sum entry to a history linked list
 * @info: struct with potential args
 * @buf: buffer
 * @linecount: history linecount
 * Return: Always 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nod = NULL;

	if (info->history)
		nod = info->history;
	add_node_end(&nod, buf, linecount);

	if (!info->history)
		info->history = nod;
	return (0);
}

/**
 * renumber_history - func to renumber history of linked list with the changes
 * @info: Struct with potential args
 * Return: new histcount
 */

int renumber_history(info_t *info)
{
	list_t *nod = info->history;
	int m = 0;

	while (nod)
	{
		nod->num = m++;
		nod = nod->next;
	}
	return (info->histcount = m);
}
