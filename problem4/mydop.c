#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define K 269
#define TRASH 20

typedef struct node node;
typedef struct Pair Pair;

struct node
{
    int prior;
    char *s;
    node *l, *r;
};

struct Pair
{
    node *first;
    node *second;
};

int check(node *t, char *s)
{
    if (!t)
        return 0;
    int res = strcmp(s, t->s);
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
    ret->first = f;
    ret->second = s;
    return ret;
}

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

Pair *split(node *t, char *s)
{
    if (!t)
        return make_pair(NULL, NULL);
    int res = strcmp(t->s, s);
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
    if (check(t, in->s))
    {
        free(in->s);
        free(in);
        return t;
    };
    Pair *p = split(t, in->s);
    node *ret = merge(p->first, merge(in, p->second));
    free(p);
    return ret;
}

node *remove_by_s(node *t, char *s)
{
    if (!t)
        return t;
    if (!check(t, s))
        return t;
    int res = strcmp(s, t->s);
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
        free(t->s);
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
    free(t->s);
    free(t);
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
    printf("'%s' prior:%x\n", t->s, t->prior);
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

char *read_word()
{
    char *ret = (char *)malloc(1 * sizeof(char));
    int sz = 0, mx = 1;
    char ch = getchar();
    while (ch != ' ' && ch != '\n')
    {
        if (sz >= mx)
        {
            mx *= 2;
            ret = (char *)realloc(ret, mx * sizeof(char));
            if (!ret)
                exit(-1);
            // return -1;
        }
        ret[sz++] = ch;
        ch = getchar();
    }
    if (sz >= mx)
    {
        mx++;
        ret = (char *)realloc(ret, mx * sizeof(char));
        if (!ret)
            exit(-1);
        // return -1;
    }
    ret[sz++] = '\0';
    return ret;
}

int main()
{
    srand(time(NULL));
    char trash[TRASH];
    node *tree = NULL;
    while(1){
        char ch = getchar();
        if(ch == '+'){
            getchar();
            char *word = read_word();
            if(check(tree,word)){
                printf("na\n");
            }
            else{
                tree = insert(tree,make_node(word));
                printf("a\n");
            }
        }
        else if(ch == '-'){
            getchar();
            char *word = read_word();
            if(check(tree,word)){
                printf("rm\n");
                tree = remove_by_s(tree,word);
            }
            else{
                printf("nrm\n");
            }
        }
        else{
            break;
        }
    }
    printf("\n");
    free_all(tree);
}
