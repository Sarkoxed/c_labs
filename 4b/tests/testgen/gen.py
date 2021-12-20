import sys
from random import randint, random, choices
from string import printable
from struct import pack


n = sys.argv[1]
k = int(sys.argv[2])
name = sys.argv[3]
f = open(name, "w")

if(n[0] == "-"):
    l = [0,8,4,12,2,6,10,14,1,3,5,7,9,11,13,15]
    for i in l[1:]:
        l.append(-i)
else:
    l = [randint(-k, k) for i in range(k)]

ll = []
for i in l:
    ll.append("add")
    ll.append(str(i))
    ll.append("".join(choices(printable[:62], k=2)))
    ll.append(str(random()))
    ll.append(str(random()))
ll.append("exit")
ll.append("ge")
f.write("\n".join(ll))
f.close()
