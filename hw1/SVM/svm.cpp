#include "svm.h"

#ifdef SVMTEST

using data_type = double;
using label_type = int;

int main()
{
    Dataloader_t<data_type, label_type> dataloader;
    dataloader.load_train("../data/testA/train_data.csv");
    for (std::size_t i = 0; i < dataloader.train_data.size(); ++i)
        std::cout << dataloader.train_data.data[i] << ", " << dataloader.train_data.label[i] << std::endl;

    svm_t<data_type, label_type> svm(dataloader.train_data, dataloader.test_data);

    for(auto x: svm.dataset_train) 
        std::cout << x << std::endl;

    
    return 0;
}

#endif