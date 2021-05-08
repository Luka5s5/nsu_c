#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define K 269
#define TRASH 20

typedef struct node node;

// unsigned long long get_hash(char *s)
// {
//     int n = strlen(s);
//     unsigned long long h = 0;
//     for (int i = n - 1; i >= 0; i--)
//     {
//         int x = (int)(s[i] + 1);
//         h = (h * K + x);
//     }
//     return h;
// }

struct node
{
    char *s;
    node *l, *r;
};

node *make_node(char *s)
{
    node *ret = (node *)malloc(sizeof(node));
    if (!ret)
    {
        printf("No memory for a node\n");
        exit(0);
    }
    ret->l = ret->r = NULL;
    ret->s = s;
    return ret;
}

void free_all(node *t)
{
    if (!t)
        return;
    free_all(t->l);
    free_all(t->r);
    free(t);
}

node *push_node(node *t, node *p)
{
    if (!t)
    {
        return p;
    }
    int res = strcmp(p->s, t->s);
    if (res == 0)
    {
        free_all(p);
        return t;
    }
    if (res < 0)
    {
        t->l = push_node(t->l, p);
        return t;
    }
    else
    {
        t->r = push_node(t->r, p);
        return t;
    }
}

node *leftmost(node *t)
{
    if (!t)
        return NULL;
    if (t->l)
        return leftmost(t->l);
    return t;
}

node *deleteNode(node *t, char *key)
{
    if (t == NULL)
        return t;
    int res = strcmp(key, t->s);
    if (res < 0)
        t->l = deleteNode(t->l, key);
    else if (res > 0)
        t->r = deleteNode(t->r, key);
    else
    {
        if (!t->l && !t->r)
        {
            free(t);
            return NULL;
        }
        else if (!t->l)
        {
            node *temp = t->r;
            free(t);
            return temp;
        }
        else if (!t->r)
        {
            node *temp = t->l;
            free(t);
            return temp;
        }
        node *temp = leftmost(t->r);
        t->s = temp->s;
        t->r = deleteNode(t->r, temp->s);
    }
    return t;
}

void write_level(node *t, int nowl, int needl)
{
    if (!t)
        return;
    write_level(t->l, nowl + 1, needl);
    if (nowl == needl)
    {
        printf("%s ", t->s);
    }
    write_level(t->r, nowl + 1, needl);
}

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
    printf("%s addr:%x\n", t->s, t);
    writee(t->l, space);
}
void write(node *root)
{
    writee(root, 0);
}

// Я хотел поддерживать размеры поддеревьев, но мне стало лень....
// из-за случаев когда добавляют то что есть и убирают то чего нет
int sz_O_n(node *t)
{
    if (!t)
        return 0;
    return 1 + sz_O_n(t->l) + sz_O_n(t->r);
}

int main()
{
    char trash[TRASH];
    scanf("%s\n", trash);
    node *tree = NULL;
    char **arr = (char **)malloc(1 * sizeof(char *));
    int maxarr = 1, arrsz = 0;
    for (;;)
    {
        if (arrsz >= maxarr)
        {
            maxarr *= 2;
            arr = (char **)realloc(arr, maxarr * sizeof(char *));
            if (!arr)
                return -1;
        }
        arr[arrsz] = (char *)malloc(1 * sizeof(char));
        int i = arrsz++;
        int sz = 0, mx = 1;
        char ch = getchar();
        while (ch != ' ' && ch != '\n')
        {
            if (sz >= mx)
            {
                mx *= 2;
                arr[i] = (char *)realloc(arr[i], mx * sizeof(char));
                if (!arr[i])
                    return -1;
            }
            arr[i][sz++] = ch;
            ch = getchar();
        }
        if (sz >= mx)
        {
            mx++;
            arr[i] = (char *)realloc(arr[i], mx * sizeof(char));
            if (!arr[i])
                return -1;
        }
        arr[i][sz++] = '\0';
        if (strcmp(arr[i], "DELETE:") == 0)
        {
            arrsz--;
            break;
        }
        tree = push_node(tree, make_node(arr[i]));
    }
    //write(tree);
    for (;;)
    {
        char *word = (char *)malloc(1 * sizeof(char));
        int wsz = 0, wlen = 1;
        char ch = getchar();
        while (ch != '\n')
        {
            if (wsz >= wlen)
            {
                wlen *= 2;
                word = (char *)realloc(word, wlen * sizeof(char));
                if (!word)
                    return -1;
            }
            word[wsz++] = ch;
            ch = getchar();
        }
        if (wsz >= wlen)
        {
            wlen += 1;
            word = (char *)realloc(word, wlen * sizeof(char));
            if (!word)
                return -1;
        }
        word[wsz] = '\0';
        if (strcmp(word, "LEVEL:") == 0)
        {
            free(word);
            break;
        }
        tree = deleteNode(tree, word);
        //write(tree);
        free(word);
    }
    int lv;
    scanf("%d", &lv);
    printf("%d\n", sz_O_n(tree));
    write_level(tree, 1, lv + 1);
    free_all(tree);
    for (int i = 0; i <= arrsz; i++)
        free(arr[i]);
    free(arr);
    printf("\n");
}