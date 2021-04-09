import numpy as np
n=int(input())
l=[]
for ind in range(n):
    sz=int(input())
    l.append([[int(i) for i in input().split()] for _ in range(sz)])
l.sort(key=np.linalg.det)
for i in l:
    for j in i:
        for k in j:
            print(k, end=' ')
        print()
