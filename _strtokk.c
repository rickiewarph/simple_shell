#include <stdio.h>

void _strtok(const char *str, char delimt)
{
	int leng = strlen(str);
	char wrd[leng + 1];
	int m, n;

	for (m = 0; m <= leng; m++)
	{
		n = 0;
		if (str[m] == delimt || str[m] == '\0')
			wrd[n] = '\0';
		if (n > 0)
		{
			printf("%s\n", wrd);
			n = 0;
		}
		else
		{
			wrd[n++] = str[m];
			n++;
		}
	}
}
