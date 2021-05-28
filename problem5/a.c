// #include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
const int INF = 1000000000;
// using namespace std;

//+=+=+=+=+= SET +=+=+=+=+=

typedef struct node node;
typedef struct Pair Pair;
typedef struct pair pair;
struct pair
{
    int first, second;
};

int paircmp(pair a, pair b)
{
    if (a.first < b.first || (a.first == b.first && a.second < b.second))
        return 1;
    if (a.first == b.first && a.second == b.second)
        return 0;
    return -1;
}

struct node
{
    int prior;
    pair val;
    node *l, *r;
};

struct Pair
{
    node *first;
    node *second;
};

int check(node *t, pair s)
{
    if (!t)
        return 0;
    int res = paircmp(s, t->val);
    if (res == 0)
        return 1;
    if (res < 0)
        return check(t->l, s);
    else
        return check(t->r, s);
}

Pair *make_pair(node *f, node *s)
{
    Pair *ret = (Pair *)malloc(sizeof(Pair));
    if (!ret)
    {
        printf("No memory for a pair\n");
        exit(0);
    }
    ret->first = f;
    ret->second = s;
    return ret;
}

node *make_node(pair s)
{
    node *ret = (node *)malloc(sizeof(node));
    if (!ret)
    {
        printf("No memory for a node\n");
        exit(0);
    }
    ret->l = ret->r = NULL;
    ret->val = s;
    ret->prior = rand();
    return ret;
}

node *merge(node *l, node *r)
{
    if (!l)
        return r;
    if (!r)
        return l;
    if (l->prior > r->prior)
    {
        l->r = merge(l->r, r);
        return l;
    }
    else
    {
        r->l = merge(l, r->l);
        return r;
    }
}

Pair *split(node *t, pair s)
{
    if (!t)
        return make_pair(NULL, NULL);
    int res = paircmp(t->val, s);
    if (res <= 0)
    {
        Pair *q = split(t->r, s);
        t->r = q->first;
        Pair *ret = make_pair(t, q->second);
        free(q);
        return ret;
    }
    else
    {
        Pair *q = split(t->l, s);
        t->l = q->second;
        Pair *ret = make_pair(q->first, t);
        free(q);
        return ret;
    }
}

node *insert(node *t, node *in)
{
    if (!t)
        return in;
    if (check(t, in->val))
    {
        free(in);
        return t;
    };
    Pair *p = split(t, in->val);
    node *ret = merge(p->first, merge(in, p->second));
    free(p);
    return ret;
}

node *remove_by_s(node *t, pair s)
{
    if (!t)
        return t;
    if (!check(t, s))
        return t;
    int res = paircmp(s, t->val);
    if (res < 0)
    {
        t->l = remove_by_s(t->l, s);
        return t;
    }
    if (res > 0)
    {
        t->r = remove_by_s(t->r, s);
        return t;
    }
    if (res == 0)
    {
        node *tmp1 = t->l, *tmp2 = t->r;
        // free(t->s);
        free(t);
        return merge(tmp1, tmp2);
    }
}

void free_all(node *t)
{
    if (!t)
        return;
    free_all(t->l);
    free_all(t->r);
    // free(t->s);
    free(t);
}

// void write_level(node *t, int nowl, int needl)
// {
//     if (!t)
//         return;
//     write_level(t->l, nowl + 1, needl);
//     if (nowl == needl)
//     {
//         printf("%s ", t->val.);
//     }
//     write_level(t->r, nowl + 1, needl);
// }

#define COUNT 10
void writee(node *t, int space)
{
    if (t == NULL)
        return;
    space += COUNT;
    writee(t->r, space);
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("'%d %d' prior:%x\n", t->val.first, t->val.second, t->prior);
    writee(t->l, space);
}

void write(node *root)
{
    writee(root, 0);
}

int sz_O_n(node *t)
{
    if (!t)
        return 0;
    return 1 + sz_O_n(t->l) + sz_O_n(t->r);
}

node *leftmost(node *t)
{
    if (!t)
        return NULL;
    if (t->l)
        return leftmost(t->l);
    return t;
}

//+=+=+=+=+=+ /SET +=+=+=+=+=+=+

pair make_int_pair(int a, int b)
{
    pair p;
    p.first = a;
    p.second = b;
    return p;
}

int max(int a, int b)
{
    return ((a > b) ? a : b);
}

int main()
{
    int ans = -INF;
    int mx, n, m;
    scanf("%d %d %d", &mx, &n, &m);
    //g - граф, задан списком смежности, .first - вес ребра, .second - куда ребро
    pair **g = (pair **)malloc(n * sizeof(pair *));
    if (!g)
        return -1;
    // .first - сколько выделено памяти .second - текущая длинна
    pair *sz_ind = (pair *)malloc(n * sizeof(pair));
    if (!sz_ind)
        return -1;
    for (int i = 0; i < n; i++)
    {
        g[i] = (pair *)malloc(sizeof(pair));
        if(!g[i])
            return -1;
        sz_ind[i].first = 1;
        sz_ind[i].second = 0;
    }
    // Сколько деняг в вершине
    int *val = (int *)malloc(n * sizeof(int));
    if (!val)
        return -1;
    for (int i = 0; i < m; i++)
    {
        int v, u, c;
        scanf("%d %d %d", &v, &u, &c);
        if (sz_ind[v].first <= sz_ind[v].second)
        {
            g[v] = (pair *)realloc(g[v], sizeof(pair) * (sz_ind[v].first *= 2));
            if (!g[v])
                return -1;
        }
        if (sz_ind[u].first <= sz_ind[u].second)
        {
            g[u] = (pair *)realloc(g[u], sizeof(pair) * (sz_ind[u].first *= 2));
            if (!g[u])
                return -1;
        }
        g[v][sz_ind[v].second].first = c;
        g[v][sz_ind[v].second++].second = u;
        g[u][sz_ind[u].second].first = c;
        g[u][sz_ind[u].second++].second = v;
    }
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);
    int s = 0;
    // d[i] - расстояние от стартовой вершины до i-той, p[i] - предок i-той вершины в кратчайшем пути
    int *d = (int *)malloc(n * sizeof(int)), *p = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        d[i] = INF;
    d[s] = 0;
    // q - priority_queue
    node *q = NULL;
    q = insert(q, make_node(make_int_pair(d[s], s)));
    int qsz = 1;
    while (qsz)
    {
        node *mn = leftmost(q);
        int v = mn->val.second;
        q = remove_by_s(q, mn->val);
        qsz--;
        for (int j = 0; j < sz_ind[v].second; ++j)
        {
            int to = g[v][j].second,
                len = g[v][j].first;
            if (d[v] + len < d[to])
            {
                if (check(q, make_int_pair(d[to], to)))
                    qsz--;
                q = remove_by_s(q, make_int_pair(d[to], to));
                d[to] = d[v] + len;
                p[to] = v;
                q = insert(q, make_node(make_int_pair(d[to], to)));
                qsz++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (d[i] <= mx)
            ans = max(ans, val[i]);
    }
    printf("%d\n", ans);
    free_all(q);
    for (int i = 0; i < n; i++)
        free(g[i]);
    free(g);
    free(sz_ind);
    free(val);
    free(d);
    free(p);
}
