#ifndef __DATATRANSFORMER_H__
#define __DATATRANSFORMER_H__
#include "Data.h"
#include <vector>
#include <algorithm>
#include <random>

class Datatransformer_t
{
public:
	Datatransformer_t() = default;
	dataset_t gaussian_noise(const dataset_t& dataset, double mu, double sigma);
	dataset_t normalize(const dataset_t& dataset);
    dataset_t random_pick(const dataset_t& dataset, std::size_t n);
    std::vector<dataset_t> split(const dataset_t& dataset, std::size_t n);
};

#endif
