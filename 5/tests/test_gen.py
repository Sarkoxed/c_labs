import sys
from random import randint, random, choices
from string import printable
from struct import pack

def sorr(l, s):
    if(len(l) == 0):
        return
    r = len(l) // 2
    s.append(l[r])

    sorr(l[:r], s)
    sorr(l[r+1:], s)
    return

a, b = int(sys.argv[1]), int(sys.argv[2])
l = ["lol"]
kok = []
for i in range(-2*a, 2*a):
    for j in range(-2*b, 2*b):
        l.append("add_v")
        l.append("".join(choices(printable[:62], k=1)))
        kok.append(l[-1])
        l.append(str(i/2))
        l.append(str(j/2))
for i in range(4*a):
    l.append("add_e")
    l.append(choices(kok, k=1)[0])
    l.append(choices(kok, k=1)[0])
    l.append(str(randint(-100, 100)))

l.append("save")
l.append("exit")
l.append("iefjiwi")
f = open("teeest", "w")
f.write("\n".join(l))
