#!/bin/bash
DATASET1="../data/Arrhythmia_data_set"
DATASET2="../data/gene_expression_cancer_RNA-Seq_data_set"

echo "dataset: arrhythmia"

./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 110 -KNN_problim 0.5 -KNN_method brute -DBSCAN_minPts 3 -DBSCAN_eps 240

./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 110 -KNN_problim 0.5 -KNN_method brute -DBSCAN_minPts 3 -DBSCAN_eps 240

./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 110 -KNN_problim 0.5 -KNN_method brute -DBSCAN_minPts 3 -DBSCAN_eps 240

echo "dataset: gene expression cancer"

./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 7 -KNN_maxdis 500 -KNN_problim 0.6 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 150

./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 7 -KNN_maxdis 90 -KNN_problim 0.6 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 100

./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 7 -KNN_maxdis 90 -KNN_problim 0.6 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 100
