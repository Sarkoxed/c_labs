import sys
f = open("edgs_"+sys.argv[1], "r")
g = open("vers_"+sys.argv[1], "r")
r = []
l = (f.read()).split("\n")[:-1]
k = (g.read()).split("\n")[:-1]
for i in k:
    z = i.split()
    r.append("add_v")
    r.append(z[0])
    r.append(z[1])
    r.append(z[2])

for i in l:
    z = i.split()
    r.append("add_e")
    r.append(z[1])
    r.append(z[2])
    r.append(z[3])

lop = open("init", "w")
lop.write("\n".join(r))
