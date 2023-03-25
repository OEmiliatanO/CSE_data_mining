#ifndef __KNN_H__
#define __KNN_H__
#include <vector>
#include <memory>
#include <utility>
#include "Data.h"
#include "KNN_Method.h"

class KNN_t
{
public:
    dataset_t train_data;
	std::unique_ptr<KNN_Method_t> KNN_Method;
    KNN_t() = default;
    KNN_t(const dataset_t& dataset);
    dataset_t predict(const dataset_t& test_data);
	void set_knn_method(const KNN_Method_t& km);
	void set_knn_method(KNN_Method_t&& km);
};
#endif
