#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include "KNN.h"
#include "Brute.h"
#include "Annoy.h"
#include "SVM.h"
#include "kmeans.h"
#include "DBSCAN.h"
#include "Dataloader.h"
#include "Datatransformer.h"
#include "argparser.h"

using data_t = double;
using label_t = std::size_t;

point_t<label_t> KNN_predict(const auto& args, const auto& dataloader);
point_t<label_t> DBSCAN_fit(const auto& args, const auto& dataloader);

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
	argparser Argparser;

	// experiment
	Argparser.add("-repeats");

	// data
	Argparser.add("-train_path");
	Argparser.add("-test_path");
	Argparser.add("-normalize");

	// KNN
	Argparser.add("-KNN_k");
	Argparser.add("-KNN_maxdis");
	Argparser.add("-KNN_method");
	Argparser.add("-KNN_ANNOY_maxpts");
	Argparser.add("-KNN_ANNOY_bfs_threhold");

	// SVM
	Argparser.add("-SVM_converge_lim");
	Argparser.add("-SVM_punishment");

	// DBSCAN
	Argparser.add("-DBSCAN_minPts");
	Argparser.add("-DBSCAN_eps");

	// kmeans
	Argparser.add("-kmeans_k");
	Argparser.add("-kmeans_converge_lim");

	auto& args = Argparser.args;

	std::size_t repeats = std::stoi(args["repeats"]);
	
    std::string_view train_path = args["-train_path"];
    std::string_view test_path  = args["-test_path"];
    std::cerr << "Train data path is " << train_path << std::endl;
    std::cerr << "Test data path is " << test_path << std::endl;

    // data is double, label is int
    Dataloader_t<data_t, label_t> dataloader;
    
    //std::cerr << "Load the train data..." << std::endl;
    dataloader.load_train(train_path);

    //std::cerr << "Load the test data..." << std::endl;
    dataloader.load_test(test_path);
    //std::cerr << "Complete loading" << std::endl << std::endl;
	if (args["normalize"] == "true" or args["normalize"] == "1")
	{
		//std::cerr << "Normalize the dataset..." << std::endl;
		dataloader.load_train(Datatransformer_t<data_t, label_t>::normalize(dataloader.train_data));
		dataloader.load_test(Datatransformer_t<data_t, label_t>::normalize(dataloader.test_data));
	}
	//std::cerr << "===================================================================" << std::endl;
	
	std::chrono::steady_clock::time_point st = std::chrono::steady_clock::now();
	for (std::size_t _ = 0; _ < repeats; ++_)
	{
		// "<classifying>-<clustering>, e.g. KNN-DBSCAN"
		auto classifying_result = KNN_predict(args, dataloader);
		auto clustering_result = DBSCAN_fit(args, dataloader);
	}
	std::chrono::steady_clock::time_point ed = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count() / 1000000.0 / repeats;
	std::cout << duration << std::endl;

    return 0;
}

point_t<label_t> KNN_predict(const auto& args, const auto& dataloader)
{
    std::size_t KNN_k = (std::size_t)std::atoi(args["-KNN_k"]);
	double KNN_maxdis = std::stod(args["-KNN_maxdis"]);
	std::size_t KNN_ANNOY_maxpts = (std::size_t)std::stoi(args["-KNN_ANNOY_maxpts"]);

	KNN_t<data_t, label_t> KNN;
	if (args["KNN_method"] == "brute")
		KNN.set_knn_method(std::make_shared<brute_force<data_t, label_t>>());
	else if (args["KNN_method"] == "annoy")
	{
		double KNN_ANNOY_bfs_threhold = std::stod(args["-KNN_ANNOY_bfs_threhold"]);
		auto annoy_ = std::make_shared<annoy<data_t, label_t> >(KNN_ANNOY_maxpts);
		annoy_->search_method = "bfs";
		annoy_->bfs_threhold = KNN_ANNOY_bfs_threhold;
		KNN.set_knn_method(annoy_);
	}
	else
	{
		std::cerr << "no such search algorithm: " << args["KNN_method"] << std::endl;
		exit(1);
	}

	KNN.train(dataloader.train_data);
	return KNN.predict(dataloader.test_data, KNN_k);
}


point_t<label_t> DBSCAN_fit(const auto& args, const auto& dataloader)
{
	std::size_t minPts = std::stoi(args["DBSCAN_minPts"]);
	double eps = std::stod(args["DBSCAN_eps"]);

    DBSCAN_t<data_t, label_t> DBSCAN{minPts, eps};
	return DBSCAN.fit(dataloader.test_data);
}

point_t<label_t> SVM_predict(const auto& args, const auto& dataloader)
{
	double SVM_converge_lim = std::stod(args["SVM_converge_lim"]);
	double SVM_punishment = std::stod(args["SVM_punishment"]);

    SVM_t<data_t, label_t> SVM{SVM_punishment, SVM_converge_lim};
	SVM.fit(dataloader.train_data);
	return SVM.predict(dataloader.test_data);
}

point_t<label_t> kmeans_fit(const auto& args, const auto& dataloader)
{
	std::size_t kmeans_k = std::stoi(args["kmeans_k"]);
	double kmeans_converge_lim = std::stod(args["kmeans_converge_lim"]);

    kmeans_t<data_t, label_t> kmeans{kmeans_k, kmeans_converge_lim};
	return kmeans.fit(dataloader.test_data);
}
