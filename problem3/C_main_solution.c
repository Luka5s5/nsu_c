#include <stdio.h>
#define N 100005
#define K 64

// Если бы массивы были динамическими то можно было бы наверное раскладывать по столбцу и свапать строки
// просто свапая указатели за O(1)
void swap_cols(int v[][K][K], int *sz, int mat_n, int r1, int r2)
{
	for (int i = 0; i < sz[mat_n]; i++)
	{
		int t = v[mat_n][i][r1];
		v[mat_n][i][r1] = v[mat_n][i][r2];
		v[mat_n][i][r2] = t;
	}
	return;
}

// Считает определитель подматрицы начинающейся в (offset, offset)
// (Пример offset=2)
// * * * * * * *
// * * * * * * *
// * * # # # # #
// * * # # # # # $\vdots$
// * * # # # # #
// * * # # # # #
// * * # # # # #
//    $\hdots$

long long determinant(int v[][K][K], int *sz, int mat_n, int offset)
{
	long long res = 0, n = sz[mat_n];
	int dim = n - offset;
	if (dim == 1)
		return v[mat_n][offset][offset];
	if (dim == 2)
		return v[mat_n][offset][offset] * v[mat_n][offset + 1][offset + 1] - v[mat_n][offset + 1][offset] * v[mat_n][offset][offset + 1];
	for (int j = offset; j < n; j++)
	{
		int sign = ((j == offset) ? 1 : -1); //из-за свапов и разложения знак не меняется после 2-ого столбца
		swap_cols(v, sz, mat_n, j, offset);
		long long t_res = determinant(v, sz, mat_n, offset + 1);
		res += v[mat_n][offset][offset] * sign * t_res;
		swap_cols(v, sz, mat_n, j, offset);
	}
	return res;
}

void swp(long long arr[][2], int i1, int i2)
{
	long long t1 = arr[i1][0], t2 = arr[i1][1];
	arr[i1][0] = arr[i2][0];
	arr[i1][1] = arr[i2][1];
	arr[i2][0] = t1;
	arr[i2][1] = t2;
}

void heap_push(long long arr[][2], int n, int i)
{
	while (1)
	{
		int l = i * 2 + 1, r = i * 2 + 2, mx = i;
		if (l < n && arr[mx][0] < arr[l][0])
			mx = l;
		if (r < n && arr[mx][0] < arr[r][0])
			mx = r;
		if (mx != i)
		{
			swp(arr, mx, i);
			i=mx;
		}
		else{
			return;
		}
	}
}

void heap_sort(long long arr[][2], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heap_push(arr, n, i);
	for (int i = n - 1; i > 0; i--)
	{
		swp(arr, 0, i);
		heap_push(arr, i, 0);
	}
}

int main()
{
	int v[N][K][K], n;
	int sz[N];
	long long det_ind[N][2];
	scanf("%lld", &n);
	for (int ind = 0; ind < n; ind++)
	{
		int k;
		scanf("%d", &k);
		sz[ind] = k;
		for (int i = 0; i < k; i++)
			for (int j = 0; j < k; j++)
				scanf("%d", &v[ind][i][j]);
		det_ind[ind][0] = determinant(v, sz, ind, 0);
		det_ind[ind][1] = ind;
	}
	heap_sort(det_ind, n);
	for (int ind = 0; ind < n; ind++)
	{
		int tind = det_ind[ind][1];
		for (int i = 0; i < sz[tind]; i++)
		{
			for (int j = 0; j < sz[tind]; j++)
			{
				printf("%d ", v[tind][i][j]);
			}
			printf("\n");
		}
	}
}
