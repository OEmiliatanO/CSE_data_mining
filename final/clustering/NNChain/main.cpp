#include <iostream>
#include <iomanip>
#include <memory>
#include <cmath>
#include <chrono>
#include <string>
#include <cstring>
#include <fstream>
#include <ranges>
#include <set>
#include <map>
#include <algorithm>
#include <string_view>
#include "NNChain.h"
#include "Dataloader.h"
#include "Datatransformer.h"

using data_t = double;
using label_t = std::size_t;

void read_file(std::string& data_path, std::string& label_path,dataset_t<data_t,label_t>& dataset){
    std::fstream fsd,fsl;
    fsd.open(data_path);
    fsl.open(label_path);
    if(fsd.fail()){
        std::cerr << "Reading File Error:" << data_path << std::endl;
        exit(1);
    }
    if(fsl.fail()){
        std::cerr << "Reading File Error:" << label_path << std::endl;
        exit(1);
    }
    std::string sd,sl;
    while(fsd>>sd && fsl>>sl){
        // std::cout << sl << std::endl;
        if(sl!="0") continue;
        std::string delimiter = ",";
        point_t<data_t> data;
        for(auto x:std::ranges::views::split(sd,delimiter)){
            data.emplace_back(std::stod(std::string_view(x).data()));
        }
        dataset.emplace_back(std::move(data),std::move(std::stoull(sl)));
    }
}

label_t fact(label_t i){
    if(i==1 || i==0) return 1;
    return i*fact(i-1);
}

void compare(std::string& test_label_path,std::string& predict_label_path,point_t<label_t>& labels,int cluster_number,int cluster_label_start){
    std::set<label_t> se(labels.begin(),labels.end());
    std::map<label_t,label_t> mp;
    label_t p=0;
    for(auto x:se){
        mp[x]=p++;
    }
    std::fstream fstl,fspl;
    fstl.open(test_label_path);
    fspl.open(predict_label_path);
    if(fstl.fail()){
        std::cerr << "Reading File Error:" << test_label_path << std::endl;
        exit(1);
    }
    if(fspl.fail()){
        std::cerr << "Reading File Error:" << predict_label_path << std::endl;
        exit(1);
    }
    label_t cnt=0;
    label_t pp=0;
    label_t all=0;
    label_t fa=fact(cluster_number);
    std::string s1,s2;
    std::vector<label_t> cnts(fa,0);
    std::vector<label_t> list(cluster_number,0);
    while(fstl >> s1 && fspl >> s2){
        ++all;
        if(s1==s2) ++cnt;
        else if(s2=="0"){
            for(int i=0;i<cluster_number;++i){
                list[i]=i+cluster_label_start;
            }
            
            for(int i=0;i<fa;++i){
                if(list[mp[labels[pp]]]==std::stoull(s1))++cnts[i];
                std::next_permutation(list.begin(),list.end());
            }
            ++pp;
        }
    }
    double outcome = (double)(cnt+*std::max_element(cnts.begin(),cnts.end()))/(double)all;
    std::cout << "Match:" << (cnt+*std::max_element(cnts.begin(),cnts.end())) << std::endl; 
    std::cout << "All:" << all << std::endl; 
    std::cout << "Accuracy:" << std::setprecision(4) << outcome << std::endl;
}
int main([[maybe_unused]] int argc, [[maybe_unused]]char* argv[]){
    std::vector<std::vector<data_t>> data;
    std::vector<label_t> label;
    std::string data_path = argv[2];
    std::cout << "data_path:" << argv[2] << std::endl;
    std::string label_path = argv[3];
    std::cout << "label_path:" << argv[3] << std::endl;
    std::string test_label_path = argv[4];
    std::cout << "test_label_path:" << argv[4] << std::endl;

    dataset_t<data_t,label_t> ds;
    read_file(data_path,label_path,ds);
    Dataloader_t<data_t,label_t> dataloader;
    dataloader.load_train(ds);
    std::size_t num_cluster = (std::size_t)std::atoi(argv[1]);
    std::cout << "Number of Clustering: " << num_cluster << std::endl;

    NNChain_t<data_t,label_t> NNChain{num_cluster};
    point_t<label_t> labels = NNChain.fit(dataloader.train_data);

    
    compare(test_label_path,label_path,labels,num_cluster,4);
    int cnt=0;

    return 0;
}
//./main.exe 2 ..\..\data\gene_expression_cancer_RNA-Seq_data_set\PCA_test_data_100.csv ..\..\classifying\DNN\classified-label-for-PCA100.csv ..\..\data\gene_expression_cancer_RNA-Seq_data_set\test_label.csv[]