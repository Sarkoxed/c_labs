#!/bin/bash
for i in $(ls -rt | grep tree)
do
printf "a\n" >> lol.txt
done

for i in $(ls -rt | grep tree)
do
cat lol.txt | ./show.py 40 $i
sleep 5
printf "a\n" >&0
done
