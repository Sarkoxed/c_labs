#!/home/sarkoxedaf/anaconda3/bin/python
import tkinter as tk
import sys
from math import sqrt
def apop(l):
    if(l[-1] == 0):
        return l
    z = l[-2]
    x = []
    y = []
    for i, j in z:
        x.append(l[i+1][1])
        x.append(l[j+1][1])

        y.append(l[i+1][2])
        y.append(l[j+1][2])

    x.sort()
    y.sort()
    minx = x[0] - 1000
    maxx = x[-1] + 1000
    miny = y[0]  - 1000
    maxy = y[-1] + 1000
    a = []
    ff = 0
    for i in range(1,l[0]):
        if(minx<=l[i][1]<=maxx and miny<=l[i][2]<=maxy):
            ff+=1
            a.append(l[i])
    a = [ff] + a
    for i in range(l[0]+1, len(l)):
        if(len(l[i]) == 5):
            k = i
            break
        if(minx<=l[l[i][0]+1][1]<=maxx and miny<=l[l[i][0]+1][2]<=maxy)and (minx<=l[l[i][1]+1][1]<=maxx and miny<=l[l[i][1]+1][2]<=maxy):
            a.append(l[i])

    a.append([minx, miny,maxx,maxy, 0])
    for i in range(k+1, len(l)):
        a.append(l[i])

    return a


def check(li, a, b, dickt):
    if(li[-1] == 0):
        return "grey"
    ak = li[-2]
    for u, v in ak:
        if(u == a and v == b):
            return "red"
    return "grey"

def reorg(l, k):
    s = {}
    n = 0
    for i in range(k):
        s[l[i][-1]] = n
        l[i][-1] = n
        n += 1
    if(l[-1] == 0):
        z = -2
    else:
        z = -3
    for i in range(k, len(l)+z):
        l[i][0] = s[l[i][0]]
        l[i][1] = s[l[i][1]]

    if(l[-1] == 1):
        for i in l[-2]:
            i[0] = s[i[0]]
            i[1] = s[i[1]]

    return s

def pip(s):
    for i in s[1:-1]:
        if(len(i) == 4 and type(i[0])!=type("ass") and type(i[0])==type(8)):
            if(abs(i[-2]) > 0):
                return False
    return True

name = sys.argv[1]
f = open(name, "r")

lol = f.read()

s = eval(lol)
pok = {}
pok = reorg(s[1:], s[0])
wid = float(sys.argv[4])

s = apop(s)
waf = {}
waf = reorg(s[1:], s[0])
if(s[-1] == 1):
    for i, j  in waf.items():
        for k, l in pok.items():
            if l == i:
                pok[k] = j
    oo = s[-3]
    for i in range(1, s[0]+1):
        s[i][1] = s[i][1] - oo[0] + 1
        s[i][2] = s[i][2] - oo[1] + 1
    oo[2] = oo[2] - oo[0] + 1
    oo[3] = oo[3] - oo[1] + 1
    oo[0] = 1.0
    oo[1] = 1.0


print("passed reorder of dict")


if(s[-1] == 1):
    kol = -3
else:
    kol = -2
x0,y0,x1,y1 = s[kol][0], s[kol][1], s[kol][2], s[kol][3]

sz = {"wid":   0,
      "height": 0,
      "left": 0,
      "right": 0,
      "top": 0,
      "down": -0,
      "midx": 0,
      "midy": 0,
      "scale" : float(sys.argv[2])
       }
sz["wid"] = (x1-x0)*sz["scale"] + 2 * (2*sz["scale"])
sz["height"] = (y1-y0)*sz["scale"] + 2 * (2*sz["scale"])
sz["right"] = (x1-x0)*sz["scale"] + 3*sz["scale"]
sz["down"] = (y1-y0)*sz["scale"] +3* sz["scale"]
sz["left"] = sz["scale"]
sz["top"] = sz["scale"]
r = float(sys.argv[3])
if(x0 >= 0 and x1 >= 0):
    sz["midx"] = sz["scale"]
elif(x0 <= 0 and x1 <= 0):
    sz["midx"] = sz["wid"] - sz["scale"]
else:
    sz["midx"] = abs(x0)*sz["scale"] + 2*sz["scale"]

if(y0 >= 0 and y1 >= 0):
    sz["midy"] = sz["height"] - sz["scale"]
elif(y0 <= 0 and y1 <= 0):
    sz["midy"] = sz["scale"]
else:
    sz["midy"] = abs(y1)*sz["scale"] + 2*sz["scale"]


window = tk.Tk()
window.title("OrGraph")

