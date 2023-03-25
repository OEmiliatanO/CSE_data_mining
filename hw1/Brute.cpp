#include "src/Brute.h"

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

std::vector<data_t> brute_force::knn(const data_t& data, std::size_t k)
{
    std::vector<double> dist;
    for (std::size_t i = 0; i < this->dataset.size(); ++i)
        dist.emplace_back(euclidean_dist(this->dataset[i].point, data.point));
    std::vector<std::size_t> dist_arg = argsort(dist);
    std::vector<data_t> result;
	for (std::size_t i = 0; i < k; ++i)
		result.emplace_back(this->dataset[dist_arg[i]]);
    return result;
}

double brute_force::predict(const data_t& data, std::size_t k)
{
    std::vector<data_t> knns = brute_force::knn(data, k);
	std::map<double, std::size_t> cnt;
	std::pair<std::size_t, double> maxkind{0, -1.0};
	for (auto& nearby : knns) ++cnt[nearby.label];
	for (auto& [k, v] : cnt) maxkind = std::max(maxkind, std::pair{v, k});
	return maxkind.second;
}

