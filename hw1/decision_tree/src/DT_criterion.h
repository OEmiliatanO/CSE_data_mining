#ifndef __DT_CRITERION_H__
#define __DT_CRITERION_H__
#include "../../include/Data.h"
#include <map>


class DT_criterion
{
public:
    DT_criterion() = default;
    virtual double operator()(const dataset_t& dataset) = 0;
    virtual double continuous_gain(const dataset_t& dataset, std::size_t attr, std::size_t where, double cutv);
    //virtual double discrete_attr_gain(const dataset_t& dataset, std::size_t attr, double cutv);
};

class entropy_crit: public DT_criterion
{
public:
    double operator()(const dataset_t& dataset) override;
    //double discrete_gain(const dataset_t& dataset, std::size_t attr, double cutv) override;
};

class gini_crit: public DT_criterion
{
public:
    double operator()(const dataset_t& dataset) override;
    //double discrete_gain(const dataset_t& dataset, std::size_t attr, double cutv) override;
};
#endif
