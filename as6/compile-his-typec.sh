#!/bin/bash
rm dj2dism-his
# flex dj.l
# bison-2.4 dj.y
#gcc-4.7 dj.tab.c ast.c symtbl.o typecheck.c -o dj-tc
#gcc-4.7 dj.tab.c ast.c symtbl.c typecheck.c -o dj-tc
gcc-4.7 dj.tab.o ast.o symtbl.o typecheck.o codegen.c -o dj2dism-his