#include "shell.h"

/**
 * bfree - function that frees pointer and NULLs address
 * @ptr: pointer address to free
 * Return: 1(freed) or 0(otherwise)
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
