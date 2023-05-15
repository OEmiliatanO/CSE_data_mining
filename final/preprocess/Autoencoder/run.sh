Aout=32
python main.py 279 $Aout ../../data/Arrhythmia_data_set/train_data.csv ../../data/Arrhythmia_data_set/train_label.csv ../../data/Arrhythmia_data_set/test_data.csv ../../data/Arrhythmia_data_set/test_label.csv ../../data/Arrhythmia_data_set/AE_train_data_$Aout.csv ../../data/Arrhythmia_data_set/AE_test_data_$Aout.csv loss.png
Aout=24
python main.py 279 $Aout ../../data/Arrhythmia_data_set/train_data.csv ../../data/Arrhythmia_data_set/train_label.csv ../../data/Arrhythmia_data_set/test_data.csv ../../data/Arrhythmia_data_set/test_label.csv ../../data/Arrhythmia_data_set/AE_train_data_$Aout.csv ../../data/Arrhythmia_data_set/AE_test_data_$Aout.csv loss.png
#Bout=30
#python main.py 20531 30  ../../data/gene_expression_cancer_RNA-Seq_data_set/train_data.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/train_label.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/test_data.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/test_label.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/AE_train_data_$Bout.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/AE_test_data_$Bout.csv loss.png
