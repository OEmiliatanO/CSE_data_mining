#ifndef __ANNOY_H__
#define __ANNOY_H__
#include "../../include/Data.h"
#include <vector>
#include <random>

template<typename T, typename U>
class node_t
{
public:
	bool leaf = false;
	dataset_t<T, U> dataset;
	
	hyperplane_t<T> mid;

	node_t<T, U> *l, *r;
	node_t() = default;
	node_t(const hyperplane_t<T>& mid_): mid{mid_} {}
	node_t(hyperplane_t<T>&& mid_): mid{std::forward<decltype(mid_)>(mid_)} {}
};

template<typename T, typename U>
class tree_t
{
public:
	node_t<T, U>* root;
};

template<typename T, typename U>
class annoy : public KNN_Method_t<T, U>
{
public:
    tree_t<T, U> tree;
	std::size_t maxpoint = 13;
	annoy() = default;
	annoy(std::size_t maxp): maxpoint{maxp} {}
	dataset_t<T, U> knn(const dataset_t<T, U>& dataset, const point_t<T>& data, std::size_t k);
	void build(const dataset_t<T, U>& dataset) override;
    void dfs_build(node_t<T, U>*& now, const dataset_t<T, U>& dataset);
    dataset_t<T, U> dfs(node_t<T, U>* now, const point_t<T>& data);
};

template<typename T, typename U>
dataset_t<T, U> annoy<T, U>::dfs(node_t<T, U>* now, const point_t<T>& data)
{
    if (now == nullptr)
    {
        std::cerr << "annoy<T, U>::dfs(): now is nullptr" << std::endl;
        exit(1);
    }
	if (now->leaf) return now->dataset;
	if (data < now->mid)
		return dfs(now->l, data);
	return dfs(now->r, data);
}

/*
template<typename T, typename U>
dataset_t<T, U> annoy<T, U>::bfs(node_t* now, const point_t<T>& data)
{
    //TODO
    exit(1);
}
*/

template<typename T, typename U>
dataset_t<T, U> annoy<T, U>::knn([[maybe_unused]]const dataset_t<T, U>& dataset, const point_t<T>& data, std::size_t k)
{
    //std::cerr << "annoy<T, U>::knn(dataset, data, k) calling..." << std::endl;
	dataset_t<T, U> candiates = this->dfs(this->tree.root, data);
    //std::cerr << "found the candiates(" << candiates.size() << ")" << std::endl;
    if (candiates.size() > k)
    {
        dataset_t<T, U> knns;
        std::vector<std::pair<double, std::size_t>> dist;
        for (std::size_t i = 0; i < candiates.size(); ++i)
            dist.emplace_back(euclidean_dist<T>(candiates.data[i], data), i);
        sort(dist.begin(), dist.end());
        dist.erase(dist.begin()+k, dist.end());
        for (const auto& [dist, id] : dist)
            knns.emplace_back(candiates.data[id], candiates.label[id]);
        return knns;
    }
    return candiates;
    //return bfs(this->tree.root, data);
}

template<typename T, typename U>
void annoy<T, U>::build(const dataset_t<T, U>& dataset)
{
	this->dfs_build(this->tree.root, dataset);
}

template<typename T, typename U>
void annoy<T, U>::dfs_build(node_t<T, U>*& now, const dataset_t<T, U>& dataset)
{
    //std::cerr << "annoy<T, U>::dfs_build(now, dataset) calling..." << std::endl;
    //std::cerr << "annoy<T, U>::dfs_build(now, dataset): dataset.size() = " << dataset.size() << std::endl;

	now = new node_t<T, U>{};
	if (dataset.size() <= this->maxpoint)
	{
		now->leaf = true;
		now->dataset = dataset;
		return;
	}
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<std::size_t> unird(0, dataset.size() - 1);
	std::size_t left = unird(gen);
	std::size_t right = unird(gen);
	auto l = dataset.data[left], r = dataset.data[right];
	hyperplane_t<T> mid{r - l, (r - l)*midpoint(l, r)};
	now->mid = mid;
	dataset_t<T, U> ldataset, rdataset;
	for (std::size_t i = 0; i < dataset.size(); ++i)
	{
		if (dataset.data[i] < mid)
			ldataset.emplace_back(dataset.data[i], dataset.label[i]);
		else
			rdataset.emplace_back(dataset.data[i], dataset.label[i]);
	}
	this->dfs_build(now->l, ldataset);
	this->dfs_build(now->r, rdataset);
}


#endif
