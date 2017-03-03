#!/bin/sh

make clean; make
echo "(((ps) || ls) && cal)"  | bin/rshell
# echo "(echo a && echo b) || (echo c && echo d)"
# echo "((echo a) && echo b)"
# echo "()"
# echo " (echo a"
# echo " echo a)"


