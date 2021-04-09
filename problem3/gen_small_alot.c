#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	srand(time(NULL));
	int t = 100000/2;
	printf("%d\n", t);
	for (int tt = 0; tt < t; tt++)
	{
		int sz = 1 + rand() % 5;
		printf("%d\n", sz);
		for (int i = 0; i < sz; i++)
		{
			for (int j = 0; j < sz; j++)
				printf("%d ", -2 + rand() % 5);
			printf("\n");
		}
	}
	return 0;
}
