#ifndef __NNChain_H__
#define __NNChain_H__
#include <algorithm>
#include <vector>
#include <limits>
#include <cstdlib>
#include <iostream>
#include "Data.h"
#include "utility.h"

template<typename T,typename U>
class NNChain_t{
public:
    std::size_t cluster_num;
    NNChain_t() = default;
    NNChain_t(std::size_t cluster_num_): cluster_num{cluster_num_} {};

    point_t<U> fit(const std::vector<point_t<T>>& X);
    point_t<U> fit(const dataset_t<T,U>& dataset);
};

template<typename T, typename U>
point_t<U> NNChain_t<T,U>::fit(const std::vector<point_t<T>>& X){
    point_t<U> labels;
    auto XX(X);
    labels.resize(X.size());
    std::size_t now_cluster_num = X.size();
    std::vector<std::size_t> chain;
    std::vector<U> set_num(X.size(),1);
    auto merge = [&set_num,&XX](U x,U y){
        auto sum1 = XX[x]*(T)set_num[x];
        auto sum2 = XX[y]*(T)set_num[y];
        XX[x] = (sum1+sum2) / (T)(set_num[x]+set_num[y]);
        set_num[x]+=set_num[y];
        set_num[y]=0;
        // XX[x]+=XX[y];
        // XX[x]/=2;
    };
    std::function<std::size_t(std::size_t)> findu = [&labels,&findu](U u){
        if(labels[u]==u) return u;
        else return labels[u] = findu(labels[u]);
    };
    //Everyone is in cluster with one ponit.
    for(std::size_t i=0;i<X.size();++i){
        labels[i] = i;
    }
    //Start Chaining
    while(now_cluster_num > this->cluster_num){
        
        std::size_t bk_pt,bk_pt_2;
        double dis,mndis;
        bool onlyone;
        while(1){
            if(chain.empty()){
                bk_pt=0;
                bk_pt_2=-1;
                chain.emplace_back(labels[0]);
                dis = std::numeric_limits<double>::infinity();
                mndis=std::numeric_limits<double>::infinity();
            }
            else if(chain.size()==1){
                bk_pt=chain[chain.size()-1];
                bk_pt_2=-1;
                dis = std::numeric_limits<double>::infinity();
                mndis=std::numeric_limits<double>::infinity();
            }
            else{

                bk_pt = chain[chain.size()-1];
                bk_pt_2=chain[chain.size()-2];
                dis = euclidean_dist(XX[bk_pt],XX[bk_pt_2]);
                mndis=std::numeric_limits<double>::infinity();
            }
            std::size_t mnidx=0;
            for(std::size_t i=0;i<X.size();++i){
                if(i != labels[i] || i==bk_pt) continue;
                double now_dis = euclidean_dist(XX[bk_pt],XX[i]);
                if(now_dis < mndis){
                    mndis = now_dis;
                    mnidx=i;
                }
            }
            
            if(mnidx == bk_pt_2){
                break;
            }
            else{
                chain.emplace_back(mnidx);
            }
        }
        if(set_num[bk_pt_2]>set_num[bk_pt]){
            std::swap(bk_pt_2,bk_pt);
        }
        labels[bk_pt_2] = bk_pt;
        merge(bk_pt,bk_pt_2);
        chain.pop_back();
        chain.pop_back();
        --now_cluster_num;
    }
    for(int i=0;i<labels.size();++i){
        findu(i);
    }
    return labels;
}

template<typename T,typename U>
point_t<U> NNChain_t<T,U>::fit(const dataset_t<T,U>& dataset){
    return this->fit(dataset.data);
}

#endif