#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include "src/KNN.h"
#include "src/Brute.h"
#include "src/Annoy.h"
#include "../include/Dataloader.h"
#include "../include/Datatransformer.h"

using data_t = double;
using label_t = int;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
    std::string_view train_path = argv[4];
    std::string_view test_path  = argv[6];
    //std::cerr << "Train data path is " << train_path << std::endl;
    //std::cerr << "Test data path is " << test_path << std::endl;

    
    std::size_t k = (std::size_t)std::atoi(argv[12]);

    // data is double, label is int
    Dataloader_t<data_t, label_t> dataloader;
    
    //std::cerr << "Load the train data..." << std::endl;
    dataloader.load_train(train_path);
    //dataloader.load_train(Datatransformer_t<data_type, label_type>::drop_attrs_are_xs(dataloader.train_data, std::vector<std::size_t>{2,3,4}, std::vector<data_type>{0,0,0}));

    //std::cerr << "Load the test data..." << std::endl;
    dataloader.load_test(test_path);
    //std::cerr << "Complete loading" << std::endl << std::endl;
	if (strcmp(argv[8], "true") == 0)
	{
		//std::cerr << "Normalize the dataset..." << std::endl;
		dataloader.load_train(Datatransformer_t<data_t, label_t>::normalize(dataloader.train_data));
		dataloader.load_test(Datatransformer_t<data_t, label_t>::normalize(dataloader.test_data));
	}
	//std::cerr << "===================================================================" << std::endl;
	
    KNN_t<data_t, label_t> KNN;
    //std::cerr << "Set knn search algorithm: " << argv[10] << std::endl;
	if (strcmp(argv[10], "brute") == 0)
		KNN.set_knn_method(std::make_shared<brute_force<data_t, label_t>>());
	else if (strcmp(argv[10], "annoy") == 0)
	{
		std::size_t maxpoint = (std::size_t)std::atoi(argv[16]);
	    //std::cerr << "ANNOY: Max point count in the leaf of search tree = " << maxpoint << std::endl;
		auto annoy_ = std::make_shared<annoy<data_t, label_t> >(maxpoint);
		if (strcmp(argv[14], "bfs") == 0)
			annoy_->bfs_threhold = std::atoi(argv[18]);
		annoy_->search_method = argv[14];
	    KNN.set_knn_method(annoy_);
	}
	else
	{
		std::cerr << "no such search algorithm" << std::endl;
		exit(1);
	}
	std::size_t repeat = (std::size_t)std::atoi(argv[2]);
	double macc = 0.0;
	double stand = 0.0;
	double sum = 0.0, sum2 = 0.0;
	std::chrono::steady_clock::time_point st = std::chrono::steady_clock::now();
	for (std::size_t t = 0; t < repeat; ++t)
	{
		//std::cerr << "Train the KNN..." << t << std::endl;
		KNN.train(dataloader.train_data);
		//std::cerr << "Predict the test data..." << std::endl;
		point_t<label_t> result = KNN.predict(dataloader.test_data, k);

		[[maybe_unused]]auto correct = [](label_t out, label_t y) { return (double)(out == y); };

		auto correct_n = (int)score<label_t>(result, dataloader.test_data.label, correct);
		double acc = (double)correct_n/result.size()*100;
		macc += acc;
		sum += acc;
		sum2 += acc*acc;
	}
	std::chrono::steady_clock::time_point ed = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count() / 1000000.0 / repeat;
	stand = sqrt(abs(sum2*repeat - sum*sum))/repeat;
	macc /= repeat;
	std::cout << macc << " " << stand << " " << duration << std::endl;
	std::cerr << macc << " " << stand << " " << duration << std::endl;

    return 0;
}
