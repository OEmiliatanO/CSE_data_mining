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
    Dataloader_t dataloader;
    
    std::cout << "load train data..." << std::endl;
    dataloader.load_train(train_path);
    //std::cerr << "train data =\n" << dataloader.train_data << std::endl;

    std::cout << "load test data..." << std::endl;
    dataloader.load_test(test_path);
    //std::cerr << "test data =\n" << dataloader.test_data << std::endl;
    
    decision_tree_t tree;
    std::cout << "set criterion(entropy)..." << std::endl;
    tree.set_criterion(std::unique_ptr<DT_criterion>(new entropy_crit()));
    std::cout << "build tree..." << std::endl;
    tree.build(dataloader.train_data);
    //std::cout << "the decision tree is like:\n"<< tree << std::endl;
    std::cout << "valid the tree..." << std::endl;
    dataset_t validation = tree.predict(dataloader.train_data);
    std::cout << "predict test data..." << std::endl;
    dataset_t result = tree.predict(dataloader.test_data);
    
    int error = 0;
    for (std::size_t i = 0; i < validation.size(); ++i)
        error += !(abs(validation[i].label - dataloader.train_data[i].label) < minerr);
    std::cout << "error on train data: " << error << std::endl;

    int correct = 0;
    for (std::size_t i = 0; i < result.size(); ++i)
    {
        correct += (abs(result[i].label - dataloader.test_data[i].label) < minerr);
    }

    std::cout << "the final accuracy is " << (double)correct/result.size()*100 << '%' << std::endl;

    std::cout << "=======================================================" << std::endl;
	std::cout << "transform data: normalize..." << std::endl;
	Datatransformer_t datatransformer;
	Dataloader_t dataloader_normal;
	dataloader_normal.load_train(datatransformer.normalize(dataloader.train_data));
	//std::cerr << "normalized train data =\n" << dataloader_normal.train_data << std::endl;
	dataloader_normal.load_test(datatransformer.normalize(dataloader.test_data));
    tree.build(dataloader_normal.train_data);
    std::cout << "valid the tree..." << std::endl;
    validation = tree.predict(dataloader_normal.train_data);
    
    error = 0;
    for (std::size_t i = 0; i < validation.size(); ++i)
        error += (validation[i].label != dataloader_normal.train_data[i].label);
    std::cout << "error on train data: " << error << std::endl;

    std::cout << "predict test data..." << std::endl;
    result = tree.predict(dataloader_normal.test_data);
    correct = 0;
    for (std::size_t i = 0; i < result.size(); ++i)
    {
        correct += (abs(result[i].label - dataloader_normal.test_data[i].label) < minerr);
    }

    std::cout << "the final accuracy is " << (double)correct/result.size()*100 << '%' << std::endl;


	/*
    std::cout << "set criterion(gini)..." << std::endl;
    tree.set_criterion(std::unique_ptr<DT_criterion>(new gini_crit()));
    std::cout << "build tree..." << std::endl;
    tree.build(dataloader.train_data);
    std::cout << "valid the tree..." << std::endl;
    validation = tree.predict(dataloader.train_data);
    std::cout << "predict test data..." << std::endl;
    result = tree.predict(dataloader.test_data);
    
    error = 0;
    for (std::size_t i = 0; i < validation.size(); ++i)
    {
        error += !(abs(validation[i].label - dataloader.train_data[i].label) < minerr);
    }
    std::cout << "error on train data: " << error << std::endl;

    correct = 0;
    for (std::size_t i = 0; i < result.size(); ++i)
    {
        correct += (abs(result[i].label - dataloader.test_data[i].label) < minerr);
    }

    std::cout << "the final accuracy is " << (double)correct/result.size()*100 << '%' << std::endl;
	*/

    return 0;
}