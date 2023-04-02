#!/bin/bash
DATAPATH="../data"
DATASETS=("$DATAPATH/testA" "$DATAPATH/testB")
repeat=50

for ((i=0;i<2;++i)); do
	DATASET=${DATASETS[$i]}
	echo $DATASET
	for normalize in "false" "true"; do
		for crit in "entropy" "gini"; do
			LOGFILE="decision_tree"
			if [ $normalize = "true" ]
			then
				echo decision_tree-normalized
				LOGFILE="$LOGFILE-normalized"
			else
				echo decision_tree
			fi
			LOGFILE="$LOGFILE-$i.log"
			echo -n "" > $LOGFILE
			./main.elf --repeat $repeat --traindata $DATASET/train_data.csv --testdata $DATASET/test_data.csv --normalize $normalize --search_method decision_tree --criterion $crit >> $LOGFILE
		done
	done
done


for ((i=0;i<2;++i)); do
	DATASET=${DATASETS[$i]}
	echo $DATASET
	for normalize in "false" "true"; do
		for crit in "entropy" "gini"; do
			LOGFILE="random_forest"
			if [ $normalize == "true" ]
			then
				echo random_forest-normalized
				LOGFILE="$LOGFILE-normalized"
			else
				echo random_forest
			fi
			LOGFILE="$LOGFILE-$i.log"
			echo -n "" > $LOGFILE
			for n in {1..101}; do
				./main.elf --repeat $repeat --traindata $DATASET/train_data.csv --testdata $DATASET/test_data.csv --normalize $normalize --search_method random_forest --criterion $crit -n $n >> $LOGFILE
			done
		done
	done
done
