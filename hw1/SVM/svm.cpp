#include "svm.h"

svm_t :: svm_t()
{

}

using data_type = double;
using label_type = int;

int main()
{
    Dataloader_t<data_type, label_type> dataloader;
    dataloader.load_train("../data/testA/train_data.csv");
    std::cout << dataloader.train_data;
    return 0;
}