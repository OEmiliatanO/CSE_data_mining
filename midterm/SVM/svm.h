#ifndef __SVM_H__
#define __SVM_H__
#include <ctime>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <unistd.h>
#include "../include/Data.h"
#include "../include/Dataloader.h"
#include "../include/Datatransformer.h"

template<typename T, typename U>
class hypvar_t;

template<typename T, typename U>
struct cmp_hyper {
    bool operator()(hypvar_t<T, U> a, hypvar_t<T, U> b) 
    {
        return a.correct_rate < b.correct_rate;
    }
};

template<typename T, typename U>
class hypvar_t
{
    public:
    hypvar_t(hyperplane_t<T> _hyperplane, dataset_t<T, U>& _dataset_train);
    double correct_rate;
    hyperplane_t<T> hyperplane;
};
template<typename T, typename U>
hypvar_t<T, U> :: hypvar_t(hyperplane_t<T> _hyperplane, dataset_t<T, U>& _dataset_train)
{
    this->hyperplane = _hyperplane;

    std::size_t data_nums = _dataset_train.size();
    int correct_nums = 0;
    for (std::size_t i = 0; i <data_nums ; ++i)
    {
        // maybe bug (data)
        correct_nums += ((hyperplane.n * _dataset_train.data[i] - hyperplane.b > 0) == _dataset_train.label[i]);
    }
    this->correct_rate = ((double)correct_nums / (double)data_nums);
}

template<typename T, typename U>
class svm_t
{
    private:
    int level;
    double mutation_rate;
    double elite_save_percent;
	std::size_t variation;
    int populations;
    std::priority_queue< hypvar_t<T, U>, std::vector< hypvar_t<T, U> >, cmp_hyper<T, U> > hyperplanes_data;
    void _init_gen();
    void _next_gen();
    hypvar_t<T, U> _crossover(hypvar_t<T, U>& a, hypvar_t<T, U>& b);

    public:
    dataset_t<T, U> dataset_train;
    dataset_t<T, U> dataset_test;
    svm_t();
    svm_t(dataset_t<T, U>& _dataset_train, dataset_t<T, U>& _dataset_test);
    void train_ga(int level, double mutation_rate, double elite_save_percent, std::size_t variation, int populations);
    double correct_rate();
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
		std::size_t _dim = _dataset_train[i].size();
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
		std::size_t _dim = _dataset_test[i].size();
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
    for(int i=0; i<this->populations; ++i)
    {
        int dim = this->dataset_train.data[i].size();
        std::vector<double> temp;
        for(int j=0; j<dim; j++)
        {
            temp.push_back((double)rand()/(RAND_MAX+1.0));
        }
        // may bug
        hyperplane_t<double> hyper_temp(temp, rand()%1000 );
        //std::cout << "Hyper n: " << hyper_temp.n << std::endl;
        hypvar_t<T, U> hypvar_temp(hyper_temp, dataset_train);
        //std::cout << "Real Hyper n: " << hypvar_temp.hyperplane.n << std::endl;
        hyperplanes_data.push(hypvar_temp);
    }
}

template<typename T, typename U>
hypvar_t<T, U> svm_t<T, U> ::_crossover(hypvar_t<T, U>& a, hypvar_t<T, U>& b)
{
    std::vector<double> tmp1;
    for(double x: a.hyperplane.n.x)
    {
        tmp1.push_back(x);
    }
    std::vector<double> tmp2 = b.hyperplane.n.x;
    for(double x: b.hyperplane.n.x)
    {
        tmp2.push_back(x);
    }
    int const_b = a.hyperplane.b;


    for(std::size_t i=0; i<this->variation; i++)
    {
        double rd_choose_val = (double)rand()/(RAND_MAX+1.0);
		std::size_t rd_index = rand() % b.hyperplane.n.size()+1;
        if(rd_choose_val < 0.5)
        {
            if(rd_index == b.hyperplane.n.size())
                const_b = (a.hyperplane.b + b.hyperplane.b)/2;
            else
                tmp1[rd_index] = (tmp1[rd_index] + tmp2[rd_index])/2;
        }
        else
        {
            if(rd_index == b.hyperplane.n.size())
                const_b = b.hyperplane.b;
            else
                tmp1[rd_index] = tmp2[rd_index];
        }
    }
    double rd_muatation = (double)rand()/(RAND_MAX+1.0);
    if(rd_muatation < this->mutation_rate)
    {
        int rd_index = rand() % b.hyperplane.n.size();
        tmp1[rd_index] = (double)rand()/(RAND_MAX+1.0);
    }

    point_t<double> point_temp(tmp1);
    hyperplane_t<double> hyperplane_temp(point_temp, const_b);
    hypvar_t<T, U> hypvar_temp(hyperplane_temp, dataset_train);
    return hypvar_temp;
}

template<typename T, typename U>
void svm_t<T, U> :: _next_gen()
{
    std::vector< hypvar_t<T, U> > elite_vector;
    for(int i=0; i<int(populations*elite_save_percent) ; i++)
    {
        elite_vector.push_back(hyperplanes_data.top());
        hyperplanes_data.pop();
    }
    while (!hyperplanes_data.empty()) hyperplanes_data.pop();
    for(int i=0; i< populations - int(populations*elite_save_percent) ; i++)
    {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::shuffle(elite_vector.begin(), elite_vector.end(), eng);
        hyperplanes_data.push(this->_crossover(elite_vector[0], elite_vector[1]));
    }
    for(std::size_t i=0; i<elite_vector.size(); i++)
    {
        hyperplanes_data.push(elite_vector[i]);
    }

}

template<typename T, typename U>
void svm_t<T, U> :: train_ga(int level, double mutation_rate, double elite_save_percent, std::size_t variation, int populations)
{
    while (!hyperplanes_data.empty()) hyperplanes_data.pop();
    this->level = level;
    this->mutation_rate = mutation_rate;
    this->elite_save_percent = elite_save_percent;
    this->variation = variation;
    this->populations = populations;
    this->_init_gen();
    for(int i=0; i<this->level; i++)
    {
        this->_next_gen();
    }
}

template<typename T, typename U>
double svm_t<T, U> :: correct_rate()
{
    hyperplane_t<double> elite_hyperplane = hyperplanes_data.top().hyperplane;
    std::size_t data_nums = dataset_test.data.size();
    int correct_nums = 0;
    for (std::size_t i = 0; i <data_nums ; ++i)
    {
        // maybe bug (data)
        // std::cout << (dataset_test.data[i].on(elite_hyperplane) == dataset_test.label[i]) << std::endl;
        correct_nums += ((elite_hyperplane.n * dataset_test.data[i] - elite_hyperplane.b > 0) == dataset_test.label[i]);
    }
    return ((double)correct_nums / (double)data_nums);
}

#endif
