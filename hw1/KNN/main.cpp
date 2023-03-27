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
    std::cout << "Train data path is " << train_path << std::endl;
    std::cout << "Test data path is " << test_path << std::endl;

    std::size_t k = 5;
    std::cout << "K = " << k << std::endl;

    Dataloader_t dataloader;
    
    std::cout << "Load the train data..." << std::endl;
    dataloader.load_train(train_path);
    //std::cerr << "train data =\n" << dataloader.train_data << std::endl;

    std::cout << "Load the test data..." << std::endl;
    dataloader.load_test(test_path);
    //std::cerr << "test data =\n" << dataloader.test_data << std::endl;
    std::cout << "Complete loading" << std::endl << std::endl;
	std::cout << "===================================================================" << std::endl;

    KNN_t KNN;
    std::cout << "Set knn search algorithm: brute force" << std::endl;
    KNN.set_knn_method(std::unique_ptr<brute_force>(new brute_force{}));
    std::cout << "Train the KNN..." << std::endl;
    KNN.train(dataloader.train_data);
    std::cout << "Predict the test data..." << std::endl;
    dataset_t result = KNN.predict(dataloader.test_data, k);

	[[maybe_unused]]auto correct = [](int out, int y) { return (double)(out == y); };
	[[maybe_unused]]auto acc = [&](int out, int y) { return (double)(out == y)*100/result.size(); };
    //std::cout << "the final accuracy is " << score(result, dataloader.test_data, correct) * 100 / result.size() << '%' << std::endl;
    auto correct_n = (int)score(result, dataloader.test_data, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
	
	Dataloader_t dataloader_normal;
	Datatransformer_t datatransformer;
	std::cout << "Transform the data: normalize the dataset..." << std::endl;
    
    std::cout << "Load the train data..." << std::endl;
	dataloader_normal.load_train(datatransformer.normalize(dataloader.train_data));
    std::cout << "Load the test data..." << std::endl;
	dataloader_normal.load_test(datatransformer.normalize(dataloader.test_data));
	
    KNN_t KNN_normal{dataloader_normal.train_data};
	KNN_normal.set_knn_method(std::unique_ptr<brute_force>(new brute_force{}));
    KNN.train(dataloader_normal.train_data);
    std::cout << "Predict the test data..." << std::endl;
    result = KNN_normal.predict(dataloader_normal.test_data, k);

    correct_n = (int)score(result, dataloader_normal.test_data, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;

    return 0;
}
