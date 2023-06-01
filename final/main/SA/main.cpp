#include <iostream>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <cmath>
#include <chrono>
#include <unordered_map>
#include <random>
#include "argparser.h"

std::string exe_with_args(auto& args)
{
    std::string s = "../main.elf -repeats 1 -classifying " + args["-classifying"] + " -clustering " + args["-clustering"] + \
                    " -verbose false " + "-train_data_path " + args["-train_data_path"] + " -train_label_path " + args["-train_label_path"] + \
                    " -test_data_path " + args["-test_data_path"] + " -test_data_path " + args["-test_data_path"] + \
                    " -test_label_path " + args["-test_label_path"] + " -normalize " + args["-normalize"] + " -KNOWN_CNT " + args["-KNOWN_CNT"] + \
                    " -UNKNOWN_CNT " + args["-UNKNOWN_CNT"];

    if (args["-classifying"] == "KNN")
    {
        // -KNN_k
        // -KNN_maxdis
        // -KNN_problim
        s += " -KNN_method brute -KNN_k " + args["-KNN_k"] + " -KNN_maxdis " + args["-KNN_maxdis"] + " -KNN_problim " + args["-KNN_problim"];
    }
    else if (args["-classifying"] == "SVM")
    {
        // -SVM_converge_lim 1e-7
        // -SVM_punishment 1
        // -SVM_kernel 
        // -SVM_kernel_gamma
        // -SVM_kernel_degree
        // -SVM_kernel_r
        s += " -SVM_converge_lim 1e-7 -SVM_punishment 1 -SVM_kernel " + args["-SVM_kernel"] + \
             " -SVM_kernel_gamma " + args["-SVM_kernel_gamma"] + " -SVM_kernel_degree 2" + \
             " -SVM_kernel_r " + args["-SVM_kernel_r"];
    }

    if (args["-clustering"] == "kmeans")
    {
        // -kmeans_converge_lim
        s += " -kmeans_converge_lim 1e-5";
    }
    else if (args["-clustering"] == "DBSCAN")
    {
        // -DBSCAN_minPts
        // -DBSCAN_eps
        s += " -DBSCAN_minPts " + args["-DBSCAN_minPts"] + " -DBSCAN_eps " + args["-DBSCAN_eps"];
    }
    return s;
}

double E(auto& args)
{
    //std::cout << exe_with_args(args) << std::endl;
    //exit(1);
    FILE *fp = popen(exe_with_args(args).c_str(), "r");
    if (fp == NULL) { std::cerr << "cannot create pipe. exit(1)..." << std::endl; exit(1); }
    double acc = -1;
    if (fscanf(fp, "%lf", &acc) == 0) return -1;
    pclose(fp);
    //std::cout << acc << std::endl;
    return acc;
}

double best_ss_d[] = {15, 0.7, 2, 2, 1};
int best_ss_i[] = {13, 10};
double best_acc = 0;

void set_arg(auto& args, double* ss_d, int* ss_i)
{
    if (args["-classifying"] == "KNN")
    {
        args["-KNN_k"] = std::to_string(ss_i[0]);
        args["-KNN_maxdis"] = std::to_string(ss_d[0]);
        args["-KNN_problim"] = std::to_string(ss_d[1]);
    }
    else if (args["-classifying"] == "SVM")
    {
        args["-SVM_kernel_gamma"] = std::to_string(ss_d[2]);
        args["-SVM_kernel_r"] = std::to_string(ss_d[3]);
    }

    if (args["-clustering"] == "kmeans")
    {
    }
    else if (args["-clustering"] == "DBSCAN")
    {
        args["-DBSCAN_minPts"] = std::to_string(ss_i[1]);
        args["-DBSCAN_eps"] = std::to_string(ss_d[4]);
    }
}

void neighbor(auto& args, double* ss_d, int* ss_i, double* nex_ss_d, int* nex_ss_i)
{
    std::default_random_engine gen(1);
    std::uniform_real_distribution<double> unid(-5.0, 5.0);
    std::uniform_int_distribution<int> unii(-1, 1);
    
    if (args["-classifying"] == "KNN")
    {
        do
            nex_ss_i[0] = ss_i[0] + unii(gen);
        while (nex_ss_i[0] <= 0);
        do
            nex_ss_d[0] = ss_d[0] + unid(gen);
        while (nex_ss_d[0] <= 0);
        do
            nex_ss_d[1] = unid(gen) * ss_d[1] + unid(gen);
        while (nex_ss_d[1] < 0 or nex_ss_d[1] > 1);
    }
    else if (args["-classifying"] == "SVM")
    {
        do
            nex_ss_d[2] = ss_d[2] + unid(gen);
        while (nex_ss_d[2] <= 0);
        do
            nex_ss_d[3] = ss_d[3] + unid(gen);
        while (nex_ss_d[3] <= 0);
    }

    if (args["-clustering"] == "kmeans")
    {
    }
    else if (args["-clustering"] == "DBSCAN")
    {
        do
            nex_ss_i[1] = ss_i[1] + unii(gen);
        while (nex_ss_i[1] <= 0);
        do
            nex_ss_d[4] = ss_d[4] + unid(gen);
        while (nex_ss_d[4] <= 0);
    }

}

