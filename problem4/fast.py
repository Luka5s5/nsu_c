s={}
while(True):
    l=input().split()
    if(len(l)<2):
        break
    if(l[0]=='+'):
        if(l[1] not in s):
            print('a')
            s[l[1]]=1
        else:
            print('na')
    else:
        if(l[1] not in s):
            print('nrm')
        else:
            print('rm')
            s.pop(l[1])
