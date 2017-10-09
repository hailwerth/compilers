#!/bin/bash
sudo apt install flex gcc-4.7 -y
wget ftp://ftp.gnu.org/gnu/bison/bison-2.4.1.tar.gz
tar zxf bison-2.4.1.tar.gz
cd bison-2.4.1
mkdir $HOME/.local/
./configure --prefix=$HOME/.local/
make
make install
mv $HOME/.local/bin/bison $HOME/.local/bin/bison-2.4
