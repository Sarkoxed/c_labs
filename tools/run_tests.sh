#!/bin/bash

set -Eeuo pipefail

echo "" > "logs/$1_log.txt"

for f in $(ls tests/); do
	echo "testcase: $f"
	./"$1" < "test/cases/$f" | sudo tee -a logs/"$1_log.txt" || true
done
