import numpy as np
n=int(input())
l=[]
for ind in range(n):
    sz=int(input())
    l.append([[int(i) for i in input().split()] for _ in range(sz)])
print(max([np.linalg.det(i) for i in l]))
