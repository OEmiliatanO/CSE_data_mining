#include <iostream>
#include <memory>
#include <cmath>
#include "src/KNN.h"
#include "src/Brute.h"
#include "src/Annoy.h"
#include "../include/Dataloader.h"
#include "../include/Datatransformer.h"

using data_type = double;
using label_type = int;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
    std::string_view train_path = "../data/testA/train_data.csv";
    std::string_view test_path  = "../data/testA/test_data.csv";
    std::cout << "Train data path is " << train_path << std::endl;
    std::cout << "Test data path is " << test_path << std::endl;

    
    std::size_t k = 9;
    if (argc >= 2) k = (std::size_t)std::atoi(argv[1]);
    std::cout << "k = " << k << std::endl;

    // data is double, label is int
    Dataloader_t<data_type, label_type> dataloader;
    
    std::cout << "Load the train data..." << std::endl;
    dataloader.load_train(train_path);
    //dataloader.load_train(Datatransformer_t<data_type, label_type>::drop_attrs_are_xs(dataloader.train_data, std::vector<std::size_t>{2,3,4}, std::vector<data_type>{0,0,0}));
    //std::cerr << "train data =\n" << dataloader.train_data << std::endl;

    std::cout << "Load the test data..." << std::endl;
    dataloader.load_test(test_path);
    //std::cerr << "test data =\n" << dataloader.test_data << std::endl;
    std::cout << "Complete loading" << std::endl << std::endl;
	std::cout << "===================================================================" << std::endl;

    KNN_t<data_type, label_type> KNN;
    std::cout << "Set knn search algorithm: brute force" << std::endl;
    KNN.set_knn_method(std::make_shared<brute_force<data_type, label_type>>());
    std::cout << "Train the KNN..." << std::endl;
    KNN.train(dataloader.train_data);
    std::cout << "Predict the test data..." << std::endl;
    point_t<label_type> result = KNN.predict(dataloader.test_data, k);

	[[maybe_unused]]auto correct = [](label_type out, label_type y) { return (double)(out == y); };

    auto correct_n = (int)score<label_type>(result, dataloader.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
	
	Dataloader_t<data_type, label_type> dataloader_normal;
	Datatransformer_t<data_type, label_type> datatransformer;
	std::cout << "Transform the data: normalize the dataset..." << std::endl;
    
    std::cout << "Load the train data..." << std::endl;
	dataloader_normal.load_train(datatransformer.normalize(dataloader.train_data));
	//std::cout <<"train data is\n" << dataloader_normal.train_data << std::endl;
    std::cout << "Load the test data..." << std::endl;
	dataloader_normal.load_test(datatransformer.normalize(dataloader.test_data));
    KNN.train(dataloader_normal.train_data);
    std::cout << "Predict the test data..." << std::endl;
    result = KNN.predict(dataloader_normal.test_data, k);

    correct_n = (int)score<label_type>(result, dataloader_normal.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;

    std::cout << "Set knn search algorithm: ANNOY" << std::endl;
    std::size_t maxpoint = 17;
    if (argc >= 3) maxpoint = std::atoi(argv[2]);
    std::cout << "Max point count in the leaf of search tree = " << maxpoint << std::endl;
    KNN.set_knn_method(std::make_shared<annoy<data_type, label_type>>(maxpoint));
    std::cout << "Train the KNN..." << std::endl;
    KNN.train(dataloader.train_data);
    std::cout << "Predict the test data..." << std::endl;
    result = KNN.predict(dataloader.test_data, k);

    correct_n = (int)score<label_type>(result, dataloader.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
	std::cout << "Use the normalized dataset..." << std::endl;
    
    KNN.train(dataloader_normal.train_data);
    std::cout << "Predict the test data..." << std::endl;
    result = KNN.predict(dataloader_normal.test_data, k);

    correct_n = (int)score<label_type>(result, dataloader_normal.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;


    return 0;
}
