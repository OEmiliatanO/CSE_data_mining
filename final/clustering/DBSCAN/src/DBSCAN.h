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
    point_t<std::size_t> labels;
    std::size_t now_label = 0;
    std::vector<bool> vis;
    
    labels.resize(X.size());
    vis.resize(X.size());

    for (std::size_t i = 0; i < X.size(); ++i)
    {
        if (vis[i]) continue;
        vis[i] = true;
        
        // region Query
        std::vector<std::size_t> neighborPts;
        for (std::size_t j = 0; j < X.size(); ++j)
            if (euclidean_dist(X[i], X[j]) < this->epsilon)
                neighborPts.emplace_back(j);

        // expand cluster
        if (neighborPts.size() < this->minPts)
            labels[i] = 0; // noise
        else
        {
            labels[i] = ++now_label;
            for (std::size_t j = 0; j < neighborPts.size(); ++j)
            {
                const std::size_t Pnum = neighborPts[j];

                if (!vis[Pnum])
                {
                    vis[Pnum] = true;
                    std::vector<std::size_t> neighborPts_;
                    for (std::size_t k = 0; k < X.size(); ++k)
                    {
                        if (!vis[k] && euclidean_dist(X[Pnum], X[k]) < this->epsilon)
                            neighborPts_.emplace_back(k);
                    }
                    if (neighborPts_.size() >= this->minPts)
                        neighborPts.insert(neighborPts.end(), neighborPts_.begin(), neighborPts_.end());
                }
                if (labels[Pnum] == 0)
                    labels[Pnum] = now_label;
            }
        }
    }
    return labels;
}

template<typename T, typename U>
point_t<std::size_t> DBSCAN_t<T, U>::fit(const dataset_t<T, U>& dataset)
{
    return this->fit(dataset.data);
}

#endif
