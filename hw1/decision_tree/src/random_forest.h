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

template<typename T, typename U>
class random_forest_t
{
public:
    dataset_t<T, U> dataset;
    Datatransformer_t<T, U> dispatcher;
    std::size_t maxsize, minsize, n = 10;
    std::vector<decision_tree_t<T, U>> trees;
    std::shared_ptr<DT_criterion<U>> criterion;

    random_forest_t() = default;
    random_forest_t(std::size_t maxsize_, std::size_t minsize_, std::size_t n_): maxsize{maxsize_}, minsize{minsize_}, n{n_} {}

    void build(const dataset_t<T, U>& dataset_);
    point_t<U> predict(const dataset_t<T, U>& dataset_);
    U predict(const point_t<T>& data_);
    void set_criterion(std::shared_ptr<DT_criterion<U>> crit);
};

template<typename T, typename U>
void random_forest_t<T, U>::build(const dataset_t<T, U>& dataset_)
{
    this->trees.clear();
    this->trees.resize(this->n);
    std::vector<dataset_t<T, U>> split_dataset = this->dispatcher.split(dataset_, this->n);
    [[maybe_unused]]std::size_t i = 0;
    for (auto& tree_ : this->trees)
    {
        tree_.set_criterion(this->criterion);
        tree_.build(split_dataset[i++]);
        //tree_.build(this->dispatcher.random_pick(dataset_, dataset_.size()/this->n));
    }
}

template<typename T, typename U>
point_t<U> random_forest_t<T, U>::predict(const dataset_t<T, U>& dataset_)
{
    point_t<U> ret;
    for (auto& data : dataset_)
        ret.emplace_back(this->predict(data));
    return ret;
}

template<typename T, typename U>
U random_forest_t<T, U>::predict(const point_t<T>& data_)
{
    std::map<U, std::size_t> vote;
    for (auto& tree_ : this->trees)
        ++vote[tree_.predict(data_)];
    std::pair<size_t, U> maxvote{0, 0};
    for (const auto& [kind, cnt] : vote)
    {
        maxvote = std::max(maxvote, std::pair<size_t, U>{cnt, kind});
    }
    return maxvote.second;
}

template<typename T, typename U>
void random_forest_t<T, U>::set_criterion(std::shared_ptr<DT_criterion<U>> crit)
{
    this->criterion = crit;
}
#endif
