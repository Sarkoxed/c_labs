import os
from random import choices, randint, random
from string import ascii_letters
from sys import argv

LOL = ascii_letters

def get_str(n):
    return "".join(choices(LOL, k = n))

def choose(a, k):
    if len(a) > 0:
        n = randint(0, 100)
        if n < 40:
            return str(a[randint(0, len(a)-1)])
        else:
            if k == 1:
                return get_str(2)
            else:
                return str(randint(1, 1000))
    else:
        if k == 1:
            return get_str(2)
        else:
            return str(randint(1, 1000))

os.system("touch table.txt")
os.system("touch pro_table.txt")
if argv[1] == "-f":
    f = open("pro_table.txt", "w")
else:
    f = open("table.txt", "w")

s = ["add", "both_delete", "del_one", "get_one", "both_search", "show"]
l = []
ks1 = []
ks2 = []
n = int(argv[2])
for i in range(randint(10,n)):
    if(argv[1] == "-f"):
        t = s[randint(0, len(s)-1)]
    else:
        t = "add"
    l.append("")
    l.append(t);
    if(t == "add"):
        l.append(str(randint(1, 1000)))
        ks1.append(l[-1])
        l.append(get_str(2))
        ks2.append(l[-1])
        l.append(get_str(randint(1, 10)))
        l.append(str(random()+randint(1, 10)))
        l.append(str(random()+randint(1, 10)))
    elif(t == "del_one"):
        l.append(["str", "uns"][randint(0,1)])
        if(l[-1] == "uns"):
            l.append(choose(ks1, 0))
        else:
            l.append(choose(ks2, 1))
            l.append(["y", "n"][randint(0,1)])
            if l[-1] == "y":
                l.append(str(randint(1, 10)))
    elif t == "both_delete":
        l.append(choose(ks1, 0))
        l.append(choose(ks2, 1))
    elif t == "get_one":
        l.append(["str", "uns"][randint(0,1)])
        if(l[-1] == "uns"):
            l.append(choose(ks1, 0))
        else:
            l.append(choose(ks2, 1))
            l.append(["y", "n"][randint(0,1)])
            if l[-1] == "y":
                l.append(str(randint(1, 10)))
    elif t == "both_search":
        l.append(choose(ks1, 0))
        l.append(choose(ks2, 1))
    elif t == "show":
        l.append(["y", "n"][randint(0,1)])

os.system("echo "+str(len(l)));
l = [str(len(l))] + l
#l.append("endofile")
l.append("show")
l.append("y")
l.append("exit")
s = "\n".join(l)
f.write(s)
f.close()