canvas = tk.Canvas(window,
                width = sz["wid"],
                height = sz["height"],
                bg = "white", cursor="pencil")
canvas.pack()

canvas.create_line(sz["midx"], sz["down"], sz["midx"], sz["top"], width=wid, fill="black", arrow=tk.LAST)
canvas.create_text(sz["midx"]+11, sz["top"] , text="y", font="Verdana 11", justify=tk.CENTER, fill = "black")
canvas.create_line(sz["left"], sz["midy"], sz["right"], sz["midy"], width=wid, fill="black", arrow=tk.LAST)
canvas.create_text(sz["right"], sz["midy"]-11 , text="x", font="Verdana 11", justify=tk.CENTER, fill = "black")
canvas.create_text(sz["midx"]+10, sz["midy"]-10 , text="O", font="Verdana 11", justify=tk.CENTER, fill = "black")
"""for i in range(int(x0), int(x1)+1):  ####################################################################################
    if i == 0:
        continue
    canvas.create_text(sz["midx"]+i*sz["scale"], sz["midy"]-10 , text=str(i), font="Verdana 11", justify=tk.CENTER, fill = "black")
    canvas.create_line(sz["midx"]+i*sz["scale"], sz["midy"]-2, sz["midx"]+i*sz["scale"], sz["midy"]+2, width=wid, fill="black")
for i in range(int(y0), int(y1)+1):
    if i == 0:
        continue
    canvas.create_text(sz["midx"]+10, sz["midy"]-i*sz["scale"] , text=str(i), font="Verdana 11", justify=tk.CENTER, fill = "black")
    canvas.create_line(sz["midx"]-2, sz["midy"]-i*sz["scale"], sz["midx"]+2, sz["midy"]-i*sz["scale"], width=wid, fill="black")


"""

for i in range(int(s[0])):
    l = s[i+1]
    x = sz["midx"] + l[1]*sz["scale"]
    y = sz["midy"] - l[2]*sz["scale"]
    canvas.create_line(x, sz["midy"] +2, x, sz["midy"]-2, width=wid, fill="black")
    canvas.create_line(sz["midx"]+2, y, sz["midx"]-2, y, width=wid, fill="black")
    canvas.create_oval(x-r,y-r,x+r,y+r)
    if(sys.argv[5] == "1"):
        canvas.create_text(x,y, text=str(l[0]), font="Verdana 14", justify=tk.CENTER, fill = "red")

rux = pip(s)
for i in s[int(s[0])+1:]:
    if(len(i) == 5):
        break
    a = s[int(i[0])+1]
    b = s[int(i[1])+1]
    st = check(s, int(i[0]), int(i[1]), pok)
    ax = sz["midx"] + float(a[1])*sz["scale"]
    ay = sz["midy"] - float(a[2])*sz["scale"]
    bx = sz["midx"] + float(b[1])*sz["scale"]
    by = sz["midy"] - float(b[2])*sz["scale"]

    if(int(i[0]) == int(i[1])):
        r = 10
        canvas.create_line(ax+r/sqrt(2), ay-r/sqrt(2),ax,ay-3*r, width=wid, fill="grey")
        canvas.create_line(ax,ay-3*r,ax-r/sqrt(2),ay-r/sqrt(2), width=wid, fill="grey",  arrow=tk.LAST)
        canvas.create_text(ax , ay - 3*r,text=str(i[2]),font="Verdana 10", justify=tk.CENTER, fill = "black")
        continue

    r = float(sys.argv[3])  # 10
    k = float(sys.argv[3])  # 10
    leng = sqrt((ax-bx)**2+(by-ay)**2)
    if(leng == 0):
        continue
    sin = -(by - ay) / leng
    cos = (bx - ax) / leng
    ax += r*cos
    bx -= r*cos
    ay -= r*sin
    by += r*sin
    canvas.create_line(ax, ay,bx,by, width=wid, fill=st, arrow=tk.LAST)
    if(ax > bx):
        k = k*1.5
    else:
        k = -k*1.5

    if(ay > by):
        r = -r*1.5
    else:
        r = r*1.5

    """if(not rux):
        canvas.create_text((ax+bx)/2 + 1.5*r, (ay + by)/2 +1.5*k, text=str(i[2])+"/"+str(i[3]),font="Verdana 9", justify=tk.CENTER, fill="black")
    else:
        canvas.create_text((ax+bx)/2 + r, (ay + by)/2 +k, text=str(i[3]),font="Verdana 11", justify=tk.CENTER, fill="black")
    """
while(1):
  input()
  break
