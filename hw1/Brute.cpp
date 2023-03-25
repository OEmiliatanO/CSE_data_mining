#include "src/Brute.h"

std::vector<int> argsort(const std::vector<double>& dist)
{
    std::vector<std::pair<int, double>> vec;
    std::vector<int> result;
    for (std::size_t i = 0; i < dist.size(); ++i)
        vec.emplace_back(i, dist[i]);
    std::sort(vec.begin(), vec.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    for (std::size_t i = 0; i < dist.size(); ++i)
        result.emplace_back(vec[i]);
    return result;
}

std::vector<data_t> brute_force::knn(const data_t& data, std::size_t k)
{
    std::vector<double> dist;
    for (std::size_t i = 0; i < data.size(); ++i)
        dist.emplace_back(euclidean_dist(brute_force::dataset.data[i].point, data.point));
    std::vector<int> dist_arg = argsort(dist);
    std::vector<data_t> result;
    for (auto& i : dist_arg) result.emplace_back(brute_force::dataset[i]);
    return result;
}

double brute_force::predict(const data_t& data, std::size_t k=3)
{
    std::vector<data_t> knns = brute_force::knn(data, k);

}
