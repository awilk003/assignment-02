#!/bin/sh
make clean; make
echo "ls && ls || ls && ls || ls" | bin/rshell 
#"ls ; ls || ls && ls # ls";
#"ls || ls && ls || ls ; ls"
#"asdf && ls; asdf || asdf || ls; ls"i

