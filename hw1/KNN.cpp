#include "src/KNN.h"

KNN_t::KNN_t(const dataset_t& dataset)
{
    this->train_data = dataset;
}

dataset_t KNN_t::predict(const dataset_t& test_data)
{
	dataset_t result{test_data};
	this->KNN_Method->dataset = this->train_data;
	for (std::size_t i = 0; i < test_data.size(); ++i)
	 	result[i].label = this->KNN_Method->predict(test_data[i]);
	return result;
}

void KNN_t::set_knn_method(const KNN_Method_t& km)
{
	this->KNN_Method = &km;
}
void KNN_t::set_knn_method(KNN_Method_t&& km)
{
	this->KNN_Method = &km;
}
