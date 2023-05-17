./drop_id_description.bash train_data.csv
./drop_id_description.bash test_data.csv
./drop_id_description.bash train_label.csv
./drop_id_description.bash test_label.csv

cat train_label.csv | python label2int.py > _
mv _ train_label.csv
cat test_label.csv | python label2int.py > _
mv _ test_label.csv
