#include <iostream>
#include "KNN.h"
#include "Dataloader.h"

int main()
{
    Dataloader_t dataloader{};
    
    std::cout << "load train data..." << std::endl;
    dataloader.load_train("train.data");

    std::cout << "load test data..." << setd::endl;
    dataloader.load_test("test.data");
    
    KNN_t KNN{dataloader.train_data};
    Data result = KNN.predict(dataloader.test_data);

    std::cout << result << std::endl;

    return 0;
}
