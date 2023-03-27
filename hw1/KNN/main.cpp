#include <iostream>
#include <memory>
#include <cmath>
#include "src/KNN.h"
#include "src/Brute.h"
#include "../include/Dataloader.h"
#include "../include/Datatransformer.h"

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
    std::string_view train_path = "../data/testA/train_data.csv";
    std::string_view test_path  = "../data/testA/test_data.csv";
    std::size_t k = 5;
    Dataloader_t dataloader;
    
    std::cout << "load train data..." << std::endl;
    dataloader.load_train(train_path);
    //std::cerr << "train data =\n" << dataloader.train_data << std::endl;

    std::cout << "load test data..." << std::endl;
    dataloader.load_test(test_path);
    //std::cerr << "test data =\n" << dataloader.test_data << std::endl;
    
    KNN_t KNN{dataloader.train_data};
    KNN.set_knn_method(std::unique_ptr<brute_force>(new brute_force{}));
    std::cout << "predict the test data..." << std::endl;
    dataset_t result = KNN.predict(dataloader.test_data, k);

	//auto correct = [](int out, int y) { return (double)(out == y); };
	auto acc = [&](int out, int y) { return (double)(out == y)*100/result.size(); };
    //std::cout << "the final accuracy is " << score(result, dataloader.test_data, correct) * 100 / result.size() << '%' << std::endl;
    std::cout << "the final accuracy is " << score(result, dataloader.test_data, acc) << '%' << std::endl;
	std::cout << "===================================================================" << std::endl;
	
	Dataloader_t dataloader_normal;
	Datatransformer_t datatransformer;
	std::cout << "transform the data: normalize the dataset..." << std::endl;
	dataloader_normal.load_train(datatransformer.normalize(dataloader.train_data));
	dataloader_normal.load_test(datatransformer.normalize(dataloader.test_data));
	KNN_t KNN_normal{dataloader_normal.train_data};
	KNN_normal.set_knn_method(std::unique_ptr<brute_force>(new brute_force{}));
    std::cout << "predict the test data..." << std::endl;
    result = KNN_normal.predict(dataloader_normal.test_data, k);

    //std::cout << "the final accuracy is " << score(result, dataloader_normal.test_data, correct) * 100 / result.size() << '%' << std::endl;
    std::cout << "the final accuracy is " << score(result, dataloader_normal.test_data, acc) << '%' << std::endl;

    return 0;
}
