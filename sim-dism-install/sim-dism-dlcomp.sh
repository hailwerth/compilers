#!/bin/bash
#run: $ sh sim-dism-dlcomp.sh
NEWDIR="sim-dism"
wget http://www.cse.usf.edu/~ligatti/compilers-17/as1/dism/nm.dism
mkdir $NEWDIR
cd $NEWDIR
wget -r -nH -nd -np -R index.html* -e robots=off http://www.cse.usf.edu/~ligatti/compilers-17/as1/dism/sim-dism/
flex dism.l
bison-2.4 dism.y
gcc-4.7 dism.tab.c ast.c interp.c -osim-dism
