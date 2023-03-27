#include <iostream>
#include <memory>
#include <cmath>
#include "src/decision_tree.h"
#include "src/DT_criterion.h"
#include "../include/Dataloader.h"
#include "../include/Datatransformer.h"

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
    std::string_view train_path = "../data/testA/train_data.csv";
    std::string_view test_path  = "../data/testA/test_data.csv";
    std::cout << "Train data path is " << train_path << std::endl;
    std::cout << "Test data path is " << test_path << std::endl;
    Dataloader_t dataloader;
    
    std::cout << "Load train data..." << std::endl;
    dataloader.load_train(train_path);
    //std::cerr << "train data =\n" << dataloader.train_data << std::endl;

    std::cout << "Load test data..." << std::endl;
    dataloader.load_test(test_path);
    //std::cerr << "test data =\n" << dataloader.test_data << std::endl;
    std::cout << "Complete loading" << std::endl << std::endl;
	std::cout << "===================================================================" << std::endl;
    
    decision_tree_t tree;

    std::cout << "Set criterion(entropy)..." << std::endl;
    tree.set_criterion(std::unique_ptr<DT_criterion>(new entropy_crit()));
    std::cout << "Build tree..." << std::endl;
    tree.build(dataloader.train_data);
    //std::cout << "the decision tree is like:\n"<< tree << std::endl;
    std::cout << "Valid the tree..." << std::endl;
    dataset_t result = tree.predict(dataloader.train_data);
    
    [[maybe_unused]]auto correct = [](int out, int y) { return (double)(out == y); };
	[[maybe_unused]]auto acc = [&](int out, int y) { return (double)(out == y)*100/result.size(); };
    auto correct_n = (int)score(result, dataloader.train_data, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;

    std::cout << "Predict test data..." << std::endl;
    result = tree.predict(dataloader.test_data);
    
    correct_n = (int)score(result, dataloader.test_data, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;

	std::cout << "Transform data: normalize..." << std::endl;
	Datatransformer_t datatransformer;
	Dataloader_t dataloader_normal;
	dataloader_normal.load_train(datatransformer.normalize(dataloader.train_data));
	//std::cerr << "normalized train data =\n" << dataloader_normal.train_data << std::endl;
	dataloader_normal.load_test(datatransformer.normalize(dataloader.test_data));
    tree.build(dataloader_normal.train_data);
    std::cout << "Valid the tree..." << std::endl;
    result = tree.predict(dataloader_normal.train_data);
    
    correct_n = (int)score(result, dataloader_normal.train_data, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;
    
    std::cout << "Predict test data..." << std::endl;
    result = tree.predict(dataloader_normal.test_data);

    correct_n = (int)score(result, dataloader_normal.test_data, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
	
    std::cout << "Set criterion(gini)..." << std::endl;
    tree.set_criterion(std::unique_ptr<DT_criterion>(new gini_crit()));
    std::cout << "Build tree(by raw data)..." << std::endl;
    tree.build(dataloader.train_data);
    std::cout << "Valid the tree..." << std::endl;
    result = tree.predict(dataloader.train_data);

    correct_n = (int)score(result, dataloader.train_data, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;
    
    std::cout << "Predict test data..." << std::endl;
    result = tree.predict(dataloader.test_data);
    
    correct_n = (int)score(result, dataloader.test_data, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
    
    std::cout << "Build tree(by normalized data)..." << std::endl;
    tree.build(dataloader_normal.train_data);
    std::cout << "Valid the tree..." << std::endl;
    result = tree.predict(dataloader_normal.train_data);

    correct_n = (int)score(result, dataloader_normal.train_data, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;
    
    std::cout << "Predict test data..." << std::endl;
    result = tree.predict(dataloader_normal.test_data);
    
    correct_n = (int)score(result, dataloader_normal.test_data, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
 
    return 0;
}
