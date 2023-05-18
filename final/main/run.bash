#!/bin/bash
DATASET1="../data/Arrhythmia_data_set"
DATASET2="../data/gene_expression_cancer_RNA-Seq_data_set"

#./main.elf -repeats 1 -classifying SVM -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 50 -DBSCAN_minPts 10 -DBSCAN_eps 500 -kmeans_converge_lim 1e-7

#echo ""
#./main.elf -repeats 1 -classifying SVM -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 50 -DBSCAN_minPts 10 -DBSCAN_eps 700 -kmeans_converge_lim 1e-7

#echo ""
#./main.elf -repeats 1 -classifying SVM -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -SVM_converge_lim 1e-7 -SVM_punishment 1 -DBSCAN_minPts 10 -DBSCAN_eps 500 -kmeans_converge_lim 1e-7

#echo ""
#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 110 -KNN_problim 0.5 -KNN_method brute -DBSCAN_minPts 3 -DBSCAN_eps 240 -kmeans_converge_lim 1e-7

#echo ""
#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 45 -KNN_maxdis 3000 -KNN_problim 0.6 -KNN_method brute -SVM_converge_lim 1e-7 -SVM_punishment 50 -DBSCAN_minPts 10 -DBSCAN_eps 500 -kmeans_converge_lim 1e-7

#echo ""
#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 21 -KNN_maxdis 120 -KNN_problim 0.5 -KNN_method brute -SVM_converge_lim 1e-7 -SVM_punishment 50 -DBSCAN_minPts 25 -DBSCAN_eps 140

#echo ""
#./main.elf -repeats 1 -classifying KNN -clustering kmeans -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 5 -KNN_maxdis 200 -KNN_problim 0.6 -KNN_method brute -kmeans_converge_lim 1e-7

#./main.elf -repeats 1 -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 11 -KNN_maxdis 200 -KNN_problim 0.5 -KNN_method brute -SVM_converge_lim 1e-7 -SVM_punishment 1 -DBSCAN_minPts 10 -DBSCAN_eps 460 -kmeans_converge_lim 1e-7

#./main.elf -repeats 1 -classifying SVM -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 21 -KNN_maxdis 700 -KNN_problim 0.5 -KNN_method brute -SVM_converge_lim 1e-7 -SVM_punishment 1 -DBSCAN_minPts 22 -DBSCAN_eps 80 -kmeans_converge_lim 1e-7

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 7 -KNN_maxdis 90 -KNN_problim 0.6 -KNN_method brute -SVM_converge_lim 1e-7 -SVM_punishment 1 -DBSCAN_minPts 10 -DBSCAN_eps 150 -kmeans_converge_lim 1e-7

#./main.elf -repeats 1 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 7 -KNN_maxdis 90 -KNN_problim 0.6 -KNN_method brute -SVM_converge_lim 1e-7 -SVM_punishment 1 -DBSCAN_minPts 10 -DBSCAN_eps 100 -kmeans_converge_lim 1e-7
