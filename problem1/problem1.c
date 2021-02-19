#include <stdio.h>
#define mx 255

// Между прочим O(n*m) по времени !!!!!

int min(int a, int b)
{
    return (a > b) ? b : a;
}

void fill_dp(int a[][mx], int dp[][mx], char used[][mx], int x, int y, int n, int m)
{
    used[x][y] = 1;
    int res = a[x][y];
    if (x == y)
        return;
    if (y > x)
    {
        if (y - 1 >= 0)
        {
            if (!used[x][y - 1])
                fill_dp(a, dp, used, x, y - 1, n, m);
            res = min(res, dp[x][y - 1]);
        }
        if (x + 1 < n)
        {
            if (!used[x + 1][y])
                fill_dp(a, dp, used, x + 1, y, n, m);
            res = min(res, dp[x + 1][y]);
        }
        dp[x][y] = res;
        // printf("Set dp %d %d to %d\n", x, y, res);
    }
    else
    {
        if (y + 1 < m)
        {
            if (!used[x][y + 1])
                fill_dp(a, dp, used, x, y + 1, n, m);
            res = min(res, dp[x][y + 1]);
        }
        if (x - 1 >= 0)
        {
            if (!used[x - 1][y])
                fill_dp(a, dp, used, x - 1, y, n, m);
            res = min(res, dp[x - 1][y]);
        }
        dp[x][y] = res;
    }
    return;
}

int main()
{
    int n, m;
    scanf("%d%d", &m, &n);
    int a[mx][mx], dp[mx][mx];
    char used[mx][mx];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
            if (i == j)
            {
                used[i][j] = 1;
                dp[i][j] = a[i][j];
            }
            else
            {
                used[i][j] = 0;
            }
        }
    }

    fill_dp(a, dp, used, n - 1, 0, n, m);
    fill_dp(a, dp, used, 0, m - 1, n, m);

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans += (a[i][j] == dp[i][j]);

    printf("%d\n", ans);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            printf("%d%s", dp[i][j], (j == m - 1) ? "\n" : " ");
}