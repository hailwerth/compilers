#!/bin/bash
flex dj.l
bison-2.4 -v dj.y
gcc-4.7 dj.tab.c -o dj-parse
exit 0