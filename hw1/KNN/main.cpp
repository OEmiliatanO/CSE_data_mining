#include <iostream>
#include <memory>
#include <cmath>
#include "src/KNN.h"
#include "src/Brute.h"
#include "src/Annoy.h"
#include "../include/Dataloader.h"
#include "../include/Datatransformer.h"

using data_t = double;
using label_t = int;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
// ./main.elf --repeat 100 --traindata ../data/testA/train_data.csv --testdata ../data/testA/test_data.csv --normalize true --search_method brute --k  9  
// [0]        [1]      [2] [3]         [4]                          [5]        [6]                         [7]         [8]  [9]             [10]  [11] [12]
// ./main.elf --repeat 100 --traindata ../data/testA/train_data.csv --testdata ../data/testA/test_data.csv --normalize true --search_method annoy --k  9    --annoy_search_method dfs  --maxpoint 17
// [0]        [1]      [2] [3]         [4]                          [5]        [6]                         [7]         [8]  [9]             [10]  [11] [12] [13]                  [14] [15]       [16]
// ./main.elf --repeat 100 --traindata ../data/testA/train_data.csv --testdata ../data/testA/test_data.csv --normalize true --search_method annoy --k  9    --annoy_search_method bfs  --maxpoint 17   --bfs_threhold 5
// [0]        [1]      [2] [3]         [4]                          [5]        [6]                         [7]         [8]  [9]             [10]  [11] [12] [13]                  [14]  [15]       [16] [17]           [18]
	
    std::string_view train_path = argv[4];
    std::string_view test_path  = argv[6];
    std::cerr << "Train data path is " << train_path << std::endl;
    std::cerr << "Test data path is " << test_path << std::endl;

    
    std::size_t k = (std::size_t)std::atoi(argv[12]);

    // data is double, label is int
    Dataloader_t<data_t, label_t> dataloader;
    
    std::cerr << "Load the train data..." << std::endl;
    dataloader.load_train(train_path);
    //dataloader.load_train(Datatransformer_t<data_type, label_type>::drop_attrs_are_xs(dataloader.train_data, std::vector<std::size_t>{2,3,4}, std::vector<data_type>{0,0,0}));

    std::cerr << "Load the test data..." << std::endl;
    dataloader.load_test(test_path);
    std::cerr << "Complete loading" << std::endl << std::endl;
	if (argv[8] == "true")
	{
		std::cerr << "Normalize the dataset..." << std::endl;
		dataloader.load_train(Datatransformer_t::normalize(dataloader.train_data));
		dataloader.load_test(Datatransformer_t::normalize(dataloader.test_data));
	}
	std::cerr << "===================================================================" << std::endl;
	
    KNN_t<data_t, label_t> KNN;
    std::cerr << "Set knn search algorithm: " << argv[10] << std::endl;
	if (argv[10] == "brute")
		KNN.set_knn_method(std::make_shared<brute_force<data_t, label_t>>());
	else if (argv[10] == "annoy")
	{
		std::size_t maxpoint = (std::size_t)std::atoi(argv[14]);
	    std::cerr << "ANNOY: Max point count in the leaf of search tree = " << maxpoint << std::endl;
		auto annoy_ = std::make_shared<annoy<data_t, label_t> >(maxpoint);
		annoy_->bfs_threhold = std::atoi(argv[18]);
		annoy_->search_method = argv[14];
	    KNN.set_knn_method(annoy_);
	}
	std::size_t repeat = (std::size_t)std::atoi(argv[2]);
	double macc = 0.0;
	double stand = 0.0;
	double sum = 0.0, sum2 = 0.0;
	for (std::size_t t = 0; t < repeat; ++t)
	{
		std::cerr << "Train the KNN..." << t << std::endl;
		KNN.train(dataloader.train_data);
		std::cerr << "Predict the test data..." << std::endl;
		point_t<label_t> result = KNN.predict(dataloader.test_data, k);

		[[maybe_unused]]auto correct = [](label_t out, label_t y) { return (double)(out == y); };

		auto correct_n = (int)score<label_t>(result, dataloader.test_data.label, correct);
		double acc = (double)correct_n/result.size();
		macc += acc;
		sum += acc;
		sum2 += acc*acc;
	}
	stand = sqrt(sum2/repeat - pow(sum/repeat, 2)) * 100;
	macc /= repeat * 100;
	std::cout << macc << " " << stand << std::endl;
	std::cerr << macc << " " << stand << std::endl;

    return 0;
}
