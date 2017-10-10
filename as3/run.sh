#!/bin/bash
for count in {1..30}
do
echo -e "\nGOOD${count}"
./dj-parse examples/good/good${count}.dj
done
exit 0