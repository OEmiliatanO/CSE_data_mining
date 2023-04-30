#include <iostream>
#include <memory>
#include <cmath>
#include <cstring>
#include <chrono>
#include "src/decision_tree.h"
#include "src/DT_criterion.h"
#include "src/random_forest.h"
#include "../include/Dataloader.h"
#include "../include/Datatransformer.h"

using data_t = double;
using label_t = int;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
// ./main.elf --repeat $repeat --traindata $DATASET/train_data.csv --testdata $DATASET/test_data.csv --normalize $normalize --search_method decision_tree  --criterion entropy >> $LOGFILE
// [0]        [1]      [2]     [3]         [4]                     [5]        [6]                    [7]         [8]        [9]             [10]           [11]        [12]
// ./main.elf --repeat $repeat --traindata $DATASET/train_data.csv --testdata $DATASET/test_data.csv --normalize $normalize --search_method random_forest  --criterion entropy -n   $n   >> $LOGFILE
// [0]        [1]      [2]     [3]         [4]                     [5]        [6]                    [7]         [8]        [9]             [10]           [11]        [12]    [13] [14]
    std::string_view train_path = argv[4];
    std::string_view test_path  = argv[6];
    //std::cerr << "Train data path is " << train_path << std::endl;
    //std::cerr << "Test data path is " << test_path << std::endl;
    Dataloader_t<data_t, label_t> dataloader;
    
    //std::cerr << "Load train data..." << std::endl;
    dataloader.load_train(train_path);
    //dataloader.load_train(Datatransformer_t<data_t, label_t>::drop_attrs_are_xs(dataloader.train_data, std::vector<std::size_t>{2,3,4}, std::vector<data_t>{0,0,0}));

    //std::cerr << "Load test data..." << std::endl;
    dataloader.load_test(test_path);
    dataloader.load_test(dataloader.test_data);
	if (strcmp(argv[8], "true") == 0)
	{
		dataloader.load_train(Datatransformer_t<data_t, label_t>::normalize(dataloader.train_data));
		dataloader.load_test(Datatransformer_t<data_t, label_t>::normalize(dataloader.test_data));
	}
    //std::cerr << "Complete loading" << std::endl << std::endl;
	//std::cerr << "===================================================================" << std::endl;
    
	std::size_t repeat = (std::size_t)std::atoi(argv[2]);
	double macc = 0;
	double stand = 0;
	double sum = 0, sum2 = 0;
	std::chrono::steady_clock::time_point st = std::chrono::steady_clock::now();
	if (strcmp(argv[10], "decision_tree") == 0)
	{
		for (std::size_t t = 0; t < repeat; ++t)
		{
			//std::cerr << "Decision tree ..." << std::endl;
			decision_tree_t<data_t, label_t> tree;
			//std::cerr << "Set criterion(entropy)..." << std::endl;
			if (strcmp(argv[12], "entropy"))
				tree.set_criterion(std::make_shared<entropy_crit<label_t>>());
			else if (strcmp(argv[12], "gini"))
				tree.set_criterion(std::make_shared<gini_crit<label_t>>());
			//std::cerr << "Build tree..." << std::endl;
			tree.build(dataloader.train_data);

			//std::cerr << "Predict test data..." << std::endl;
			auto result = tree.predict(dataloader.test_data);
			auto correct = [](int out, int y) { return (double)(out == y); };
			auto correct_n = (int)score<label_t>(result, dataloader.test_data.label, correct);
			double acc = (double)correct_n/result.size()*100;
			macc += acc;
			sum += acc;
			sum2 += acc*acc;
		}
	}
	else if (strcmp(argv[10], "random_forest") == 0)
	{
		for (std::size_t t = 0; t < repeat; ++t)
		{
			//std::cerr << "Random forest ..." << std::endl;
			std::size_t n = std::atoi(argv[14]);
			//std::cerr << "Create random forest with " << n << " decision trees..." << std::endl;
			random_forest_t<data_t, label_t> forest{0, 0, n};
			//std::cerr << "Set criterion(entropy)..." << std::endl;
			if (strcmp(argv[12], "entropy"))
				forest.set_criterion(std::make_shared<entropy_crit<label_t>>());
			else if (strcmp(argv[12], "gini"))
				forest.set_criterion(std::make_shared<gini_crit<label_t>>());
			//std::cerr << "Build tree..." << std::endl;
			forest.build(dataloader.train_data);

			//std::cerr << "Predict test data..." << std::endl;
			auto result = forest.predict(dataloader.test_data);
			auto correct = [](int out, int y) { return (double)(out == y); };
			auto correct_n = (int)score<label_t>(result, dataloader.test_data.label, correct);
			double acc = (double)correct_n/result.size()*100;
			macc += acc;
			sum += acc;
			sum2 += acc*acc;
		}
	}
	std::chrono::steady_clock::time_point ed = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count() / 1000000.0 / repeat;
	stand = sqrt(abs(sum2*repeat - sum*sum))/repeat;
	macc /= repeat;
	std::cout << macc << " " << stand << " " << duration << std::endl;

    return 0;
}
