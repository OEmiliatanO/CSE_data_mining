#ifndef __SVM_H__
#define __SVM_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "../include/Data.h"
#include "../include/Dataloader.h"
#include "../include/Datatransformer.h"


template<typename T, typename U>
class svm_t
{
    public:
    dataset_t<T, U> dataset;
    svm_t();
    svm_t(dataset_t<T, U>& _dataset);
};
template<typename T, typename U>
svm_t<T,  U> :: svm_t()
{

}

template<typename T, typename U>
svm_t<T,  U> :: svm_t(dataset_t<T, U>& _dataset)
{
    for (std::size_t i = 0; i < _dataset.size(); ++i)
    {
        double _kernel_added = 1;
        int _dim = _dataset[i].size();
        for(std::size_t j=0; j < _dim ; ++j)
        {
            _kernel_added *= pow(_dataset.data[i][j], 2.0/_dim);
            _dataset.data[i][j] *= _dataset.data[i][j];
        }
        _kernel_added *= 1.414;
        _dataset[i].emplace_back(_kernel_added);
    }
    this->dataset = _dataset;
}


#endif