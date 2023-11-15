#include "shell.h"

/**
 **_memset - func to fill memory with a const byte
 *@s: points to the memory area
 *@b: byte to fill *s with
 *@n: amount of bytes to fill
 *Return: (s) a pointer to the memory area s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		s[m] = b;
	return (s);
}
/**
 * ffree - funct to free a string of strings
 * @pp: string of strings
 */

void ffree(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}

/**
 * _realloc - reallocation of of a memory block
 * @ptr: points to previous mallocated block
 * @old_size: size of byte of previous block
 * @new_size: sizeof byte of the new block
 * Return: points to nameen
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
