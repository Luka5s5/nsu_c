#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BIN 123
#define PY 123423
#define TXT 1739
#define C 823

double min(double a, double b)
{
	return (a > b) ? b : a;
}

double max(double a, double b)
{
	return (a > b) ? a : b;
}

int get_type(char *s)
{
	int n = strlen(s);
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '.')
		{
			if (i + 2 < n && s[i + 1] == 'p' && s[i + 2] == 'y')
				return PY;
			if (i + 3 < n && s[i + 1] == 't' && s[i + 2] == 'x' && s[i + 3] == 't')
				return TXT;
			if ((i + 1 < n && s[i + 1] == 'c') || (i + 3 < n && s[i + 1] == 'c' && s[i + 2] == 'p' && s[i + 3] == 'p'))
				return C;
			break;
		}
	}
	return BIN;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Usage: ./test [solution binary] [test generator (binary/.py/.c/.cpp/.txt)] [number of iterations]\n");
		return 'a' + 'r' + 'g' + 'c';
	}
	char *sol = argv[1], *gen = argv[2];
	int type = get_type(gen), iters = atoi(argv[3]);
	printf("Generating input...\n");
	if (type == BIN)
	{
		char command[1024];
		sprintf(command, "./%s > input.txt", gen);
		system(command);
	}
	if (type == C)
	{
		char command[1024];
		sprintf(command, "g++ %s -o gen; ./gen > input.txt; rm gen;", gen);
		system(command);
	}
	if (type == PY)
	{
		char command[1024];
		sprintf(command, "python3 %s > input.txt", gen);
		system(command);
	}
	if (type == TXT)
	{
		char command[1024];
		sprintf(command, "cp %s input.txt", gen);
		system(command);
	}
	printf("Generated input!\n");
	double *t = (double *)malloc(sizeof(double) * iters);
	double mean = 0;
	if (!t)
		return 'm' + 'l';
	for (int i = 0; i < iters; i++)
	{
		printf("running test %d...\n", i+1);
		char command[1024];
		sprintf(command, "(/usr/bin/time -f \"%%e\" ./%s < input.txt > output.txt) 2> time.txt", sol);
		system(command);
		FILE *t_file = fopen("time.txt", "r");
		fscanf(t_file, "%lf", &t[i]);
		fclose(t_file);
		mean += t[i];
	}
	system("rm time.txt");
	mean /= iters;
	for (int i = 0; i < iters; i++)
	{
		printf("run %d, time %lfs\n", i + 1, t[i]);
	}
	double sd = 0, mn = t[0], mx = t[0];
	for (int i = 0; i < iters; i++)
	{
		sd += (t[i] - mean) * (t[i] - mean);
		mn = min(t[i], mn);
		mx = max(t[i], mx);
	}
	printf("Uncorrected SD: %lf, corrected SD: %lf\n", sqrt(sd / iters), sqrt(sd / (iters - 1)));
	printf("Max time: %lf, min time: %lf\n", mx, mn);
	free(t);
}
