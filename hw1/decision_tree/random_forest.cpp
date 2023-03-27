#include "src/random_forest.h"

void random_forest_t::build(const dataset_t& dataset_)
{
    this->tree.clear();
    this->tree.resize(this->n);
    std::vector<dataset_t> split_dataset = this->dispatcher.split(dataset_, this->n);
    std::size_t i = 0;
    for (auto& tree : this->tree)
    {
        tree.set_criterion(std::unique_ptr<DT_criterion>{new decltype(this->criterion)});
        tree.build(split_dataset[i++]);
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
    int positive = 0;
    for (const auto& tree : this->tree)
        positive += tree.predict(data_);
    return (positive >= (this->n/2));
}

void random_forest_t::set_criterion(std::unique_ptr<DT_criterion> crit)
{
    this->criterion = std::move(crit);
}
