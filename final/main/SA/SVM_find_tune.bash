#!/bin/bash
DATASET1="../../data/Arrhythmia_data_set"
DATASETA="Arrhythmia"
DATASET2="../../data/gene_expression_cancer_RNA-Seq_data_set"
DATASETB="gene"

echo ====================$DATASETA========================
echo "=========SVM-kmeans=========="
echo "original, linear"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel linear
echo "original, linear, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel linear
echo "original, poly"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel poly
echo "original, poly, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel poly
echo "original, rbf"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel rbf
echo "original, rbf, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel rbf
echo "original, sigmoid"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 0.000002 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel sigmoid
echo "original, sigmoid, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 0.00002 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel sigmoid


echo "AE 32, linear"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel linear
echo "AE 32, linear, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel linear
echo "AE 32, poly"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel poly
echo "AE 32, poly, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel poly
echo "AE 32, rbf"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel rbf
echo "AE 32, rbf, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel rbf
echo "AE 32, sigmoid"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 0.0000001 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel sigmoid
echo "AE 32, sigmoid, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 0.0001 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel sigmoid

echo "PCA 32, linear"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel linear
echo "PCA 32, linear, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel linear
echo "PCA 32, poly"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel poly
echo "PCA 32, poly, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel rbf
echo "PCA 32, rbf"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel rbf
echo "PCA 32, rbf, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel rbf
echo "PCA 32, sigmoid"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel sigmoid
echo "PCA 32, sigmoid, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10 -SVM_kernel sigmoid

echo "=========SVM-DBSCAN=========="
echo "original"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20
echo "original, nor"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10  -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20

echo "AE 32"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20
echo "AE 32, nor"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20

echo "PCA 32"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20
echo "PCA 32, nor"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20

echo ====================$DATASETB========================
echo "=========SVM-kmeans=========="

echo "original"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 13 -init_KNN_maxdis 1000 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "original, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 13 -init_KNN_maxdis 1000 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "AE 30"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 13 -init_KNN_maxdis 1000 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20
echo "AE 30, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 13 -init_KNN_maxdis 1000 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "PCA 30"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20
echo "PCA 30, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "PCA 100"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_100.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_100.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel sigmoid -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 0.00001 -init_SVM_kernel_r 0.0001 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20
echo "PCA 100, nor"
./main.elf -classifying SVM -clustering kmeans -train_data_path $DATASET2/PCA_train_data_100.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_100.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel sigmoid -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 0.001 -init_SVM_kernel_r 0 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "=========SVM-DBSCAN=========="

echo "original"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 5 -init_KNN_maxdis 10000 -init_KNN_problim 0.9 -init_DBSCAN_minPts 10 -init_DBSCAN_eps 1000 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1
echo "original, nor"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 5 -init_KNN_maxdis 10000 -init_KNN_problim 0.9 -init_DBSCAN_minPts 10 -init_DBSCAN_eps 1000 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1

echo "AE 30"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 5 -init_KNN_maxdis 10000 -init_KNN_problim 0.9 -init_DBSCAN_minPts 10 -init_DBSCAN_eps 1000 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1
echo "AE 30, nor"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 5 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1

echo "PCA 30"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1
echo "PCA 30, nor"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1

echo "PCA 100"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_100.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_100.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel sigmoid -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 0.00001 -init_SVM_kernel_r 0.7
echo "PCA 100, nor"
./main.elf -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_100.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_100.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel sigmoid -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 0.001 -init_SVM_kernel_r 0
