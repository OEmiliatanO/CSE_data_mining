#ifndef __DATATRANSFORMER_H__
#define __DATATRANSFORMER_H__
#include "Data.h"
#include <random>

class Datatransformer_t
{
public:
	Datatransformer_t() = default;
	dataset_t gaussian_noise(const dataset_t& dataset, double mu, double sigma);
	dataset_t normalize(const dataset_t& dataset);
};

#endif
