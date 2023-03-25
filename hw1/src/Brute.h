#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include "Data.h"

struct brute_force
{
    static dataset_t dataset;
    static std::vector<data_t> knn(data_t data, std::size_t k);
    static double predict(data_t data);
};

