#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <utility>
#include <limits>

template<typename T, typename U>
std::size_t assign(const U& x, const std::vector<T>& centers)
{
    std::pair<double, std::size_t> res{std::numeric_limits<double>::lowest(), 0};
    for (std::size_t i = 0; i < centers.size(); ++i)
        res = std::min(res, std::pair{euclidean_dist(centers[i], x), i});
    return res.second;
}

#endif
