#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <utility>
#include <limits>

template<typename T, typename U>
std::size_t assign(const U& x, const std::vector<T>& centers)
{
    std::pair<double, std::size_t> res{std::numeric_limits<double>::max(), 0};
    for (std::size_t i = 0; i < centers.size(); ++i)
        res = std::min(res, std::pair{euclidean_dist(centers[i], x), i});
    return res.second;
}

template<typename T>
double sign(T x) { return (x > 0 ? 1 : -1); }

template<typename T>
std::size_t argmax(std::vector<T> arr)
{
    if (arr.empty()) return 0;
    
    T maxx = std::numeric_limits<T>::min();
    std::size_t maxi = 0;
    for (std::size_t i = 0; i < arr.size(); ++i)
        if (arr[i] > maxx)
        {
            maxx = arr[i];
            maxi = i;
        }

    return maxi;
}

#endif
