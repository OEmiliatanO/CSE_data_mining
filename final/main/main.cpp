#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include <unordered_map>
#include <fstream>
#include "KNN.h"
#include "Brute.h"
#include "Annoy.h"
#include "SVM.h"
#include "svm_kernel.h"
#include "kmeans.h"
#include "DBSCAN.h"
#include "Dataloader.h"
#include "Datatransformer.h"
#include "argparser.h"
#include "utility.h"

using data_t = double;
using label_t = long long;

using ccfn = point_t<label_t>(*)(std::unordered_map<std::string, std::string>&, const Dataloader_t<data_t, label_t>&, std::size_t);

point_t<label_t> KNN_predict(auto& args, const auto& dataloader, std::size_t KNOWN_CNT);
point_t<label_t> SVMs_predict(auto& args, const auto& dataloader, std::size_t KNOWN_CNT);
point_t<label_t> SVDD_wt_NN_predict(auto& args, const auto& dataloader, std::size_t n);
point_t<label_t> DBSCAN_fit(auto& args, const auto& dataloader, std::size_t UNKNOWN_CNT);
point_t<label_t> kmeans_fit(auto& args, const auto& dataloader, std::size_t k);

std::unordered_map<std::string, ccfn> Fn;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
    Fn["KNN"] = KNN_predict;
    Fn["SVM"] = SVMs_predict;
    Fn["SVDD-wt-NN"] = SVDD_wt_NN_predict;
    Fn["DBSCAN"] = DBSCAN_fit;
    Fn["kmeans"] = kmeans_fit;

	argparser Argparser;

	// experiment
	Argparser.add("-repeats");
    Argparser.add("-classifying");
    Argparser.add("-clustering");
    Argparser.add("-verbose");

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
	Argparser.add("-KNN_problim");
	Argparser.add("-KNN_method");
	Argparser.add("-KNN_ANNOY_maxpts");
	Argparser.add("-KNN_ANNOY_bfs_threhold");

	// SVM
	Argparser.add("-SVM_converge_lim");
	Argparser.add("-SVM_punishment");
    Argparser.add("-SVM_kernel");
    Argparser.add("-SVM_kernel_gamma");
    Argparser.add("-SVM_kernel_degree");
    Argparser.add("-SVM_kernel_r");

    // SVDD w.t. NN
    Argparser.add("-SVDD-wt-NN_result_path");

	// DBSCAN
	Argparser.add("-DBSCAN_minPts");
	Argparser.add("-DBSCAN_eps");

	// kmeans
	Argparser.add("-kmeans_converge_lim");

    Argparser.parse(argc, argv);
	auto& args = Argparser.args;

	std::size_t repeats = std::stoi(args["-repeats"]);
    std::size_t KNOWN_CNT = std::stoi(args["-KNOWN_CNT"]);
    std::size_t UNKNOWN_CNT = std::stoi(args["-UNKNOWN_CNT"]);
	
    std::string_view train_data_path = args["-train_data_path"];
    std::string_view test_data_path  = args["-test_data_path"];
    std::string_view train_label_path = args["-train_label_path"];
    std::string_view test_label_path  = args["-test_label_path"];
    if (args["-verbose"] == "true")
    {
        std::cout << "===================================================" << std::endl;
        std::cout << "Train data: " << train_data_path << std::endl;
        std::cout << "Train label: " << train_label_path << std::endl;
        std::cout << "Test data: " << test_data_path << std::endl;
        std::cout << "Test label: " << test_label_path << std::endl << std::endl;
    }

    // data is double, label is int
    Dataloader_t<data_t, label_t> dataloader;
    
    if (args["-verbose"] == "true")
        std::cout << "Load the train data..." << std::endl;
    dataloader.load_train(train_data_path, false);
    dataloader.load_train_label(train_label_path);

    if (args["-verbose"] == "true")
        std::cout << "Load the test data..." << std::endl;

    dataloader.load_test(test_data_path, false);
    dataloader.load_test_label(test_label_path);
    
    if (args["-verbose"] == "true") std::cerr << "Complete loading" << std::endl << std::endl;

	if (args["-normalize"] == "true" or args["-normalize"] == "1")
	{
        if (args["-verbose"] == "true")
            std::cout << "Normalize the dataset..." << std::endl;
		dataloader.load_train(Datatransformer_t<data_t, label_t>::normalize(dataloader.train_data));
		dataloader.load_test(Datatransformer_t<data_t, label_t>::normalize(dataloader.test_data));
	}
	
	double macc_ = 0, sum_ = 0, sum2_ = 0;
	std::chrono::steady_clock::time_point st = std::chrono::steady_clock::now();
    if (args["-verbose"] == "true")
    {
        std::cout << "classifying algorithm: " << args["-classifying"] << std::endl;
    	std::cout << "clustering algorithm: " << args["-clustering"] << std::endl << std::endl;
    }
    
	for (std::size_t _ = 0; _ < repeats; ++_)
	{
		//std::cout << _ << "-th fitting..." << std::endl;
        std::vector<point_t<data_t>> centers;
        std::vector<std::size_t> kindscnt;
        kindscnt.resize(KNOWN_CNT + 1);
        centers.resize(UNKNOWN_CNT + KNOWN_CNT + 1);
        for (auto& x : centers) x.resize(dataloader.test_data.data_dimension());

        //std::cerr << "classifying..." << std::endl;
        auto classifying_result = Fn[args["-classifying"]](args, dataloader, KNOWN_CNT);
		
		dataset_t<data_t, label_t> unknown_data;
		auto unknowncnt = 0, classify_correct = 0;
		for (std::size_t i = 0; i < dataloader.test_data.size(); ++i)
        {
            if (classifying_result[i] == 0)
				unknown_data.emplace_back(dataloader.test_data.data[i], dataloader.test_data.label[i]);
            
            if (dataloader.test_data.label[i] > (label_t)KNOWN_CNT)
                ++unknowncnt;

            if (classifying_result[i] == dataloader.test_data.label[i])
                ++classify_correct;

            centers[classifying_result[i]] += dataloader.test_data[i];
            ++kindscnt[classifying_result[i]];
        }

        for (std::size_t i = 1; i <= KNOWN_CNT; ++i)
            centers[i] /= kindscnt[i];

        if (args["-verbose"] == "true")
        {
            std::cerr << classifying_result << std::endl;
            std::cerr << "classify unknown cnt = " << kindscnt[0] << std::endl;
            std::cerr << "truely unknown cnt = " << unknowncnt << std::endl;
            std::cerr << "classify acc = " << (double)classify_correct / (dataloader.test_data.size() - unknowncnt) << std::endl;
        }

		Dataloader_t<data_t, label_t> unknown_dataloader;
		unknown_dataloader.load_test(unknown_data);
        
		//std::cerr << "clustering..." << std::endl;
        auto clustering_result = Fn[args["-clustering"]](args, unknown_dataloader, UNKNOWN_CNT);
        if (args["-verbose"] == "true")
            std::cerr << clustering_result << std::endl;
		
        for (std::size_t i = 0; i < unknown_dataloader.test_data.size(); ++i)
        {
            if (clustering_result[i] == 0)
                clustering_result[i] = (label_t)assign(unknown_dataloader.test_data[i], centers);
        }

		for (std::size_t i = 0, j = 0; i < dataloader.test_data.size(); ++i)
			if (classifying_result[i] == 0)
				classifying_result[i] = KNOWN_CNT + clustering_result[j++];

		std::vector<label_t> mapping;
		for (label_t i = KNOWN_CNT + 1; i <= (label_t)KNOWN_CNT + (label_t)UNKNOWN_CNT; ++i)
			mapping.emplace_back(i);
		
		double final_acc = 0;
		do
		{
			long long sum = 0;
			for (std::size_t i = 0; i < dataloader.test_data.size(); ++i)
				sum += (classifying_result[i] > (label_t)KNOWN_CNT && dataloader.test_data.label[i] == mapping[classifying_result[i] - (label_t)KNOWN_CNT - 1]) | \
					   (dataloader.test_data.label[i] == classifying_result[i]);
			double acc = (double)sum/dataloader.test_data.size()*100;
			final_acc = std::max(final_acc, acc);
		} while (next_permutation(mapping.begin(), mapping.end()));
        
        //std::cout << "acc: " << final_acc << "%" << std::endl << std::endl;
		macc_ += final_acc;
		sum_ += final_acc;
		sum2_ += final_acc*final_acc;
	}
	
	double stand_ = sqrt(abs(sum2_*repeats - sum_*sum_))/repeats;
	macc_ /= repeats;

	std::chrono::steady_clock::time_point ed = std::chrono::steady_clock::now();
	std::cout << "" << macc_ << "%(" << stand_ << ")" << std::endl;
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count() / 1000000.0 / repeats;
	std::cout << "time: " << duration << std::endl << std::endl;

    return 0;
}

