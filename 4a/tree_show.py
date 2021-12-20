#!/home/sarkoxedaf/anaconda3/bin/python
from tkinter import *
import sys
from time import sleep

def get_new(a, g, s):
    i = 0;
    g.append([a[0], 0, 0, 0, 0, 0, 0])
    while(1):
        if(a[0] < g[i][0])and(g[i][5] == 0):
            g[i][5] = len(g) - 1
            g[-1][1] = g[i][1]+1
            g[-1][2] = i
            g[-1][3] = g[i][3] - s["total_w"]//(2 **(g[-1][1]+1))
            g[-1][4] = g[i][4] + s["tab_v"] + s["heigh"]
            return
        elif(a[0] < g[i][0]):
            i = g[i][5]
        elif(a[0] > g[i][0])and(g[i][6] == 0):
            g[i][6] = len(g) - 1
            g[-1][1] = g[i][1]+1
            g[-1][2] = i
            g[-1][3] = g[i][3] + s["total_w"]//(2 **(g[-1][1]+1))
            g[-1][4] = g[i][4] + s["tab_v"] + s["heigh"]
            return
        elif(a[0] > g[i][0]):
            i = g[i][6]


def print_node(a, s, canvas, g):
    c_min, c_max, min_ind, max_ind = 0, 0, 0, 0
    if(len(g) == 0):
        g.append([a[0],
        0, #ind in tree
        0, #prev
        s["total_w"] // 2,
        s["tab_v"],
        0, #left
        0]) #right
    else:
        get_new(a, g, s)

    p = g[-1]
    p_prev = g[p[2]]

    canvas.create_rectangle(p[3] - s["wid"]//2, p[4], p[3] + s["wid"]//2, p[4] + s["heigh"], fill = "white", outline = "black")
    canvas.create_text(p[3], p[4] + s["heigh"]//2, text=str(a[0]), font="Verdana "+str(s["wid"] - s["wid"]//2), justify=CENTER, fill = "red")
    #canvas.create_text(p[3] , p[4] + 10 + 15 , text=f"{a[1]}, {a[2]}, {a[3]}", font="Verdana 15", justify=CENTER, fill = "black")
    if(len(g) > 1):
        canvas.create_line(p[3], p[4], p_prev[3], p_prev[4] + s["heigh"], width=1, fill="black")

    #print(g)
    return

name = input("filename: ")

f = open(name, "r")
lol = f.read()[:-2]+']'
s = eval(lol)

wid = int(input("width: "))
sz = {"dep": s[0],
      "wid": wid,
      "heigh": wid,
      "tab_v": wid//4,
      "tab_g": wid//4,
      "col_max": 2**(s[0] - 1)
       }
sz.setdefault("total_w", (sz["wid"] + sz["tab_g"]) * sz["col_max"] + sz["tab_g"])
sz.setdefault("total_h", (sz["heigh"] + sz["tab_v"]) * sz["dep"] + sz["tab_v"])

window = Tk()
window.title("Binary tree")

canvas = Canvas(window,
                width = sz["total_w"],
                height = sz["total_h"],
                bg = "white", cursor="pencil")
canvas.pack()
g = []
for i in s[1:]:
    print_node(i, sz, canvas, g)

while(1):
  input()
  break
