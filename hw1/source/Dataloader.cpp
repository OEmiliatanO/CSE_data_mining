#include "../include/Dataloader.h"
#include "../include/Data.h"

// unit test
#ifdef DATALOADER_TEST
int main()
{
    Dataloader_t<double, int> dataloader;
    std::cout << "load test data..." << std::endl;
    dataloader.load_train("../data/testA/test_data.csv");
    std::cout << dataloader.train_data << std::endl;
    std::cout << "load train data..." << std::endl;
    dataloader.load_test("../data/testA/train_data.csv");
    std::cout << dataloader.test_data << std::endl;
    return 0;
}
#endif
