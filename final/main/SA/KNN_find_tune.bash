#!/bin/bash
DATASET1="../../data/Arrhythmia_data_set"
DATASETA="Arrhythmia"
DATASET2="../../data/gene_expression_cancer_RNA-Seq_data_set"
DATASETB="gene"

echo ====================$DATASETA========================
echo "=========KNN-kmeans=========="
echo "original"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10
echo "original, nor"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10

echo "AE 32"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10
echo "AE 32, nor"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10

echo "PCA 32"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10
echo "PCA 32, nor"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 10 -init_KNN_k 13 -init_DBSCAN_minPts 10

echo "=========KNN-DBSCAN=========="
echo "original"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15 -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20
echo "original, nor"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10  -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20

echo "AE 32"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20
echo "AE 32, nor"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20

echo "PCA 32"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20
echo "PCA 32, nor"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_maxdis 15  -init_KNN_problim 0.7 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_KNN_k 13 -init_DBSCAN_minPts 20

echo ====================$DATASETB========================
echo "=========KNN-kmeans=========="
echo "original"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 13 -init_KNN_maxdis 1000 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "original, nor"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 13 -init_KNN_maxdis 1000 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "AE 30"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 13 -init_KNN_maxdis 1000 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20
echo "AE 30, nor"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 13 -init_KNN_maxdis 1000 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "PCA 30"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20
echo "PCA 30, nor"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "PCA 100"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET2/PCA_train_data_100.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_100.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20
echo "PCA 100, nor"
./main.elf -classifying KNN -clustering kmeans -train_data_path $DATASET2/PCA_train_data_100.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_100.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1 -init_DBSCAN_eps 50 -init_DBSCAN_minPts 20

echo "=========KNN-DBSCAN=========="
echo "original"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 5 -init_KNN_maxdis 10000 -init_KNN_problim 0.9 -init_DBSCAN_minPts 10 -init_DBSCAN_eps 1000 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1
echo "original, nor"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 5 -init_KNN_maxdis 10000 -init_KNN_problim 0.9 -init_DBSCAN_minPts 10 -init_DBSCAN_eps 1000 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1

echo "AE 30"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 5 -init_KNN_maxdis 10000 -init_KNN_problim 0.9 -init_DBSCAN_minPts 10 -init_DBSCAN_eps 1000 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1
echo "AE 30, nor"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 5 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1

echo "PCA 30"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1
echo "PCA 30, nor"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1

echo "PCA 100"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_100.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_100.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1
echo "PCA 100, nor"
./main.elf -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_100.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_100.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -SVM_kernel linear -T 100 -Rt 0.75 -EndT 0.1 -n 10 -init_KNN_k 7 -init_KNN_maxdis 90 -init_KNN_problim 0.6 -init_KNN_method brute -init_DBSCAN_minPts 10 -init_DBSCAN_eps 100 -init_SVM_kernel_gamma 2 -init_SVM_kernel_r 1
