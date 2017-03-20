#!/bin/sh
make clean; make
echo "wc -l < test.txt"  | bin/rshell
#wc < test.txt;
#"cat < test.txt"
#"cat < DNE.txt"
#"wc -l < DNE"
#"wc -l < DNE && ps"
#"cal; cat < test.txt"
#"cal && cat < test.txt"
#"cal || cat < test.txt"
#"cat < test.txt && cal"
#"cat < test.txt || cal"
#"cat < test.txt; cal"
