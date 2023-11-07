#include <stdio.h>
#include <stdlib.h>

int main (int ac, char **av)
{
	int m;
	int add = 0;

	printf("argc or ac = %d\n", ac);
	printf("argv content is argv[]\n");

	for (m = 1; m < ac; m++)
	{
		printf("argv[%d] = %s\n", m, av[m]);
		add += atoi(av[m]);
	}
	printf("add is %d\n", add);
	return (0);
}
