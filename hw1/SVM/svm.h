#ifndef __SVM_H__
#define __SVM_H__

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "../include/Data.h"
#include "../include/Dataloader.h"
#include "../include/Datatransformer.h"

template<typename T>
struct hyperplane_data_t
{
    double correct_rate;
    hyperplane_t<T> hyperplane;
};

template<typename T, typename U>
class svm_t
{
    private:
    int level;
    double cut_rate;
    double mutation_rate;
    double elite_save_percent;
    int variation;
    int populations;
    std::vector< hyperplane_t<double> > hyperplanes;
    void _init_gen();

    public:
    dataset_t<T, U> dataset_train;
    dataset_t<T, U> dataset_test;
    svm_t();
    svm_t(dataset_t<T, U>& _dataset_train, dataset_t<T, U>& _dataset_test);
    void train_sa(int level, double cut_rate, double mutation_rate, double elite_save_percent, int variation, int populations);
};

template<typename T, typename U>
svm_t<T,  U> :: svm_t()
{
}

template<typename T, typename U>
svm_t<T,  U> :: svm_t(dataset_t<T, U>& _dataset_train, dataset_t<T, U>& _dataset_test)
{
    for (std::size_t i = 0; i < _dataset_train.size(); ++i)
    {
        double _kernel_added = 1;
        int _dim = _dataset_train[i].size();
        for(std::size_t j=0; j < _dim ; ++j)
        {
            _kernel_added *=(_dataset_train.data[i][j] ? pow(_dataset_train.data[i][j], 2.0/_dim) : 1);
            _dataset_train.data[i][j] *= _dataset_train.data[i][j];
        }
        _kernel_added *= 1.414;
        _dataset_train[i].emplace_back(_kernel_added);
    }

    for (std::size_t i = 0; i < _dataset_test.size(); ++i)
    {
        double _kernel_added = 1;
        int _dim = _dataset_test[i].size();
        for(std::size_t j=0; j < _dim ; ++j)
        {
            _kernel_added *=(_dataset_test.data[i][j] ? pow(_dataset_test.data[i][j], 2.0/_dim) : 1);
            _dataset_test.data[i][j] *= _dataset_test.data[i][j];
        }
        _kernel_added *= 1.414;
        _dataset_test[i].emplace_back(_kernel_added);
    }
    this->dataset_train = _dataset_train;
    this->dataset_test = _dataset_test;
}

template<typename T, typename U>
void svm_t<T, U> :: _init_gen()
{
    std::srand(std::time(NULL));
    int dim = this->dataset_train[i].size();
    for(int i=0; i<this->level; ++i)
    {
        std::vector<double> temp;
        for(int j=0; j<dim; j++)
        {
            temp.push_back((double)rand()/(RAND_MAX+1.0));
        }
        hyperplane_t<double> hyper_temp(temp, (double)rand()/(RAND_MAX+1.0));
        hyperplanes.push_back(hyper_temp);
    }
}

template<typename T, typename U>
void svm_t<T, U> :: train_sa(int level, double cut_rate, double mutation_rate, double elite_save_percent, int variation, int populations)
{

}

#endif