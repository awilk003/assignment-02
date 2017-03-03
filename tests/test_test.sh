#!/bin/sh
make clean; make
echo "test -e bin/rshell"  | bin/rshell
# echo "test bin/rshell"
# echo "test -r bin/rshell"
# echo "test -e a"
# echo "      test - bin/rshell"

