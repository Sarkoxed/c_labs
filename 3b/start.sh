#!/bin/bash

printf "Starting Table Maker...\n"

case "$1" in
-a) ./asan.out ;;
-b) ./task.out ;;
-t) cat tests/test_now/pro_table.txt | ./asan.out ;;
-f) cat tests/test_now/table.txt | ./asan.out ;;
-h) printf "opts: [-a asan], [-b task], [-t test],[-f fill]\n" ;;
esac

if [[ -e "$2_struct" ]]
then
rm "$2_struct"
mv "$2_struct_new" "$2_struct"
fi
