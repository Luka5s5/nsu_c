#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#define MXRE 64
#define MXS 1024
#define MXNUMLEN 10

#define bool int

int chars_in_re(char *re, int lre, int rre)
{
	int escs = 0;
	int length = rre - lre;
	for (int i = lre; i < rre; i++)
		escs += (re[i] == '\\');
	return length - escs;
}

// Наверное, стоило как-то выделить парсер отдельно но тут вроде всё +-просто парсится
// Все кусочки - полуинтервалы [lt, rt), [lre,rre)
bool is_match(char *t, char *re, int lt, int rt, int lre, int rre)
{
	if (lre > rre)
		return 0;
	//<...>*
	if (re[lre] == '<')
	{
		int left = lre, right = lre;
		while (re[++right] != '>')
			;
		int letters = chars_in_re(re, left + 1, right);
		int letters_left = rt - lt;
		bool pref_matching = 1;
		if (is_match(t, re, lt, rt, right + 2, rre))
			return 1;
		for (int step = 0; step < letters_left / letters; step++)
		{
			pref_matching &= is_match(t, re, lt + step * letters, lt + (step + 1) * letters, left + 1, right);
			if (!pref_matching)
				return 0;
			if (is_match(t, re, lt + (step + 1) * letters, rt, right + 2, rre))
				return 1;
		}
		return 0;
	}

	// \d \D или просто символ

	while (re[lre] == '\\' || isdigit(re[lre]) || isalpha(re[lre]))
	{
		if (lt == rt)
			return (lre == rre);
		if (lre > rre)
			return 0;
		if (re[lre] == '\\')
		{
			assert(!(lre + 1 >= rre));
			assert(!(re[lre + 1] != 'd' && re[lre + 1] != 'D'));

			if ((re[lre + 1] == 'd' && !isdigit(t[lt])) || (re[lre + 1] == 'D' && !isalpha(t[lt])))
				return 0;
			lt += 1;
			lre += 2;
		}
		else
		{ //(isdigit(re[lre]) || isalpha(re[lre]))
			if (re[lre] != t[lt])
				return 0;
			lt += 1;
			lre += 1;
		}
	}
	// за 30 минут не придумал как избавиться от етой копипасты(( вроде как надо действительно после каждой итерации
	// и после завершения тоже чекать что не закончилось ни выражение, ни строка.
	if (lt == rt)
		return (lre == rre);
	if (lre > rre)
		return 0;

	// return is_match(t, re, lt, rt, lre, rre);
	if (re[lre] == '~')
	{
		if (re[lre + 1] != t[lt])
		{
			return is_match(t, re, lt + 1, rt, lre + 2, rre);
		}
		else
			return 0;
	}
	if (re[lre] == '[')
	{
		int n = 0;
		int last = lre;
		while (isdigit(re[++last]))
			;
		for (int i = last - 1, pw = 1; i > lre; i--, pw *= 10)
			n += pw * (re[i] - '0');
		int lbracket = last + 1;
		int rbracket = lbracket;
		int escs = 0;
		while (re[++rbracket] != ')')
			escs += (re[rbracket] == '\\');
		int letters = (rbracket - lbracket - 1) - escs;
		bool ans = 1;
		if (rt - lt < letters * n)
			return 0;

		for (int i = 0; i < n; i++)
		{
			ans &= is_match(t, re, lt + i * letters, lt + (i + 1) * letters, lbracket + 1, rbracket);
		}

		if (!ans)
			return 0;
		return is_match(t, re, lt + (n)*letters, rt, rbracket + 2, rre);
	}
}

int main()
{
	char re[MXRE], s[MXS];
	int t, n, m;
	scanf("%s", re);
	n = strlen(re);
	scanf("%d", &t);

	bool any = 0;
	for (int i = 0; i < t; i++)
	{
		scanf("%s", s);
		m = strlen(s);
		bool ans = is_match(s, re, 0, m, 0, n);
		if (ans)
			printf("%d ", i);
		any |= ans;
	}

	if (!any)
		printf("none");
}
