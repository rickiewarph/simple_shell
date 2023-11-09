#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char str[] = "separates words using spaces and writes the words on a new line";
	char delim[] = " ";
	char *trunx;

	trunx = strtok(str, delim);
	printf("%p\n %p\n", str, trunx);

	while (trunx != NULL)
	{
		printf("%s\n", trunx);
		trunx = strtok(NULL, delim);
	}
	return (0);
}
