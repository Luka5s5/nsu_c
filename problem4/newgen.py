from random import randrange, shuffle, randint, choice

rmp=50
addp=30
adds=60

class ListDict(object):
    def __init__(self):
        self.item_to_position = {}
        self.items = []

    def __len__(self):
        return len(self.items)
    
    def add_item(self, item):
        if item in self.item_to_position:
            return
        self.items.append(item)
        self.item_to_position[item] = len(self.items)-1

    def remove_item(self, item):
        position = self.item_to_position.pop(item)
        last_item = self.items.pop()
        if position != len(self.items):
            self.items[position] = last_item
            self.item_to_position[last_item] = position

    def choose(self):
        return choice(self.items)

def maprange(a, b, s):
    (a1, a2), (b1, b2) = a, b
    return  b1 + ((s - a1) * (b2 - b1) / (a2 - a1))
print("getting words")
words=[]
with open("raw.txt","r") as f:
    for line in f:
        for i in line.split():
            words.append((''.join([j for j in i if j.isalpha()])).lower());
words=[i for i in words if len(i)>=3]
words=list(set(words))
shuffle(words)
print("got words")

for tn in range(2,90):
    print("generating test "+str(tn))
    with open("tests/test"+(tn<10)*'0'+str(tn)+".txt","w") as f:
        to=0
        if(tn<=20): #queries<=30
            to=int(maprange((2,20),(1,30),tn))
        if(tn>20 and tn<=50): #30<queries<=100
            to=int(maprange((21,50),(30,100),tn))
        if(tn>50 and tn<=80): #100<queries<=1000
            to=int(maprange((51,80),(100,1000),tn))
        if(tn>80 and tn<=90): #1000<queries<=100000
            to=int(maprange((81,99),(1000,100000),tn))
        added=ListDict()
        not_added=ListDict() #words.copy()
        for i in words:
            if(len(i)<=(10**6)//to):
                not_added.add_item(i)
        for qn in range(to):
            if(randint(1,100)<=adds):
                if(len(not_added)==0 or (randint(1,100)<=addp and len(added)!=0)):
                    wrd=added.choose()
                    f.write("+ "+wrd+"\n")
                else:
                    wrd=not_added.choose()
                    not_added.remove_item(wrd)
                    added.add_item(wrd)
                    f.write("+ "+wrd+"\n")
            else:
                if(len(not_added)==0 or (randint(1,100)<=rmp and len(added)!=0)):
                    wrd=added.choose()
                    added.remove_item(wrd)
                    not_added.add_item(wrd)
                    f.write("- "+wrd+"\n")
                else:
                    wrd=not_added.choose()
                    f.write("- "+wrd+"\n")
        f.write("end\n")
for tn in range(90,100):
    print("generating test "+str(tn))
    with open("tests/test"+(tn<10)*'0'+str(tn)+".txt","w") as f:
        if(tn>80 and tn<=99): #1000<queries<=100000
            to=int(maprange((90,99),(100,100000),tn))
        added=ListDict()
        not_added=ListDict() #words.copy(
        for i in words:
            if(len(i)<=(10**6)//to):
                not_added.add_item(i)
        srt=list(sorted(not_added.items))
        for t in range(min(to//2-1,len(srt))):
            f.write("+ "+srt[t]+"\n")
            added.add_item(srt[t])
            not_added.remove_item(srt[t])
        for t in range(to//2-1):
            if(randint(1,100)<=85):
                wrd=added.choose()
                f.write("+ "+wrd+"\n")
            else:
                wrd=not_added.choose()
                f.write("- "+wrd+"\n")
        f.write("end")
