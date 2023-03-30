#include <iostream>
#include <memory>
#include <cmath>
#include "src/decision_tree.h"
#include "src/DT_criterion.h"
#include "src/random_forest.h"
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
    Dataloader_t<data_type, label_type> dataloader;
    
    std::cout << "Load train data..." << std::endl;
    dataloader.load_train(train_path);
    dataloader.load_train(Datatransformer_t<data_type, label_type>::drop_attrs_are_xs(dataloader.train_data, std::vector<std::size_t>{2,3,4}, std::vector<data_type>{0,0,0}));
    //std::cerr << "train data =\n" << dataloader.train_data << std::endl;

    std::cout << "Load test data..." << std::endl;
    dataloader.load_test(test_path);
    dataloader.load_test(dataloader.test_data);
    //std::cerr << "test data =\n" << dataloader.test_data << std::endl;
    std::cout << "Complete loading" << std::endl << std::endl;
	std::cout << "===================================================================" << std::endl;
    
    std::cout << "Random forest ..." << std::endl;
    std::size_t n = 35;
    if (argc >= 2) n = atoi(argv[1]);
    std::cout << "Create random forest with " << n << " decision trees..." << std::endl;
    random_forest_t<data_type, label_type> forest{0, 0, n};
    
    std::cout << "Set criterion(entropy)..." << std::endl;
    forest.set_criterion(std::make_shared<entropy_crit<label_type>>());
    
    std::cout << "Build tree..." << std::endl;
    forest.build(dataloader.train_data);
    
    std::cout << "Valid the tree..." << std::endl;
    point_t<label_type> result = forest.predict(dataloader.train_data);
    
    [[maybe_unused]]auto correct = [](int out, int y) { return (double)(out == y); };
    auto correct_n = (int)score<label_type>(result, dataloader.train_data.label, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;
    
    std::cout << "Predict test data..." << std::endl;
    result = forest.predict(dataloader.test_data);
    
    correct_n = (int)score<label_type>(result, dataloader.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
	
    std::cout << "Transform data: normalize..." << std::endl;
	Datatransformer_t<data_type, label_type> datatransformer;
	Dataloader_t<data_type, label_type> dataloader_normal;
	dataloader_normal.load_train(datatransformer.normalize(dataloader.train_data));
	dataloader_normal.load_test(datatransformer.normalize(dataloader.test_data));
    
    forest.build(dataloader_normal.train_data);

    std::cout << "Valid the tree..." << std::endl;
    result = forest.predict(dataloader_normal.train_data);
    
    correct_n = (int)score<label_type>(result, dataloader_normal.train_data.label, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;
    
    std::cout << "Predict test data..." << std::endl;
    result = forest.predict(dataloader_normal.test_data);

    correct_n = (int)score<label_type>(result, dataloader_normal.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
    
    std::cout << "Decision tree ..." << std::endl;
    decision_tree_t<data_type, label_type> tree;

    std::cout << "Set criterion(entropy)..." << std::endl;
    tree.set_criterion(std::make_shared<entropy_crit<label_type>>());
    std::cout << "Build tree..." << std::endl;
    tree.build(dataloader.train_data);
    //std::cout << "the decision tree is like:\n"<< tree << std::endl;
    std::cout << "Valid the tree..." << std::endl;
    result = tree.predict(dataloader.train_data);
    
    correct_n = (int)score<label_type>(result, dataloader.train_data.label, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;

    std::cout << "Predict test data..." << std::endl;
    result = tree.predict(dataloader.test_data);
    
    correct_n = (int)score<label_type>(result, dataloader.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;

	std::cout << "Transform data: normalize..." << std::endl;


	dataloader_normal.load_train(datatransformer.normalize(dataloader.train_data));
	//std::cerr << "normalized train data =\n" << dataloader_normal.train_data << std::endl;
	dataloader_normal.load_test(datatransformer.normalize(dataloader.test_data));
    tree.build(dataloader_normal.train_data);
    std::cout << "Valid the tree..." << std::endl;
    result = tree.predict(dataloader_normal.train_data);
    
    correct_n = (int)score<label_type>(result, dataloader_normal.train_data.label, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;
    
    std::cout << "Predict test data..." << std::endl;
    result = tree.predict(dataloader_normal.test_data);

    correct_n = (int)score<label_type>(result, dataloader_normal.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
	
    std::cout << "Set criterion(gini)..." << std::endl;
    tree.set_criterion(std::make_shared<gini_crit<label_type>>());
    std::cout << "Build tree(by raw data)..." << std::endl;
    tree.build(dataloader.train_data);
    std::cout << "Valid the tree..." << std::endl;
    result = tree.predict(dataloader.train_data);

    correct_n = (int)score<label_type>(result, dataloader.train_data.label, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;
    
    std::cout << "Predict test data..." << std::endl;
    result = tree.predict(dataloader.test_data);
    
    correct_n = (int)score<label_type>(result, dataloader.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;
    
    std::cout << "Build tree(by normalized data)..." << std::endl;
    tree.build(dataloader_normal.train_data);
    std::cout << "Valid the tree..." << std::endl;
    result = tree.predict(dataloader_normal.train_data);

    correct_n = (int)score<label_type>(result, dataloader_normal.train_data.label, correct);
    std::cout << std::endl << "The score is " << correct_n << "/" << result.size() << " on original train data." << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << " on original train data." << std::endl << std::endl;
    
    std::cout << "Predict test data..." << std::endl;
    result = tree.predict(dataloader_normal.test_data);
    
    correct_n = (int)score<label_type>(result, dataloader_normal.test_data.label, correct);
    std::cout << std::endl << "The socre is " << correct_n << "/" << result.size() << std::endl;
    std::cout << "The accuracy is " << (double)correct_n/result.size() << std::endl;
	std::cout << "===================================================================" << std::endl;

    return 0;
}
