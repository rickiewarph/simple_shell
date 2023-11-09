#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	size_t m = 0;
	char *buffer = NULL;

	printf("$ ");
	getline(&buffer, &m, stdin);
	printf("%s", buffer);
	printf("Buffer size: %ld/n", m);

	free(buffer);
	return (0);
}
