#ifndef __KNN_H__
#define __KNN_H__
#include <vector>
#include <memory>
#include <utility>
#include "../../include/Data.h"
#include "KNN_Method.h"

class KNN_t
{
public:
    dataset_t train_data;
	std::unique_ptr<KNN_Method_t> KNN_Method;
    KNN_t() = default;
    KNN_t(const dataset_t& dataset);
    void train(const dataset_t& dataset);
    void train(dataset_t&& dataset);
	dataset_t predict(const dataset_t& test_data, size_t k);
	void set_knn_method(std::unique_ptr<KNN_Method_t> km);
};
#endif
