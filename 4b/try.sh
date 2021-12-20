#!/bin/bash
if [ "$5" = "-n" ]
then
python tests/gen.py "$4" "$2" "$3"
fi

case "$1" in
-s) cat "$2_sorted.txt" | ./asan.out ;;
-ns) cat "$2.txt" | ./asan.out ;;
esac

#1 - cat key
#2 - name of file
#3 - py key to iterate
#4 - number of els
#5 - if you wanna new
