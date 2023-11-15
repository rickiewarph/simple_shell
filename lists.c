#include "shell.h"

/**
 * add_node - func to add a node to start of the list
 * @head: pointer address to head node
 * @str: string field of node
 * @num: index used by history
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *x_head;

	if (!head)
		return (NULL);
	x_head = malloc(sizeof(list_t));
	if (!x_head)
		return (NULL);
	_memset((void *)x_head, 0, sizeof(list_t));
	x_head->num = num;
	if (str)
	{
		x_head->str = _strdup(str);
		if (!x_head->str)
		{
			free(x_head);
			return (NULL);
		}
	}
	x_head->next = *head;
	*head = x_head;
	return (x_head);
}

/**
 * add_node_end - func to add a node to end of the list
 * @head: pointer address to head node
 * @str: string field of node
 * @num: index used by history
 * Return: size of list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *x_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	x_node = malloc(sizeof(list_t));
	if (!x_node)
		return (NULL);
	_memset((void *)x_node, 0, sizeof(list_t));
	x_node->num = num;
	if (str)
	{
		x_node->str = _strdup(str);
		if (!x_node->str)
		{
			free(x_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = x_node;
	}
	else
		*head = x_node;
	return (x_node);
}

/**
 * print_list_str - funct to only print string element of a list_t linked list
 * @h: points to the first node
 * Return: size of list
 */

size_t print_list_str(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * delete_node_at_index - func to delete node at a particular index
 * @head: pointer address to first node
 * @index: index of node to be deleted
 * Return: 1(success) or 0(fail)
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *y_node;
	unsigned int m = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (m == index)
		{
			y_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		m++;
		y_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - func to free all nodes of a list
 * @head_ptr: pointer address to head node
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

