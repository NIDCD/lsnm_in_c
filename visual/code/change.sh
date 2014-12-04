#! /bin/sh
#

for file in `ls  ../inputs/*.inp`; do
change $file
done

for file in `ls  ../inputs/*.*s*`;
do
change $file
done

exit 0
