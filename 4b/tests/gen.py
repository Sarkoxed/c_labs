import sys
from random import randint, random, choices
from string import printable
from struct import pack

def mid(l):
    return round(sum(l) / len(l))

def sorr(l, s):
    if(len(l) == 0):
        return
    r = len(l) // 2
    s.append(l[r])

    sorr(l[:r], s)
    sorr(l[r+1:], s)
    return

n = sys.argv[3]
k = int(sys.argv[1])
name = sys.argv[2]
f = open(name+".txt", "w")
g = open(name+"_sorted.txt", "w")

t = []
if(n[0] == "i"):
    l = list(range(0, 2*k))
    t = list(range(-k, 2*k))

else:
    l = [randint(0, 2*k) for i in range(k)]
    for i in l:
        t.append(i)

t.sort()
so = []
sorr(t, so)

ll = []
for i in l:
    ll.append("add")
    ll.append(str(i))
    ll.append("".join(choices(printable[:62], k=2)))
    ll.append("".join(choices(printable[:62], k=2)))
    ll.append("save")
ll.append("exit")
ll.append("ge")
f.write("\n".join(ll))
f.close()

ll = []
for i in so:
    ll.append("add")
    ll.append(str(i))
    ll.append("".join(choices(printable[:62], k=2)))
    ll.append("".join(choices(printable[:62], k=2)))
    ll.append("save")
ll.append("exit")
ll.append("gwew")
#g.write("\n".join(ll))
g.close()
