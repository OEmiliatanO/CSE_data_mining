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

	node_t<T> *l, *r;
	node_t() = default;
	node_t(const hyperplane<T>& mid_): mid{mid_} {}
	node_t(hyperplane<T>&& mid_): mid{std::forward<decltype(mide_)>(mid_)} {}
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
	std::size_t maxpoint = 10;
	annoy() = default;
	annoy(std::size_t maxp): maxpoint{maxp} {}
	std::vector<std::size_t> knn(const dataset_t<T, U>& dataset, const point_t<T>& data, std::size_t k);
	void build(const dataset_t<T, U>& dataset) override;
};

template<typename T, typename U>
dataset_t<T, U> annoy<T, U>::dfs(node_t* now, const point_t<T>& data)
{
	if (now->leaf) return now->dataset;
	if (data < now->mid)
		return dfs(now->l, data);
	return dfs(now->r, data);
}

template<typename T, typename U>
std::vector<std::size_t> annoy<T, U>::knn(const dataset_t<T, U>& dataset, const point_t<T>& data, std::size_t k)
{
	
}

template<typename T, typename U>
void annoy<T, U>::build(const dataset<T, U>& dataset)
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<std::size_t> unird(0, dataset.size());
	this->dfs_build(this->tree->root, dataset, gen, unird);
}

template<typename T, typename U>
void annoy<T, U>::dfs_build(node_t* now, const dataset<T, U>& dataset, std::default_random_engine& gen, std::uniform_int_distribution<std::size_t>& unird)
{
	now = new node_t<T, U>{};
	if (dataset.size() <= this->maxpoint)
	{
		now->leaf = true;
		now->dataset = dataset;
		return;
	}
	std::size_t now = unird(gen);
	std::size_t prev = unird(gen);
	auto l = dataset.data[args[i]], r = dataset.data[args[i-1]];
	hyperplane_t mid{r - l, (r - l)*midpoint(l, r)};
	now->mid = mid;
	dataset<T, U> ldataset, rdataset;
	for (std::size_t i = 0; i < dataset.size(); ++i)
	{
		if (dataset.data[i] < mid)
			ldataset.emplace_back(dataset.data[i], dataset.label[i]);
		else
			rdataset.emplace_back(dataset.data[i], dataset.label[i]);
	}
	this->dfs_build(now->l, ldataset, gen, unird);
	this->dfs_build(now->r, rdataset, gen, unird);
}


#endif
