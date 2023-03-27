#ifndef __ANNOY_H__
#define __ANNOY_H__
#include "../../include/Data.h"

struct annoy : public KNN_Method_t
{
    std::vector<data_t> knn(const data_t& data, std::size_t k) override;
    double predict(const data_t& data, std::size_t k) override;
};

#endif
