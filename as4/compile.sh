#!/bin/bash
rm dj-ast
flex dj.l
bison-2.4 dj.y
gcc-4.7 dj.tab.c ast.c -o dj-ast -w