point_t<label_t> KNN_predict(auto& args, const auto& dataloader, [[maybe_unused]]std::size_t KNOWN_CNT)
{
    std::size_t k = (std::size_t)std::stoi(args["-KNN_k"]);
	double maxdis = std::stod(args["-KNN_maxdis"]);
    double problim = std::stod(args["-KNN_problim"]);

	KNN_t<data_t, label_t> KNN;
	if (args["-KNN_method"] == "brute")
		KNN.set_knn_method(std::make_shared<brute_force<data_t, label_t>>());
	else if (args["-KNN_method"] == "annoy")
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
		std::cerr << "no such search algorithm: " << args["-KNN_method"] << std::endl;
		exit(1);
	}

	KNN.train(dataloader.train_data);
	return KNN.predict_ex_maxdis_prob(dataloader.test_data, k, maxdis, problim);
}


point_t<label_t> DBSCAN_fit(auto& args, const auto& dataloader, [[maybe_unused]]std::size_t UNKNOWN_CNT)
{
	std::size_t minPts = std::stoi(args["-DBSCAN_minPts"]);
	double eps = std::stod(args["-DBSCAN_eps"]);

    DBSCAN_t<data_t, label_t> DBSCAN{minPts, eps};
	return DBSCAN.fit(dataloader.test_data);
}

