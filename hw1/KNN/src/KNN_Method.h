#ifndef __KNN_METHOD_H__
#define __KNN_METHOD_H__
#include "Data.h"

class KNN_Method_t
{
public:
	KNN_Method_t() = default;
	KNN_Method_t(const KNN_Method_t& other): dataset{other.dataset} {};
	KNN_Method_t(KNN_Method_t&& other): dataset{std::move(other.dataset)} {};
	virtual ~KNN_Method_t() = default;
	
	dataset_t dataset;
	virtual std::vector<data_t> knn(const data_t&, std::size_t) = 0;
	virtual double predict(const data_t&, std::size_t) = 0;
};
#endif
