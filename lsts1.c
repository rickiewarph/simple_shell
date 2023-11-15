#include "shell.h"

/**
 * list_len - func to determine len of linked list
 * @h: points to first node
 * Return: size of list
 */

size_t list_len(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * list_to_strings -func to return array of strings of the list->str
 * @head: points to first node
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *nod = head;
	size_t m = list_len(head), n;
	char **strs;
	char *str;

	if (!head || !m)
		return (NULL);
	strs = malloc(sizeof(char *) * (m + 1));
	if (!strs)
		return (NULL);
	for (m = 0; nod; nod = nod->next, m++)
	{
		str = malloc(_strlen(nod->str) + 1);
		if (!str)
		{
			for (n = 0; n < m; n++)
				free(strs[n]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, nod->str);
		strs[m] = str;
	}
	strs[m] = NULL;
	return (strs);
}


/**
 * print_list - func printig all elements of a list_t linked list
 * @h: points to first node
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * node_starts_with - func returning a node with string starting with prefix
 * @node: points to list head
 * @prefix: string to match
 * @c: the next char after prefix to match
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *b = NULL;

	while (node)
	{
		b = starts_with(node->str, prefix);
		if (b && ((c == -1) || (*b == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - func to fetch index of a node
 * @head: points to list head
 * @node: points to the node
 * Return: node index or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t m = 0;

	while (head)
	{
		if (head == node)
			return (m);
		head = head->next;
		m++;
	}
	return (-1);
}

