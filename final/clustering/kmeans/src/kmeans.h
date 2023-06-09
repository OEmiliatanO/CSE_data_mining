#ifndef __KMEANS_H__
#define __KMEANS_H__
#include <vector>
#include <limits>
#include <cstdlib>
#include <random>
#include "Data.h"
#include "utility.h"

template<typename T, typename U>
class kmeans_t
{
public:
    std::size_t k;
    double theta;
	std::vector<point_t<T>> centers_;
    kmeans_t() = default;
    kmeans_t(std::size_t k_, double theta_): k{k_}, theta{theta_} {};

    point_t<U> fit(const std::vector<point_t<T>>& X);
    point_t<U> fit(const dataset_t<T, U>& dataset);
};

template<typename T, typename U>
point_t<U> kmeans_t<T, U>::fit(const std::vector<point_t<T>>& X)
{
    //std::random_device rd;
    std::default_random_engine gen(0);

	auto try_cnt = 0;

	point_t<U> labels;
    if (X.size() < this->k) { labels.resize(X.size()); return labels; }
	std::vector<point_t<T>> centers;
	std::vector<point_t<T>> ncenters;
	std::vector<std::size_t> label_sizes;

	centers.resize(this->k);
	for (auto& x : centers) x.resize(X.front().size());
	ncenters.resize(this->k);
	for (auto& x : ncenters) x.resize(X.front().size());
	labels.resize(X.size());
	label_sizes.resize(this->k);
    std::vector<std::size_t> choosep;
    for (std::size_t i = 0; i < X.size(); ++i)
        choosep.emplace_back(i);

RETRY:
	while (try_cnt++ <= 10)
	{
        std::shuffle(choosep.begin(), choosep.end(), gen);

		std::fill(label_sizes.begin(), label_sizes.end(), 0);
		for (auto& x : ncenters) x.fill0();

		// random initialize center
		for (std::size_t i = 0; i < this->k; ++i)
            centers[i] = X[choosep[i % choosep.size()]];
		
		bool bk = false;
		while (true)
		{
			// assignment
			for (auto& ls : label_sizes) ls = 0;
			for (std::size_t i = 0; i < X.size(); ++i)
			{
				labels[i] = assign(X[i], centers);
				++label_sizes[labels[i]];
			}

			// calculate WCSS_t
			double WCSS0 = 0;
			for (std::size_t j = 0; j < X.size(); ++j)
				WCSS0 += euclidean_dist(X[j], centers[labels[j]]);

			// update
			for (auto& center : ncenters)
				center.fill0();
			for (std::size_t i = 0; i < X.size(); ++i)
				ncenters[labels[i]] += X[i];
			for (std::size_t i = 0; i < this->k; ++i)
			{
				if (label_sizes[i] == 0) goto RETRY;
				ncenters[i] /= (double)label_sizes[i];
			}
			std::swap(centers, ncenters);
			if (bk) break;
			
			// calculate WCSS_t+1
			// if return rate <= theta, terminate
			double WCSS = 0;
			for (std::size_t j = 0; j < X.size(); ++j)
				WCSS += euclidean_dist(X[j], centers[labels[j]]);
			if (not std::isfinite((WCSS - WCSS0) / WCSS0) or (WCSS - WCSS0) / WCSS0 <= this->theta)
				bk = true;
		}

		this->centers_ = std::move(centers);
		this->centers_.insert(this->centers_.begin(), point_t<T>{});
		for (auto& lb : labels) ++lb;

		return labels;
	}
	return labels;
}

template<typename T, typename U>
point_t<U> kmeans_t<T, U>::fit(const dataset_t<T, U>& dataset)
{
    return this->fit(dataset.data);
}

#endif
