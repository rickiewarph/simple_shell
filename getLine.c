#include "shell.h"

/**
 * input_buf - func to buffer the chained commands
 * @info: parameter structure
 * @buf: buffer address
 * @len: len var address
 * Return: amount bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t v = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		v = getline(buf, &len_p, stdin);
#else
		v = _getline(info, buf, &len_p);
#endif
		if (v > 0)
		{
			if ((*buf)[v - 1] == '\n')
			{
				(*buf)[v - 1] = '\0';
				v--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = v;
				info->cmd_buf = buf;
			}
		}
	}
	return (v);
}

/**
 * get_input - function to gets a line without the newline
 * @info: structure parameter
 * Return: amount of bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t m, n, len;
	ssize_t v = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	v = input_buf(info, &buf, &len);
	if (v == -1)
		return (-1);
	if (len)
	{
		n = m;
		p = buf + m;

		check_chain(info, buf, &n, m, len);
		while (n < len)
		{
			if (is_chain(info, buf, &n))
				break;
			n++;
		}

		m = n + 1;
		if (m >= len)
		{
			m = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (v);
}

/**
 * read_buf - func to reads a buffer
 * @info: structure parameter
 * @buf: buffer
 * @i: size
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t v = 0;

	if (*i)
		return (0);
	v = read(info->readfd, buf, READ_BUF_SIZE);
	if (v >= 0)
		*i = v;
	return (v);
}

/**
 * _getline - func to get next line of input from STDIN
 * @info: structure parameter
 * @ptr: pointer address to buffer, preallocated or NULL
 * @length: size of preallocated pointer buffer if not NULL
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t m, len;
	size_t k;
	ssize_t v = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (m == len)
		m = len = 0;

	v = read_buf(info, buf, &len);
	if (v == -1 || (v == 0 && len == 0))
		return (-1);

	c = _strchr(buf + m, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + m, k - m);
	else
		_strncpy(new_p, buf + m, k - m + 1);

	s += k - m;
	m = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - func to block ctrl-C
 * @sig_num: signal no.
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

