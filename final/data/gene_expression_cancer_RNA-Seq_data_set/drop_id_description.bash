#!/bin/bash
n=`cat $1 | wc -l`
echo $n
tail -n `expr $n - 1` $1 > tmp
cut -f 1 --delimiter=, --complement tmp > $1
rm tmp
