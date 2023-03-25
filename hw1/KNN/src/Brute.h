#ifndef __BRUTE_H__
#define __BRUTE_H__

#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include <map>
#include "Data.h"
#include "KNN_Method.h"

class brute_force: public KNN_Method_t
{
public:
	//brute_force(const brute_force& bf): KNN_Method_t::dataset{bf.dataset} {}
	//brute_force(brute_force&& bf): KNN::Method_t::dataset{std::move(bf.dataset)} {}

    std::vector<data_t> knn(const data_t& data, std::size_t k) override;
    double predict(const data_t& data, std::size_t k) override;
};

#endif
