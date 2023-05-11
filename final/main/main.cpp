#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include <unordered_map>
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
using label_t = long long;

using ccfn = point_t<label_t>(*)(std::unordered_map<std::string, std::string>&, const Dataloader_t<data_t, label_t>&, std::size_t);

point_t<label_t> KNN_predict(auto& args, const auto& dataloader, std::size_t KNOWN_CNT);
point_t<label_t> SVMs_predict(auto& args, const auto& dataloader, std::size_t KNOWN_CNT);
point_t<label_t> DBSCAN_fit(auto& args, const auto& dataloader, std::size_t UNKNOWN_CNT);
point_t<label_t> kmeans_fit(auto& args, const auto& dataloader, std::size_t k);

std::unordered_map<std::string, ccfn> Fn;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
    Fn["KNN"] = KNN_predict;
    Fn["SVM"] = SVMs_predict;
    Fn["DBSCAN"] = DBSCAN_fit;
    Fn["kmeans"] = kmeans_fit;

	argparser Argparser;

	// experiment
	Argparser.add("-repeats");
    Argparser.add("-classifying");
    Argparser.add("-clustering");

	// data
	Argparser.add("-train_data_path");
	Argparser.add("-train_label_path");
	Argparser.add("-test_data_path");
	Argparser.add("-test_label_path");
	Argparser.add("-normalize");
    Argparser.add("-KNOWN_CNT");
    Argparser.add("-UNKNOWN_CNT");

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

	std::size_t repeats = std::stoi(args["-repeats"]);
    std::size_t KNOWN_CNT = std::stoi(args["-KNOWN_CNT"]);
    std::size_t UNKNOWN_CNT = std::stoi(args["-UNKNOWN_CNT"]);
	
    std::string_view train_data_path = args["-train_data_path"];
    std::string_view test_data_path  = args["-test_data_path"];
    std::string_view train_label_path = args["-train_label_path"];
    std::string_view test_label_path  = args["-test_label_path"];
    std::cerr << "Train data path is " << train_data_path << std::endl;
    std::cerr << "Train label path is " << train_label_path << std::endl;
    std::cerr << "Test data path is " << test_data_path << std::endl;
    std::cerr << "Test label path is " << test_label_path << std::endl;

    // data is double, label is int
    Dataloader_t<data_t, label_t> dataloader;
    
    //std::cerr << "Load the train data..." << std::endl;
    dataloader.load_train(train_data_path);
    dataloader.load_train_label(train_label_path);

    //std::cerr << "Load the test data..." << std::endl;
    dataloader.load_test(test_data_path);
    dataloader.load_test_label(test_label_path);
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
        auto classifying_result = Fn[args["-classifying"]](args, dataloader, KNOWN_CNT);
        auto clustering_result = Fn[args["-clustering"]](args, dataloader, KNOWN_CNT+UNKNOWN_CNT);
	}
	std::chrono::steady_clock::time_point ed = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count() / 1000000.0 / repeats;
	std::cout << duration << std::endl;

    return 0;
}

point_t<label_t> KNN_predict(auto& args, const auto& dataloader, [[maybe_unused]]std::size_t KNOWN_CNT)
{
    std::size_t k = (std::size_t)std::stoi(args["-KNN_k"]);
	double maxdis = std::stod(args["-KNN_maxdis"]);
    double problim = std::stod(args["-KNN_problim"]);

	KNN_t<data_t, label_t> KNN;
	if (args["KNN_method"] == "brute")
		KNN.set_knn_method(std::make_shared<brute_force<data_t, label_t>>());
	else if (args["KNN_method"] == "annoy")
	{
        std::size_t ANNOY_maxpts = (std::size_t)std::stoi(args["-KNN_ANNOY_maxpts"]);
		double ANNOY_bfs_threhold = std::stod(args["-KNN_ANNOY_bfs_threhold"]);
		auto annoy_ = std::make_shared<annoy<data_t, label_t> >(ANNOY_maxpts);
		annoy_->search_method = "bfs";
		annoy_->bfs_threhold = ANNOY_bfs_threhold;
		KNN.set_knn_method(annoy_);
	}
	else
	{
		std::cerr << "no such search algorithm: " << args["KNN_method"] << std::endl;
		exit(1);
	}

	KNN.train(dataloader.train_data);
	return KNN.predict_ex_maxdis_prob(dataloader.test_data, k, maxdis, problim);
}


point_t<label_t> DBSCAN_fit(auto& args, const auto& dataloader, [[maybe_unused]]std::size_t UNKNOWN_CNT)
{
	std::size_t minPts = std::stoi(args["DBSCAN_minPts"]);
	double eps = std::stod(args["DBSCAN_eps"]);

    DBSCAN_t<data_t, label_t> DBSCAN{minPts, eps};
	return DBSCAN.fit(dataloader.test_data);
}

point_t<label_t> SVMs_predict(auto& args, const auto& dataloader, std::size_t KNOWN_CNT)
{
	double converge_lim = std::stod(args["SVM_converge_lim"]);
	double punishment = std::stod(args["SVM_punishment"]);
    
    point_t<label_t> result;
    for (std::size_t i = 1; i <= KNOWN_CNT; ++i)
    {
        dataset_t<data_t, label_t> dataset_{dataloader.train_data};
        for (auto& x : dataset_.label) x = (x == (label_t)i ? 1LL : -1LL);

        SVM_t<data_t, label_t> SVM{punishment, converge_lim};
    	SVM.fit(dataloader.train_data);
    	point_t<label_t> result_ =  SVM.predict(dataloader.test_data);
        for (std::size_t j = 0; j < result_.size(); ++j)
            result[j] = (result_[j] == 1LL ? (label_t)i : 0LL);
    }
    return result;
}

point_t<label_t> kmeans_fit(auto& args, const auto& dataloader, std::size_t k)
{
	double converge_lim = std::stod(args["kmeans_converge_lim"]);

    kmeans_t<data_t, label_t> kmeans{k, converge_lim};
	return kmeans.fit(dataloader.test_data);
}
