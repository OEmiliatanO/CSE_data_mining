#include "src/random_forest.h"

void random_forest_t::build(const dataset_t& dataset_)
{
    this->tree.clear();
    this->tree.resize(this->n);
    std::vector<dataset_t> split_dataset = this->dispatcher.split(dataset_, this->n);
    std::size_t i = 0;
    for (auto& tree_ : this->tree)
    {
        tree_.set_criterion(std::unique_ptr<DT_criterion>(new entropy_crit()));
        tree_.build(split_dataset[i++]);
        //tree_.build(this->dispatcher.random_pick(dataset_, dataset_.size()/this->n));
    }
}

dataset_t random_forest_t::predict(const dataset_t& dataset_)
{
    dataset_t dataset = dataset_;
    for (auto& data : dataset)
        data.label = this->predict(data);
    return dataset;
}

int random_forest_t::predict(const data_t& data_) // data_t shall be replace as point_t
{
    std::size_t positive = 0;
    for (auto& tree_ : this->tree)
        positive += tree_.predict(data_);
    return (positive >= (this->n/2));
}

void random_forest_t::set_criterion(std::unique_ptr<DT_criterion> crit)
{
    this->criterion = std::move(crit);
}
