#ifndef __RANDOM_FOREST_H__
#define __RANDOM_FOREST_H__
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <tuple>
#include "../../include/Data.h"
#include "../../include/Datatransformer.h"
#include "decision_tree.h"
#include "DT_criterion.h"


class random_forest_t
{
public:
    dataset_t dataset;
    Datatransformer_t dispatcher;
    std::size_t maxsize, minsize, n = 10;
    std::vector<decision_tree_t> tree;
    std::unique_ptr<DT_criterion> criterion;

    random_forest_t() = default;
    random_forest_t(std::size_t maxsize_, std::size_t minsize_, std::size_t n_): maxsize{maxsize_}, minsize{minsize_}, n{n_} {}

    void build(const dataset_t& dataset_);
    dataset_t predict(const dataset_t& dataset_);
    int predict(const data_t& data_);
    void set_criterion(std::unique_ptr<DT_criterion> crit);
};
#endif
