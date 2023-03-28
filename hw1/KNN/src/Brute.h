#ifndef __BRUTE_H__
#define __BRUTE_H__
#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include "../../include/Data.h"
#include "KNN_Method.h"

template<typename T, typename U>
class brute_force: public KNN_Method_t<T, U>
{
public:
    // find k-nearest points related to "data"
	std::vector<std::size_t> knn(const dataset_t<T, U>& dataset, const point_t<T>& data, std::size_t k) override;
};

static std::vector<std::size_t> argsort(const std::vector<double>& dist)
{
    std::vector<std::pair<std::size_t, double>> arg;
    std::vector<std::size_t> result;
    for (std::size_t i = 0; i < dist.size(); ++i)
        arg.emplace_back(i, dist[i]);
    std::sort(arg.begin(), arg.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    for (std::size_t i = 0; i < dist.size(); ++i)
        result.emplace_back(arg[i].first);
    return result;
}

template<typename T, typename U>
std::vector<std::size_t> brute_force<T, U>::knn(const dataset_t<T, U>& dataset, const point_t<T>& target, std::size_t k)
{
    std::vector<double> dist;
    for (const auto& data : dataset)
        dist.emplace_back(euclidean_dist(data, target));

    std::vector<std::size_t> dist_arg = argsort(dist);
    dist_arg.erase(dist_arg.begin() + k, dist_arg.end());
    return dist_arg;
}

#endif
