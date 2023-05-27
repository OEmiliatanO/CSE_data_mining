#!/bin/bash
DATASET1="../data/Arrhythmia_data_set"
DATASETA="Arrhythmia"
DATASET2="../data/gene_expression_cancer_RNA-Seq_data_set"
DATASETB="gene"
ACCFILE="SVM-kmeans"
echo "======================== dataset: arrhythmia ====================="
echo "original, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 2 -kmeans_converge_lim 1e-7
echo "original, nor, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment  2 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "original, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel poly -SVM_kernel_gamma 1 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "original, nor, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel poly -SVM_kernel_gamma 28 -SVM_kernel_degree 2 -SVM_kernel_r 0 -kmeans_converge_lim 1e-7 -verbose false
echo "original, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel rbf -SVM_kernel_gamma 0.0000001 -SVM_kernel_degree 2 -SVM_kernel_r 500 -kmeans_converge_lim 1e-7 -verbose false
echo "original, nor, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel rbf -SVM_kernel_gamma 0.0005 -SVM_kernel_degree 2 -SVM_kernel_r 15 -kmeans_converge_lim 1e-7 -verbose false
echo "original, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.000001 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "original, nor, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.0001 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7

echo "AE 32, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 32, nor, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 32, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel poly -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 32, nor, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel poly -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 32, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel rbf -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 32, nor, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel rbf -SVM_kernel_gamma 0.5 -SVM_kernel_degree 2 -SVM_kernel_r 0 -kmeans_converge_lim 1e-7
echo "AE 32, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.000001 -SVM_kernel_degree 2 -SVM_kernel_r 0.5 -kmeans_converge_lim 1e-7
echo "AE 32, nor, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.1 -SVM_kernel_degree 2 -SVM_kernel_r 0.75 -kmeans_converge_lim 1e-7


echo "PCA 32, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 32, nor, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7

echo "PCA 32, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel poly -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 32, nor, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel poly -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 32, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel rbf -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 32, nor, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel rbf -SVM_kernel_gamma 0.5 -SVM_kernel_degree 2 -SVM_kernel_r 0 -kmeans_converge_lim 1e-7
echo "PCA 32, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.000001 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 32, nor, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.1 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7

echo "================== dataset: gene expression cancer ====================="
echo "original, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "original, nor, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "original, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel poly -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "original, nor, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel poly -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "original, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel rbf -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "original, nor, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel rbf -SVM_kernel_gamma 0.5 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "original, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.00001 -SVM_kernel_degree 2 -SVM_kernel_r 0.1 -kmeans_converge_lim 1e-7
echo "original, nor, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.01 -SVM_kernel_degree 2 -SVM_kernel_r 0.1 -kmeans_converge_lim 1e-7

echo "AE 30, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 30, nor, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.5 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 30, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel poly -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 30, nor, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel poly -SVM_kernel_gamma 1 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 30, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel rbf -SVM_kernel_gamma 5 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "AE 30, nor, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel rbf -SVM_kernel_gamma 0.5 -SVM_kernel_degree 2 -SVM_kernel_r 0 -kmeans_converge_lim 1e-7
echo "AE 30, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.00001 -SVM_kernel_degree 2 -SVM_kernel_r 0.2 -kmeans_converge_lim 1e-7
echo "AE 30, nor, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel sigmoid -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7

echo "PCA 30, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 30, nor, linear"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel linear -SVM_kernel_gamma 2 -SVM_kernel_degree 6 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 30, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel poly -SVM_kernel_gamma 2 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 30, nor, poly"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel poly -SVM_kernel_gamma 2 -SVM_kernel_degree 6 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 30, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.5 -SVM_kernel rbf -SVM_kernel_gamma 0.5 -SVM_kernel_degree 2 -SVM_kernel_r 1 -kmeans_converge_lim 1e-7
echo "PCA 30, nor, rbf"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 0.5 -SVM_kernel rbf -SVM_kernel_gamma 0.5 -SVM_kernel_degree 6 -SVM_kernel_r 0 -kmeans_converge_lim 1e-7
echo "PCA 30, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel sigmoid -SVM_kernel_gamma 0.0001 -SVM_kernel_degree 2 -SVM_kernel_r 0.1 -kmeans_converge_lim 1e-7
echo "PCA 30, nor, sigmoid"
./main.elf -repeats 1 -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel sigmoid -SVM_kernel_gamma 4 -SVM_kernel_degree 2 -SVM_kernel_r 0.1 -kmeans_converge_lim 1e-7a
