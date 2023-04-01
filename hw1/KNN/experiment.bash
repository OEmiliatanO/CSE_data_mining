#!/bin/bash
DATAPATH="../data"
DATASETS=("$DATAPATH/testA" "$DATAPATH/testB")

for ((i=0;i<2;++i)); do
	DATASET=${DATASETS[$i]}
	for normalize in "false" "true"; do
		LOGFILE=KNN_BF
		if [ normalize == "true" ]
		then
			echo BF-normalized
			LOGFILE=$LOGFILE-normalized
		else
			echo BF
		fi
		LOGFILE=$LOGFILE-$i.log

		for k in {1...100}; do
			echo -n "$k " >> $LOGFILE
			./main.elf --repeat 100 --traindata $DATASET/train_data.csv --testdata $DATASET/test_data.csv --normalize $normalize --search_method brute --k $k >> $LOGFILE 2>/dev/null
		done
	done
done

for ((i=0;i<2;++i)); do
	DATASET=${DATASETS[$i]}
	for normalize in "false" "true"; do
		LOGFILE=KNN_ANNOY-dfs
		if [ normalize == "true" ]
		then
			echo annoy-dfs-normalized
			LOGFILE=$LOGFILE-normalized
		else
			echo annoy-dfs
		fi
		LOGFILE=$LOGFILE-$i.log

		for k in {1...100}; do
			for maxpoint in {1...$k}; do
				echo -n "$k $maxpoint " >> $LOGFILE
				./main.elf --repeat 100 --traindata ../data/testA/train_data.csv --testdata ../data/testA/test_data.csv --normalize $normalize --search_method annoy --k $k --annoy_search_method dfs --maxpoint $maxpoint >> $LOGFILE 2>/dev/null
		done
	done
done


for ((i=0;i<2;++i)); do
	DATASET=${DATASETS[$i]}
	for normalize in "false" "true"; do
		LOGFILE=KNN_ANNOY-bfs
		if [ normalize == "true" ]
		then
			echo annoy-bfs-normalized
			LOGFILE=$LOGFILE-normalized
		else
			echo annoy-bfs
		fi
		LOGFILE=$LOGFILE-$i.log

		for k in {1...100}; do
			for maxpoint in {1...$k}; do
				for bfs_threhold in 0.01 0.1 1 5 10 15 20 25 30; do
					echo -n "$k $maxpoint $bfs_threhold " >> $LOGFILE
					./main.elf --repeat 100 --traindata ../data/testA/train_data.csv --testdata ../data/testA/test_data.csv --normalize $normalize --search_method annoy --k $k --annoy_search_method bfs --maxpoint $maxpoint --bfs_threhold $bfs_threhold >> $LOGFILE 2>/dev/null
			done
		done
	done
done

