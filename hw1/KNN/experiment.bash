#!/bin/bash
DATAPATH="../data"
DATASETS=("$DATAPATH/testA" "$DATAPATH/testB")
repeat=50

:<< DID
for ((i=0;i<2;++i)); do
	DATASET=${DATASETS[$i]}
	echo $DATASET
	for normalize in "false" "true"; do
		LOGFILE="KNN_BF"
		if [ $normalize = "true" ]
		then
			echo BF-normalized
			LOGFILE="$LOGFILE-normalized"
		else
			echo BF
		fi
		LOGFILE="$LOGFILE-$i.log"
		echo -n "" > $LOGFILE
		for k in {1..101}; do
			echo -n "$k "
			echo -n "$k " >> $LOGFILE
			./main.elf --repeat $repeat --traindata $DATASET/train_data.csv --testdata $DATASET/test_data.csv --normalize $normalize --search_method brute --k $k >> $LOGFILE
		done
	done
done
DID

for ((i=0;i<2;++i)); do
	DATASET=${DATASETS[$i]}
	echo $DATASET
	for normalize in "false" "true"; do
		LOGFILE="KNN_ANNOY-dfs"
		if [ $normalize = "true" ]
		then
			echo annoy-dfs-normalized
			LOGFILE="$LOGFILE-normalized"
		else
			echo annoy-dfs
		fi
		LOGFILE="$LOGFILE-$i.log"
		echo -n "" > $LOGFILE

		for k in {1..101}; do
			for maxpoint in $(seq 1 101); do
				echo -n "$k $maxpoint "
				echo -n "$k $maxpoint " >> $LOGFILE
				./main.elf --repeat $repeat --traindata $DATASET/train_data.csv --testdata $DATASET/test_data.csv --normalize $normalize --search_method annoy --k $k --annoy_search_method dfs --maxpoint $maxpoint >> $LOGFILE
			done
		done
	done
done

for ((i=0;i<2;++i)); do
	DATASET=${DATASETS[$i]}
	echo $DATASET
	for normalize in "false" "true"; do
		LOGFILE="KNN_ANNOY-bfs"
		if [ $normalize == "true" ]
		then
			echo annoy-bfs-normalized
			LOGFILE="$LOGFILE-normalized"
		else
			echo annoy-bfs
		fi
		LOGFILE="$LOGFILE-$i.log"
		echo -n "" > $LOGFILE

		for k in {1..101}; do
			for maxpoint in $(seq 1 101); do
				for bfs_threhold in 0.01 0.1 1 5 10 15 20; do
					echo -n "$k $maxpoint $bfs_threhold " >> $LOGFILE
					echo -n "$k $maxpoint $bfs_threhold "
					./main.elf --repeat $repeat --traindata $DATASET/train_data.csv --testdata $DATASET/test_data.csv --normalize $normalize --search_method annoy --k $k --annoy_search_method bfs --maxpoint $maxpoint --bfs_threhold $bfs_threhold >> $LOGFILE
				done
			done
		done
	done
done
