import sys
import numpy as np
with open(sys.argv[1]) as shit:
    t = [[int(j) for j in i.split()]
         for i in shit.read().split('\n') if i != ""]
    ind = 0
    heh = []
    while(ind < len(t)):
        now = [t[i] for i in range(ind, ind+len(t[ind]))]
        heh.append(round(np.linalg.det(now)))
        ind += len(t[ind])
    for i in range(len(heh)-1):
        if(heh[i+1] < heh[i]):
            print(-1)
            print(heh)
            sys.exit()
    if(len(t) > 0):
        print(1)
    else:
        print(-1)
