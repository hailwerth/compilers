#!/bin/bash
for count in {1..46}
do
echo -e "\n${1}${count}"
./dj-tc examples/${1}/${1}${count}.dj
done
exit 0