void SA(auto& args, double T, double Rt, double EndT, std::size_t n)
{
    std::default_random_engine gen(0);
    std::uniform_real_distribution<double> unid(0.0, 1.0);

    // -KNN_maxdis(0) -KNN_problim(1) -SVM_kernel_gamma(2) -SVM_kernel_r(3) -DBSCAN_eps(4)
    double now_ss_d[] = {15, 0.7, 2, 1, 10};
    now_ss_d[0] = std::stod(args["-init_KNN_maxdis"]);
    now_ss_d[1] = std::stod(args["-init_KNN_problim"]);
    now_ss_d[2] = std::stod(args["-init_SVM_kernel_gamma"]);
    now_ss_d[3] = std::stod(args["-init_SVM_kernel_r"]);
    now_ss_d[4] = std::stod(args["-init_DBSCAN_eps"]);
    // -KNN_k(0) -DBSCAN_minPts(1)
    int now_ss_i[] = {13, 10};
    now_ss_i[0] = std::stoi(args["-init_KNN_k"]);
    now_ss_i[1] = std::stoi(args["-init_DBSCAN_minPts"]);

    set_arg(args, now_ss_d, now_ss_i);
    
    double e = E(args);
    std::cerr << "init E = " << e << std::endl;
    best_acc = e;
    while (T > EndT)
    {
        T *= Rt;
        for (std::size_t _ = 0; _ < n; ++_)
        {
            double nex_ss_d[] = {15, 0.7, 2, 1, 10};
            int nex_ss_i[] = {13, 10};
            // neighbor
            neighbor(args, now_ss_d, now_ss_i, nex_ss_d, nex_ss_i);
            set_arg(args, nex_ss_d, nex_ss_i);
            double e1 = E(args);
            //std::cerr << "new e = " << e1 << std::endl;
            double dt = e1 - e;
            if (e1 > best_acc)
            {
                best_acc = e1;
                std::cerr << best_acc << std::endl;
                memcpy(best_ss_d, nex_ss_d, sizeof(nex_ss_d));
                memcpy(best_ss_i, nex_ss_i, sizeof(nex_ss_i));
            }
            if (e1 > e or unid(gen) < exp(dt/T))
            {
                memcpy(now_ss_d, nex_ss_d, sizeof(nex_ss_d));
                memcpy(now_ss_i, nex_ss_i, sizeof(nex_ss_i));
                e = e1;
            }
        }
    }
}

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[])
{
	argparser Argparser;
	// -repeats 1
    Argparser.add("-classifying");
    Argparser.add("-clustering");
    // -classifying 
    // -clustering 
    // -verbose true

	Argparser.add("-train_data_path");
	Argparser.add("-train_label_path");
	Argparser.add("-test_data_path");
	Argparser.add("-test_label_path");
	Argparser.add("-normalize");
    Argparser.add("-KNOWN_CNT");
    Argparser.add("-UNKNOWN_CNT");

	// KNN
    // -KNN_k
    Argparser.add("-init_KNN_k");
    // -KNN_maxdis
    Argparser.add("-init_KNN_maxdis");
	// -KNN_problim
    Argparser.add("-init_KNN_problim");
	// -KNN_method brute

	// -KNN_ANNOY_maxpts (unused)
	// -KNN_ANNOY_bfs_threhold (unused)

	// SVM
	// -SVM_converge_lim 1e-7
	// -SVM_punishment 1
    // -SVM_kernel 
    Argparser.add("-SVM_kernel");
    // -SVM_kernel_gamma
    Argparser.add("-init_SVM_kernel_gamma");
    // -SVM_kernel_degree 2
    // -SVM_kernel_r
    Argparser.add("-init_SVM_kernel_r");

	// DBSCAN
	// -DBSCAN_minPts
    Argparser.add("-init_DBSCAN_minPts");
	// -DBSCAN_eps
    Argparser.add("-init_DBSCAN_eps");

	// kmeans
	// -kmeans_converge_lim

    Argparser.add("-T");
    Argparser.add("-Rt");
    Argparser.add("-EndT");
    Argparser.add("-n");

    Argparser.parse(argc, argv);
	auto& args = Argparser.args;
    
    SA(args, std::stod(args["-T"]), std::stod(args["-Rt"]), std::stod(args["-EndT"]), (std::size_t)std::stoi(args["-n"]));

    std::cout << "best_acc: " << best_acc << std::endl;
    if (args["-classifying"] == "KNN")
    {
        std::cout << "KNN_k = " << best_ss_i[0] << std::endl;
        std::cout << "KNN_maxdis = " << best_ss_d[0] << std::endl;
        std::cout << "KNN_problim = " << best_ss_d[1] << std::endl;
    }
    else if (args["-classifying"] == "SVM")
    {
        std::cout << "SVM_kernel_gamma = " << best_ss_d[2] << std::endl;
        std::cout << "SVM_kernel_r = " << best_ss_d[3] << std::endl;
    }
    if (args["-clustering"] == "kmeans")
    {
    }
    else if (args["-clustering"] == "DBSCAN")
    {
        std::cout << "DBSCAN_minPts = " << best_ss_i[1] << std::endl;
        std::cout << "DBSCAN_eps = " << best_ss_d[4] << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
