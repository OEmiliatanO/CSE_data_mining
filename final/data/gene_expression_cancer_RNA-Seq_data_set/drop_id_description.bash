#!/bin/bash
n=`cat $1 | wc -l`
echo $n
tail -n `expr $n - 1` $1 > $2
cut -f 1 --delimiter=, --complement $2 > $1
rm $2
