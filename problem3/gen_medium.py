from random import randint
import numpy as np
ntests = randint(1, 3)
print(ntests)
for t in range(ntests):
    while True:
        dim = randint(10, 11)
        l = [[0 for j in range(dim)] for i in range(dim)]
        for i in range(dim):
            for j in range(dim):
                l[i][j] = randint(-3, 3)
        det = np.linalg.det(l)
        if(det < 1e9 and det > -1e9):
            break
    print(dim)
    for i in range(dim):
        for j in range(dim):
            print(l[i][j], end=' ')
        print()
