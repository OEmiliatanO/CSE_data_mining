#ifndef __DBSCAN_H__
#define __DBSCAN_H__
#include <vector>
#include <limits>
#include <cstdlib>
#include "../../../include/Data.h"

template<typename T, typename U>
class DBSCAN_t
{
public:
    std::size_t minPts;
    double epsilon;
    DBSCAN_t() = default;
    DBSCAN_t(std::size_t minPts_, double epsilon_): minPts{minPts_}, epsilon{epsilon_} {};

    point_t<std::size_t> fit(const std::vector<point_t<T>>& X);
    point_t<std::size_t> fit(const dataset_t<T, U>& dataset);
};

template<typename T, typename U>
point_t<std::size_t> DBSCAN_t<T, U>::fit(const std::vector<point_t<T>>& X)
{

}

template<typename T, typename U>
point_t<std::size_t> DBSCAN_t<T, U>::fit(const dataset_t<T, U>& dataset)
{
    return this->fit(dataset.data);
}

#endif
