import sys
from random import shuffle, randint

if(len(sys.argv)!=4):
    print(sys.argv,'Usage: python3 gen.py [N of words to add] [N of words to delete] [level N]')
    exit()

addn=int(sys.argv[1])
rmn=int(sys.argv[2])
lv=int(sys.argv[3])

words=[]
with open("raw.txt","r") as f:
    for line in f:
        for i in line.split():
            words.append((''.join([j for j in i if j.isalpha()])).lower());
words=[i for i in words if len(i)>=3]
words=list(set(words))
shuffle(words)

added=[]
print("TEXT:")
for i in range(addn):
    added.append(words[randint(0,len(words)-1)])
    print(added[len(added)-1],end=' ')
print()
print('DELETE:')
added=list(set(added))
for i in range(rmn):
    print(added[randint(0,len(added)-1)],end=' ')
print('\nLEVEL:',lv,sep='\n')
