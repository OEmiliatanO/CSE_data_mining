#!/bin/bash
DATASET1="../data/Arrhythmia_data_set"
DATASET2="../data/gene_expression_cancer_RNA-Seq_data_set"

./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 10 -KNN_maxdis 10 -KNN_problim 0.5 -KNN_method brute -SVM_converge_lim 1e-7 -SVM_punishment 1 -DBSCAN_minPts 7 -DBSCAN_eps 10 -kmeans_k 13 -kmeans_converge_lim 1e-7

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $(DATASET2)/train_data.csv -train_label_path $(DATASET2)/train_label.csv -test_data_path $(DATASET2)/test_data.csv -test_label_path $(DATASET2)/train_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 10 -KNN_maxdis 10 -KNN_method brute -SVM_converge_lim 1e-7 -SVM_punishment 1 -DBSCAN_minPts 7 -DBSCAN_eps 10 -kmeans_k 13 -kmeans_converge_lim 1e-7
