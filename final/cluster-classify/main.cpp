#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>
#include <unordered_map>
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

// this is clustering first, then classifying

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
	std::cout << "===================================================" << std::endl;
    std::cout << "Train data: " << train_data_path << std::endl;
    std::cout << "Train label: " << train_label_path << std::endl;
    std::cout << "Test data: " << test_data_path << std::endl;
    std::cout << "Test label: " << test_label_path << std::endl << std::endl;

    // data is double, label is int
    Dataloader_t<data_t, label_t> dataloader;
    
    std::cout << "Load the train data..." << std::endl;
    dataloader.load_train(train_data_path, false);
    dataloader.load_train_label(train_label_path);

    std::cout << "Load the test data..." << std::endl;
    dataloader.load_test(test_data_path, false);
    dataloader.load_test_label(test_label_path);
    std::cerr << "Complete loading" << std::endl << std::endl;
	if (args["normalize"] == "true" or args["normalize"] == "1")
	{
		std::cout << "Normalize the dataset..." << std::endl;
		dataloader.load_train(Datatransformer_t<data_t, label_t>::normalize(dataloader.train_data));
		dataloader.load_test(Datatransformer_t<data_t, label_t>::normalize(dataloader.test_data));
	}
	std::cout << "===================================================================" << std::endl;
	
	double macc_ = 0, sum_ = 0, sum2_ = 0;
	std::chrono::steady_clock::time_point st = std::chrono::steady_clock::now();
	std::cout << "classifying algorithm: " << args["-classifying"] << std::endl;
	std::cout << "clustering algorithm: " << args["-clustering"] << std::endl << std::endl;
    
	for (std::size_t _ = 0; _ < repeats; ++_)
	{
		std::cout << _ << "-th fitting..." << std::endl;
        
        std::vector<point_t<data_t>> centers;
        std::vector<std::size_t> kindscnt;
        kindscnt.resize(UNKNOWN_CNT + KNOWN_CNT + 1);
        centers.resize(UNKNOWN_CNT + KNOWN_CNT + 1);
        for (auto& x : centers) x.resize(dataloader.test_data.data_dimension());

		dataset_t<data_t, label_t> center_data;

		std::cerr << "clustering..." << std::endl;
        auto clustering_result = Fn[args["-clustering"]](args, dataloader, KNOWN_CNT + UNKNOWN_CNT);
        std::cerr << "clustering result: " << clustering_result << std::endl;
        
        for (std::size_t i = 0; i < dataloader.test_data.size(); ++i)
        {
            const auto& label = clustering_result[i];
            if (label == 0) continue;
            centers[label] += dataloader.test_data.data[i];
            ++kindscnt[label];
        }
        for (std::size_t i = 0; i < centers.size(); ++i)
        {
            centers[i] /= kindscnt[i];
            center_data.emplace_back(centers[i], 0);
        }

        Dataloader_t<data_t, label_t> center_dataloader;
        center_dataloader.load_train(dataloader.train_data);
        center_dataloader.load_test(center_data);

        auto classifying_result = Fn[args["-classifying"]](args, center_dataloader, KNOWN_CNT);
        std::cerr << "classifying result: " << classifying_result << std::endl;
        auto label = clustering_result;

        kindscnt.clear();
        centers.clear();
        kindscnt.resize(UNKNOWN_CNT + KNOWN_CNT + 1);
        centers.resize(UNKNOWN_CNT + KNOWN_CNT + 1);
        for (auto& x : centers) x.resize(dataloader.test_data.data_dimension());

		std::vector<label_t> mapping;
        std::size_t unknown_cnt = 0;
        mapping.resize(KNOWN_CNT + UNKNOWN_CNT);
        for (std::size_t i = 0; i < clustering_result.size(); ++i)
        {
            if (label[i] != 0)
            {
                if (classifying_result[clustering_result[i]] != 0)
                    label[i] = classifying_result[clustering_result[i]];
                else
                {
                    if (mapping[clustering_result[i]] == 0)
                    {
                        label[i] = KNOWN_CNT + ++unknown_cnt;
                        mapping[clustering_result[i]] = KNOWN_CNT + unknown_cnt;
                    }
                    else
                        label[i] = mapping[clustering_result[i]];
                }
            }
        }

		for (std::size_t i = 0; i < dataloader.test_data.size(); ++i)
        {
            centers[label[i]] += dataloader.test_data[i];
            ++kindscnt[label[i]];
        }
        for (std::size_t i = 0; i < centers.size(); ++i)
            centers[i] /= kindscnt[i];

        for (std::size_t i = 0; i < label.size(); ++i)
        {
            if (label[i] == 0)
                label[i] = (label_t)assign(dataloader.test_data[i], centers) + 1;
        }

        std::cerr << "final label: " << label << std::endl;
        std::cerr << "true label:  " << dataloader.test_data.label << std::endl;
        
		mapping.clear();
		for (label_t i = KNOWN_CNT + 1; i <= (label_t)KNOWN_CNT + (label_t)UNKNOWN_CNT; ++i)
			mapping.emplace_back(i);
		
		double final_acc = 0;
		do
		{
			long long sum = 0;
			for (std::size_t i = 0; i < dataloader.test_data.size(); ++i)
				sum += (label[i] > (label_t)KNOWN_CNT && dataloader.test_data.label[i] == mapping[label[i] - (label_t)KNOWN_CNT - 1]) | \
					   (dataloader.test_data.label[i] == label[i]);
			double acc = (double)sum/dataloader.test_data.size()*100;
			final_acc = std::max(final_acc, acc);
		} while (next_permutation(mapping.begin(), mapping.end()));
        
        std::cout << "acc: " << final_acc << "%" << std::endl << std::endl;
		macc_ += final_acc;
		sum_ += final_acc;
		sum2_ += final_acc*final_acc;
	}
	
	double stand_ = sqrt(abs(sum2_*repeats - sum_*sum_))/repeats;
	macc_ /= repeats;

	std::chrono::steady_clock::time_point ed = std::chrono::steady_clock::now();
	std::cout << "acc = " << macc_ << "%(" << stand_ << ")" << std::endl;
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(ed - st).count() / 1000000.0 / repeats;
	std::cout << "time: " << duration << std::endl;

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

point_t<label_t> kmeans_fit(auto& args, const auto& dataloader, std::size_t k)
{
	double converge_lim = std::stod(args["-kmeans_converge_lim"]);

    kmeans_t<data_t, label_t> kmeans{k, converge_lim};
	return kmeans.fit(dataloader.test_data);
}
