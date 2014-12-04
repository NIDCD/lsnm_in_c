#! /bin/sh
#

for file in `ls  m*.in`; do
change $file
done

for file in `ls r*.in`; do
change $file
done

for file in `ls  a*.in`; do
change $file
done

exit 0
