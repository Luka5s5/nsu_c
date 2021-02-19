#include <stdio.h>
#define mx 255

// То же самое, что и problem1.c только без рекурсии
// (Вроде в таком контексте это называется итеративное решение, да?)

// Между прочим тоже O(n*m) по времени !!!!!

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int main()
{
    int n, m;
    scanf("%d%d", &m, &n);
    int a[mx][mx], dp[mx][mx];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
            dp[i][j] = a[i][j];
        }
    }

    //  заполняет дп над диагональю
    for (int dj = 1; dj < m; dj++)
    {
        for (int i = 0, j = dj; i < n && j < m; j++, i++)
        {
            if (j - 1 >= 0) // лишнее условие, но на всякий случай
                dp[i][j] = min(dp[i][j], dp[i][j - 1]);
            if (i + 1 < n)
                dp[i][j] = min(dp[i][j], dp[i + 1][j]);
        }
    }

    //  заполняет дп под диагональю
    for (int di = 1; di < n; di++)
    {
        for (int i = di, j = 0; i < n && j < m; j++, i++)
        {
            if (j + 1 < m)
                dp[i][j] = min(dp[i][j], dp[i][j + 1]);
            if (i - 1 >= 0) // тоже лишнее условие, тоже на всякий случай
                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans += (a[i][j] == dp[i][j]);

    printf("%d\n", ans);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            printf("%d%s", dp[i][j], (j == m - 1) ? "\n" : " ");
}