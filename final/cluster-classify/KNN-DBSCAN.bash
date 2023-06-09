#!/bin/bash
DATASET1="../data/Arrhythmia_data_set"
DATASET2="../data/gene_expression_cancer_RNA-Seq_data_set"

echo "dataset: arrhythmia"

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 15 -KNN_problim 0.7 -KNN_method brute -DBSCAN_minPts 5 -DBSCAN_eps 500

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 15 -KNN_problim 0.7 -KNN_method brute -DBSCAN_minPts 5 -DBSCAN_eps 5

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 5 -KNN_maxdis 20 -KNN_problim 0.9 -KNN_method brute -DBSCAN_minPts 5 -DBSCAN_eps 150

echo "dataset: gene expression cancer"

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 101 -KNN_maxdis 10000 -KNN_problim 0.9 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 50

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 13 -KNN_maxdis 100 -KNN_problim 0.8 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 10
#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 7 -KNN_maxdis 12 -KNN_problim 0.8 -KNN_method brute -DBSCAN_minPts 50 -DBSCAN_eps 11

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 7 -KNN_maxdis 90 -KNN_problim 0.6 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 100

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 10 -KNN_maxdis 100 -KNN_problim 1 -KNN_method brute -DBSCAN_minPts 15 -DBSCAN_eps 70
