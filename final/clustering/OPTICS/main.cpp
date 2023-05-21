#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include <cstring>
#include "OPTICS.h"
#include "Dataloader.h"
#include "Datatransformer.h"

using data_t = double;
using label_t = std::size_t;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
    std::string_view train_path = argv[3];
    //std::string_view test_path  = argv[2];
    //std::cerr << "Train data path is " << train_path << std::endl;
    //std::cerr << "Test data path is " << test_path << std::endl;

    // data is double, label is int
    Dataloader_t<data_t, label_t> dataloader;
    
    //std::cerr << "Load the train data..." << std::endl;
    dataloader.load_train(train_path, false);
    //dataloader.load_train(Datatransformer_t<data_type, label_type>::drop_attrs_are_xs(dataloader.train_data, std::vector<std::size_t>{2,3,4}, std::vector<data_type>{0,0,0}));

    //std::cerr << "Load the test data..." << std::endl;
	//dataloader.load_test(test_path, false);
    //std::cerr << "Complete loading" << std::endl << std::endl;
	if (strcmp(argv[4], "true") == 0)
	{
		//std::cerr << "Normalize the dataset..." << std::endl;
		dataloader.load_train(Datatransformer_t<data_t, label_t>::normalize(dataloader.train_data));
		dataloader.load_test(Datatransformer_t<data_t, label_t>::normalize(dataloader.test_data));
	}
	//std::cerr << "===================================================================" << std::endl;
	
	std::size_t minPts = (std::size_t)std::atoi(argv[1]);
    double epsilon = (double)std::stod(argv[2]);
    std::cerr << "Parameter:\nminPts = " << minPts << "\neps = " << epsilon << std::endl;
    DBSCAN_t<data_t, label_t> OPTICS{minPts, epsilon};
	point_t<label_t> labels = OPTICS.fit(dataloader.train_data);

    std::cout << dataloader.train_data.size() << std::endl;
	for (std::size_t i = 0; i < dataloader.train_data.size(); ++i)
	{
		std::cout << dataloader.train_data.data[i] << labels[i] << std::endl;
	}

    return 0;
}
