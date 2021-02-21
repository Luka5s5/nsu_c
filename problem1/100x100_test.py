from random import randint

n, m = randint(1, 100), randint(1, 100)
print(m, n)
l = [[randint(-1000, 1000) for j in ' '*m] for i in n*' ']
for i in l:
    for j in i:
        print(j, end=' ')
    print()
