#!/bin/bash
DATASET1="../data/Arrhythmia_data_set"
DATASETA="Arrhythmia"
DATASET2="../data/gene_expression_cancer_RNA-Seq_data_set"
DATASETB="gene"
ACCFILE="KNN-DBSCAN"

echo "======================== dataset: arrhythmia ====================="

echo "original"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 120 -KNN_problim 0.7 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 260 -verbose false #> $ACCFILE-$DATASETA-original.acc
echo "original, nor"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/train_data.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/test_data.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 15 -KNN_problim 0.7 -KNN_method brute -DBSCAN_minPts 20 -DBSCAN_eps 50 -verbose false #> $ACCFILE-$DATASETA-original-nor.acc

echo "AE 32"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 20 -KNN_problim 0.8 -KNN_method brute -DBSCAN_minPts 9 -DBSCAN_eps 10 -verbose false #> $ACCFILE-$DATASETA-AE_32.acc
echo "AE 32, nor"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/AE_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/AE_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 11 -KNN_maxdis 15 -KNN_problim 0.7 -KNN_method brute -DBSCAN_minPts 5 -DBSCAN_eps 5 -verbose false #> $ACCFILE-$DATASETA-AE_32-nor.acc

echo "PCA 32"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize false -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 21 -KNN_maxdis 500 -KNN_problim 0.7 -KNN_method brute -DBSCAN_minPts 5 -DBSCAN_eps 500 -verbose false #> $ACCFILE-$DATASETA-PCA_32.acc
echo "PCA 32, nor"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET1/PCA_train_data_32.csv -train_label_path $DATASET1/train_label.csv -test_data_path $DATASET1/PCA_test_data_32.csv -test_label_path $DATASET1/test_label.csv -normalize true -KNOWN_CNT 8 -UNKNOWN_CNT 5 -KNN_k 5 -KNN_maxdis 20 -KNN_problim 0.9 -KNN_method brute -DBSCAN_minPts 5 -DBSCAN_eps 17 -verbose false #> $ACCFILE-$DATASETA-PCA_32-nor.acc

echo "================== dataset: gene expression cancer ====================="

echo "original"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 101 -KNN_maxdis 10000 -KNN_problim 0.9 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 1000 -verbose false #> $ACCFILE-$DATASETB-original.acc
echo "original, nor"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/train_data.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/test_data.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 101 -KNN_maxdis 10000 -KNN_problim 0.9 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 1000 -verbose false #> $ACCFILE-$DATASETB-original-nor.acc

echo "AE 30"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 15 -KNN_maxdis 200 -KNN_problim 0.8 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 100 -verbose false #> $ACCFILE-$DATASETB-AE_30.acc
echo "AE 30, nor"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/AE_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/AE_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 7 -KNN_maxdis 12 -KNN_problim 0.8 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 10 -verbose false #> $ACCFILE-$DATASETB-AE_30-nor.acc

echo "PCA 30"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 7 -KNN_maxdis 90 -KNN_problim 0.6 -KNN_method brute -DBSCAN_minPts 10 -DBSCAN_eps 100 -verbose false #> $ACCFILE-$DATASETB-PCA_30.acc
echo "PCA 30, nor"
./main.elf -repeats 10 -classifying KNN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_30.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_30.csv -test_label_path $DATASET2/test_label.csv -normalize true -KNOWN_CNT 3 -UNKNOWN_CNT 2 -KNN_k 11 -KNN_maxdis 15 -KNN_problim 0.8 -KNN_method brute -DBSCAN_minPts 15 -DBSCAN_eps 15 -verbose false #> $ACCFILE-$DATASETB-PCA_30-nor.acc
