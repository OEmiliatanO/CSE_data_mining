#ifndef __KNN_H__
#define __KNN_H__
#include <vector>
#include <memory>
#include <utility>
#include "../../include/Data.h"
#include "KNN_Method.h"

template<typename T, typename U>
class KNN_t
{
public:
    dataset_t<T, U> train_data;
    std::shared_ptr<KNN_Method_t<T, U>> KNN_Method;

    KNN_t() = default;
    KNN_t(const dataset_t<T, U>& dataset) { this->train_data = dataset; }
    KNN_t(dataset_t<T, U>&& dataset) { this->train_data = std::move(dataset); }
    
    void train(const dataset_t<T, U>& dataset) { this->train_data = dataset; }
    void train(dataset_t<T, U>&& dataset) { this->train_data = std::move(dataset); }

	point_t<U> predict(const dataset_t<T, U>& test_data, std::size_t k)
    {
	    return this->KNN_Method->predict(this->train_data, test_data, k);
    }
    point_t<U> predict(const std::vector<point_t<T>>& test_data, std::size_t k)
    {
        return this->KNN_Method->predict(this->train_data, test_data, k);
    }
	void set_knn_method(std::shared_ptr<KNN_Method_t<T, U>> km)
    {
    	this->KNN_Method = km;
    }
};
// KNN_t<T, U> KNN;
// KNN.train(...);
// KNN.predict(test_data, k);
#endif
