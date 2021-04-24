#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BIN 123
#define PY 123423
#define TXT 1739
#define C 823
#define MX_LEN 1024

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

void gen_inp(char *gen, char *fname, int type)
{
	printf("Generating input...\n");
	if (type == BIN)
	{
		char command[MX_LEN];
		sprintf(command, "./%s > %s", gen, fname);
		system(command);
	}
	if (type == C)
	{
		char command[MX_LEN];
		sprintf(command, "g++ %s -o gen; ./gen > %s; rm gen;", gen, fname);
		system(command);
	}
	if (type == PY)
	{
		char command[MX_LEN];
		sprintf(command, "python3 %s > %s", gen, fname);
		system(command);
	}
	if (type == TXT)
	{
		char command[MX_LEN];
		sprintf(command, "cp %s %s", gen, fname);
		system(command);
	}
	printf("Generated input!\n");
}

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		printf("Usage: ./test [solution binary] [test generator (binary/.py/.c/.cpp/.txt)] [number of iterations] [mode]\n");
		return 'a' + 'r' + 'g' + 'c';
	}
	char *sol = argv[1], *gen = argv[2];
	int type = get_type(gen), iters = atoi(argv[3]), mode = atoi(argv[4]);
	if (mode == 0)
	{
		char *fname = "input.txt";
		gen_inp(gen, fname, type);
		double *t = (double *)malloc(sizeof(double) * iters);
		char *res = (char *)malloc(iters);

		if (!t || !res)
			return 'm' + 'l';

		double mean = 0;
		for (int i = 0; i < iters; i++)
		{
			printf("running test %d...\n", i + 1);
			char command[MX_LEN];
			sprintf(command, "(/usr/bin/time -f \"%%e\" ./%s < input.txt > output.txt) 2> time.txt", sol);
			system(command);
			system("python3 good_checker.py output.txt > res.txt");
			system("rm output.txt");
			FILE *temp = fopen("res.txt", "r");
			if (!temp)
				return 'f' + 'e';
			fscanf(temp, "%d", &res[i]);
			fclose(temp);
			FILE *t_file = fopen("time.txt", "r");
			if (!t_file)
				return 'f' + 'e';
			fscanf(t_file, "%lf", &t[i]);
			fclose(t_file);
			mean += t[i];
		}
		system("rm time.txt; rm res.txt");
		mean /= iters;
		for (int i = 0; i < iters; i++)
		{
			printf("run %d, time %lfs, %s\n", i + 1, t[i], (res[i] > 0) ? "AC" : "WA");
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
		free(res);
	}
	else
	{
		printf("Starting the max/min part\n");
		double *sds = (double *)malloc(sizeof(double) * iters);
		double *means = (double *)malloc(sizeof(double) * iters);
		if (!sds || !means)
			return 'm' + 'l';
		for (int i = 0; i < iters; i++)
		{
			char iname[MX_LEN], oname[MX_LEN];
			sprintf(iname, "input%d.txt", i);
			sprintf(oname, "output%d.txt", i);
			gen_inp(gen, iname, type);
			double *t = (double *)malloc(sizeof(double) * mode);
			if (!t)
				return 'm' + 'l';
			system("rm time.txt > /dev/null 2>&1;");
			for (int j = 0; j < mode; j++)
			{
				printf("running gen %d test run %d...\n", i, j);
				char command[MX_LEN];
				sprintf(command, "(/usr/bin/time -f \"%%e\" ./%s < input%d.txt > output%d.txt) 2>> time.txt", sol, i, i);
				system(command);
			}
			FILE *t_file = fopen("time.txt", "r");
			if (!t_file)
				return 'f' + 'e';
			double mean = 0, sd = 0;
			for (int j = 0; j < mode; j++)
			{
				fscanf(t_file, "%lf", &t[j]);
				printf("run %d %d, time %lfs\n", i, j, t[j]);
				mean += t[j];
			}
			mean /= mode;
			for (int j = 0; j < mode; j++)
				sd += (t[i] - mean) * (t[i] - mean);
			means[i] = mean;
			sds[i] = sqrt(sd / (mode > 1 ? (mode - 1) : 1)); // corrected
			fclose(t_file);
			free(t);
		}
		int mxmean = 0, mnmean = 0, mxsd = 0, mnsd = 0;
		for (int i = 1; i < iters; i++)
		{
			if (means[mxmean] < means[i])
				mxmean = i;
			if (means[mnmean] > means[i])
				mnmean = i;
			if (sds[mxsd] < sds[i])
				mxsd = i;
			if (sds[mnsd] > sds[i])
				mnsd = i;
		}
		for (int i = 0; i < iters; i++)
		{
			char command[MX_LEN];
			// sprintf(command, "rm output%d.txt", i);
			system(command);
			sprintf(command, "rm input%d.txt", i);
			if (i != mxmean && i != mnmean && i != mxsd && i != mnsd)
			{
				system(command);
			}
		}
		printf("mxsd: %d = %lf,mnsd: %d = %lf,mxmean: %d = %lf,mnmean: %d = %lf\n", mxsd, sds[mxsd], mnsd, sds[mnsd], mxmean, means[mxmean], mnmean, means[mnmean]);
		free(sds);
		free(means);
	}
}
