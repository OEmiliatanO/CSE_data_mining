#ifndef __DATATRANSFORMER_H__
#define __DATATRANSFORMER_H__
#include "Data.h"
#include <vector>
#include <algorithm>
#include <random>

template<typename T, typename U>
class Datatransformer_t
{
public:
	Datatransformer_t() = default;
	static dataset_t<T, U> gaussian_noise(const dataset_t<T, U>& dataset, double mu, double sigma);
	static dataset_t<T, U> normalize(const dataset_t<T, U>& dataset);
    static dataset_t<T, U> random_pick(const dataset_t<T, U>& dataset, std::size_t n);
    static std::vector<dataset_t<T, U>> split(const dataset_t<T, U>& dataset, std::size_t n);
	static dataset_t<T, U> drop_attr_is_x(const dataset_t<T, U>& dataset, std::size_t attr, const T& x);
	static dataset_t<T, U> drop_attrs_are_xs(const dataset_t<T, U>& dataset, const std::vector<std::size_t>& attrs, const std::vector<T>& xs);
};

template<typename T, typename U>
dataset_t<T, U> Datatransformer_t<T, U>::gaussian_noise(const dataset_t<T, U>& dataset_, double mu, double sigma)
{
    std::default_random_engine genator;
	std::normal_distribution<T> normal_rd(mu, sigma);
	auto rd = std::bind(normal_rd, genator);
	dataset_t<T, U> dataset{dataset_};
	for (auto& data : dataset.data)
		data += point_t<T>{data.point.size(), rd};
	return dataset;
}

struct sigma_mu
{
	double sigma, mu;
	sigma_mu() = default;
	sigma_mu(double mu_, double sigma_): sigma{sigma_}, mu{mu_} {}
};

template<typename T, typename U>
dataset_t<T, U> Datatransformer_t<T, U>::normalize(const dataset_t<T, U>& dataset_)
{
	dataset_t<T, U> dataset{dataset_};
	std::vector<sigma_mu> colinfo;
	std::vector<T> sum, sum2;

	sum.resize(dataset_.column());
	std::fill(sum.begin(), sum.end(), 0);
	sum2.resize(dataset_.column());
	std::fill(sum2.begin(), sum2.end(), 0);
	colinfo.resize(dataset_.column());

	for (auto& data : dataset.data)
		for (std::size_t i = 0; i < colinfo.size(); ++i)
		{
			sum[i] += data[i];
			sum2[i] += data[i]*data[i];
		}
	
	for (std::size_t i = 0; i < colinfo.size(); ++i)
	{
		colinfo[i].sigma = sqrt((sum2[i] - sum[i]*sum[i]/dataset_.size())/dataset_.size());
		colinfo[i].mu = sum[i] / dataset_.size();
	}

	for (auto& data : dataset.data)
		for (std::size_t i = 0; i < colinfo.size(); ++i)
			data[i] = (data[i] - colinfo[i].mu) / colinfo[i].sigma;

	return dataset;
}

template<typename T, typename U>
dataset_t<T, U> Datatransformer_t<T, U>::random_pick(const dataset_t<T, U>& dataset_, std::size_t n)
{
    std::vector<std::size_t> arg;
    for (std::size_t i = 0; i < dataset_.size(); ++i)
        arg.emplace_back(i);
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::random_shuffle(arg.begin(), arg.end(), eng);

    arg.erase(arg.begin() + n, arg.end());
    dataset_t<T, U> ret;
    for (const auto& i : arg) ret.emplace_back(dataset_.data[i], dataset_.label[i]);
    return ret;
}

template<typename T, typename U>
std::vector<dataset_t<T, U>> Datatransformer_t<T, U>::split(const dataset_t<T, U>& dataset_, std::size_t n)
{
    if (n > dataset_.size()) { std::cerr << "Datatransformer_t::split(): n > dataset_.size()" << std::endl; exit(1); }
    dataset_t<T, U> dataset = dataset_;
 
    std::vector<std::size_t> arg;
    for (std::size_t i = 0; i < dataset_.size(); ++i)
        arg.emplace_back(i);
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::shuffle(arg.begin(), arg.end(), eng);

    //std::random_shuffle(dataset.begin(), dataset.end());
    std::vector<dataset_t<T, U>> ret;
    ret.resize(n);
    for (std::size_t i = 0; i < n; ++i)
        for (std::size_t j = 0; j < dataset.size()/n; ++j)
            ret[i].emplace_back(dataset.data[arg[i*(dataset.size()/n)+j]], dataset.label[arg[i*(dataset.size()/n)+j]]);
    return ret;
}

template<typename T, typename U>
dataset_t<T, U> Datatransformer_t<T, U>::drop_attr_is_x(const dataset_t<T, U>& dataset, std::size_t attr, const T& x)
{
	dataset_t<T, U> ret;
	for (std::size_t i = 0; i < dataset.size(); ++i)
	{
		if (dataset.data[i][attr] == x) continue;
		ret.emplace_back(dataset.data[i], dataset.label[i]);
	}
	return ret;
}
template<typename T, typename U>
dataset_t<T, U> Datatransformer_t<T, U>::drop_attrs_are_xs(const dataset_t<T, U>& dataset, const std::vector<std::size_t>& attrs, const std::vector<T>& xs)
{
	dataset_t<T, U> ret;
	for (std::size_t i = 0; i < dataset.size(); ++i)
	{
		bool preserved = true;
		for (std::size_t j = 0; j < attrs.size(); ++j)
			if (dataset.data[i][attrs[j]] == xs[j]) { preserved = false; break; }
		if (preserved) ret.emplace_back(dataset.data[i], dataset.label[i]);
	}
	return ret;
}

#endif
