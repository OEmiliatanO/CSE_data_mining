#!/bin/bash
DATASET1="../data/Arrhythmia_data_set"
DATASET2="../data/gene_expression_cancer_RNA-Seq_data_set"

./main.elf -repeats 10 -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 3 -kmeans_converge_lim 1e-7

./main.elf -repeats 10 -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 3 -kmeans_converge_lim 1e-7

./main.elf -repeats 10 -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 3 -kmeans_converge_lim 1e-7

echo "========"

#./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -kmeans_converge_lim 1e-7

#./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -kmeans_converge_lim 1e-7

#./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -kmeans_converge_lim 1e-7
