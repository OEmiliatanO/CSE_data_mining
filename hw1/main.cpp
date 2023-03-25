#include <iostream>
#include <memory>
#include <cmath>
#include "src/KNN.h"
#include "src/Dataloader.h"
#include "src/Brute.h"

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
    std::string_view train_path = "data/testA/train_data.csv";
    std::string_view test_path  = "data/testA/test_data.csv";
    std::size_t k = 5;
    Dataloader_t dataloader;
    
    std::cout << "load train data..." << std::endl;
    dataloader.load_train(train_path);
    std::cerr << "train data =\n" << dataloader.train_data << std::endl;

    std::cout << "load test data..." << std::endl;
    dataloader.load_test(test_path);
    std::cerr << "test data =\n" << dataloader.test_data << std::endl;
    
    KNN_t KNN{dataloader.train_data};
    KNN.set_knn_method(std::unique_ptr<brute_force>(new brute_force{}));
    std::cout << "predict the test data..." << std::endl;
    dataset_t result = KNN.predict(dataloader.test_data, k);

    int correct = 0;
    for (std::size_t i = 0; i < result.size(); ++i)
    {
        correct += (abs(result[i].label - dataloader.test_data[i].label) < 1e-8);
    }

    std::cout << "the final accuracy is " << (double)correct/result.size()*100 << '%' << std::endl;

    return 0;
}
