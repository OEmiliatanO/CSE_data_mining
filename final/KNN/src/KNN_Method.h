#ifndef __KNN_METHOD_H__
#define __KNN_METHOD_H__
#include <algorithm>
#include <vector>
#include <map>
#include "../../include/Data.h"

template<typename T, typename U>
class KNN_Method_t
{
public:
	KNN_Method_t() = default;
	virtual ~KNN_Method_t() = default;
	
	// build essential data structure if need
	virtual void build([[maybe_unused]]const dataset_t<T, U>& dataset) {}
    // find the k-nearest points related to "data"
	virtual dataset_t<T, U> knn(const dataset_t<T, U>& dataset, const point_t<T>& data, std::size_t k) = 0;
    // classify the target
	virtual U predict(const dataset_t<T, U>& dataset, const point_t<T>& target, std::size_t k);
    // classify the targets
	virtual point_t<U> predict(const dataset_t<T, U>& dataset, const dataset_t<T, U>& targets, std::size_t k);
	virtual point_t<U> predict(const dataset_t<T, U>& dataset, const std::vector<point_t<T>>& targets, std::size_t k);
};

// classify the target
template<typename T, typename U>
U KNN_Method_t<T, U>::predict(const dataset_t<T, U>& dataset, const point_t<T>& target, std::size_t k)
{
    dataset_t<T, U> knns = this->knn(dataset, target, k);
	std::map<U, std::size_t> cnt;
	std::pair<std::size_t, U> maxkind{0, 0};
	for (std::size_t nearby = 0; nearby < knns.size(); ++nearby) { ++cnt[knns.label[nearby]]; }
	for (auto& [label, howmany] : cnt) maxkind = std::max(maxkind, std::pair{howmany, label});
	return maxkind.second;
}

// classify the targets
template<typename T, typename U>
point_t<U> KNN_Method_t<T, U>::predict(const dataset_t<T, U>& dataset, const dataset_t<T, U>& targets, std::size_t k)
{
    point_t<U> ret;
    for (const auto& data : targets)
        ret.emplace_back(this->predict(dataset, data, k));
    return ret;
}
template<typename T, typename U>
point_t<U> KNN_Method_t<T, U>::predict(const dataset_t<T, U>& dataset, const std::vector<point_t<T>>& targets, std::size_t k)
{
    point_t<U> ret;
    for (const auto& data : targets)
        ret.emplace_back(this->predict(dataset, data, k));
    return ret;
}
#endif
