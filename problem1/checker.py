import os
import sys
import time

_, f1, f2, gen, iters, slp = sys.argv
slp = int(slp)

for i in range(int(iters)):
    print('Test', i+1)
    os.popen('python3 %s > test.txt' % gen)
    p1 = os.popen('./%s < test.txt' % f1)
    p2 = os.popen('./%s < test.txt' % f2)
    if(slp != 0):
        time.sleep(slp/1000)
    v1 = p1.readlines()
    v2 = p2.readlines()

    if v1 != v2:
        print("FAIL!\nInput:")
        print(*(open("test.txt").readlines()))
        print("Correct output:")
        print(*v1)
        print("Wrong output:")
        print(*v2)
        sys.exit()
print("No output differences found.")
