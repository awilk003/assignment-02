#!/bin/sh
make clean; make
echo "echo a > test.txt"  | bin/rshell
#"echo b >> test.txt";
#"echo c > DNE.TXT"
#"echo D >> DNE.TXT"
#"cal > test2.txt"
#"echo e > test.txt; cal"
#"echo f >> test.txt; cal"
#"echo e > test.txt && cal"
#"echo g > test.txt || cal"
#"cal ; echo h > test.txt"
#"cal || echo i > test.txt"
#"cal && echo j > test.txt"
