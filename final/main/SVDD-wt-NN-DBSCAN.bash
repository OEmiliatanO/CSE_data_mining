#!/bin/bash
DATASET1="../data/Arrhythmia_data_set"
DATASETA="Arrhythmia"
DATASET2="../data/gene_expression_cancer_RNA-Seq_data_set"
DATASETB="gene"
ACCFILE="SVDD-wt-NN-DBSCAN"

RESFILE="SVDD-wt-NN_result.csv"

echo "================== dataset: gene expression cancer ====================="

echo "PCA 100"
time python ../classifying/SVDD-wt-NN/SVDDNN.py $DATASET2/PCA_test_data_100.csv $DATASET2/test_label.csv ./$RESFILE ../classifying/SVDD-wt-NN/model ../classifying/SVDD-wt-NN/parameter
./main.elf -repeats 1 -classifying SVDD-wt-NN -clustering DBSCAN -train_data_path $DATASET2/PCA_train_data_100.csv -train_label_path $DATASET2/train_label.csv -test_data_path $DATASET2/PCA_test_data_100.csv -test_label_path $DATASET2/test_label.csv -SVDD-wt-NN_result_path ./$RESFILE -normalize false -KNOWN_CNT 3 -UNKNOWN_CNT 2 -DBSCAN_minPts 19 -DBSCAN_eps 105.831 -verbose false