point_t<label_t> SVMs_predict(auto& args, const auto& dataloader, std::size_t KNOWN_CNT)
{
	double converge_lim = std::stod(args["-SVM_converge_lim"]);
	double punishment = std::stod(args["-SVM_punishment"]);
    
    point_t<label_t> result;
	result.resize(dataloader.test_data.size());
    for (std::size_t i = 1; i <= KNOWN_CNT; ++i)
    {
        dataset_t<data_t, label_t> dataset_{dataloader.train_data};
        for (auto& x : dataset_.label) x = (x == (label_t)i ? 1LL : -1LL);
		
        SVM_t<data_t, label_t> SVM{punishment, converge_lim};

        if (args["-SVM_kernel"] == "linear")
            SVM.kernel = std::make_shared<linear_kernel<data_t>>();
        else if (args["-SVM_kernel"] == "poly")
        {
            double g = std::stod(args["-SVM_kernel_gamma"]);
            double d = std::stod(args["-SVM_kernel_degree"]);
            double r = std::stod(args["-SVM_kernel_r"]);
            SVM.kernel = std::make_shared<poly_kernel<data_t>>(g, d, r);
        }
        else if (args["-SVM_kernel"] == "rbf")
        {
            double g = std::stod(args["-SVM_kernel_gamma"]);
            SVM.kernel = std::make_shared<rbf_kernel<data_t>>(g);
        }
        else if (args["-SVM_kernel"] == "sigmoid")
        {
            double g = std::stod(args["-SVM_kernel_gamma"]);
            double r = std::stod(args["-SVM_kernel_r"]);
            SVM.kernel = std::make_shared<sigmoid_kernel<data_t>>(g, r);
        }
        else
        {
            std::cerr << "doesn't support such kernel: " << args["-SVM_kernel"] << std::endl;
            exit(1);
        }

    	SVM.fit(dataloader.train_data);
    	point_t<label_t> result_ =  SVM.predict(dataloader.test_data);
        for (std::size_t j = 0; j < result_.size(); ++j)
            result[j] = (result_[j] == 1LL ? (label_t)i : 0LL);
    }
    return result;
}

point_t<label_t> SVDD_wt_NN_predict(auto& args, [[maybe_unused]] const auto& dataloader, [[maybe_unused]] std::size_t n)
{
    std::fstream fs;
    fs.open(args["-SVDD-wt-NN_result_path"], std::ios::in);
    if (!fs.is_open()) { std::cerr << "Cannot open " << args["-SVDD-wt-NN_result_path"] << std::endl; exit(1); }
    label_t x;
    point_t<label_t> result;
    while (fs >> x) result.emplace_back(x);
    fs.close();
    return result;
}

point_t<label_t> kmeans_fit(auto& args, const auto& dataloader, std::size_t k)
{
	double converge_lim = std::stod(args["-kmeans_converge_lim"]);

    kmeans_t<data_t, label_t> kmeans{k, converge_lim};
	return kmeans.fit(dataloader.test_data);
}
