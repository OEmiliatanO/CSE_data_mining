#include "svm.h"
#include <iostream>
using data_type = double;
using label_type = int;

int main()
{
    Dataloader_t<data_type, label_type> dataloader;
    dataloader.load_train("../data/testA/train_data.csv");
    dataloader.load_test("../data/testA/test_data.csv");

    svm_t<data_type, label_type> svm(dataloader.train_data, dataloader.test_data);
    svm.train_ga( 
        /*level*/ 300,
        /*mutation_rate*/ 0.05, 
        /*elite_save_percent*/ 0.1, 
        /*variation*/ 5, 
        /*populations*/ 250
    );
    std::cout << "Correct_Rate: " << svm.correct_rate() << std::endl;

    return 0;
}