#!/bin/sh
make clean; make
echo "echo a |tee test.txt"  | bin/rshell
#"echo a | tee test.txt | tee test2.txt;
#"cal && echo a | tee test.txt"
#"cal; echo a | tee DNE.txt"
#"cal || echo a | tee test.txt"
#"cal | tee test.txt | tee test2.txt | tee test3.txt | tee test4.txt"
