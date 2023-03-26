#include "src/DT_criterion.h"

static double log2_(double x)
{
    return (x > 0 ? log2(x) : std::numeric_limits<double>::lowest());
}

// use attr-th column as prime attribution
double DT_criterion::continuous_gain(const dataset_t& dataset, [[maybe_unused]]std::size_t attr, std::size_t where, [[maybe_unused]]double cutv)
{
    double I = (*this)(dataset);
    dataset_t ldataset, rdataset;
    ldataset.data.insert(ldataset.data.end(), dataset.data.begin(), dataset.data.begin() + where);
    rdataset.data.insert(rdataset.data.end(), dataset.data.begin() + where, dataset.data.end());
    double linfo = (*this)(ldataset), rinfo = (*this)(rdataset);
    return I - ( linfo * where/dataset.size() + rinfo - rinfo * where/dataset.size() );
}

double entropy_crit::operator()(const dataset_t& dataset)
{
    double positive = 0, negative = 0;
    for (const data_t& data : dataset.data) positive += data.label;
    negative = dataset.size() - positive;

    return -( positive/dataset.size() * (log2_(positive)-log2_(dataset.size()))
            + negative/dataset.size() * (log2_(negative)-log2_(dataset.size())) );
}

/*
double entropy_crit::discrete_gain(const dataset_t& dataset, std::size_t attr, double cutv)
{
    // TODO
}
*/

double gini_crit::operator()(const dataset_t& dataset)
{
    double positive = 0, negative = 0;
    for (const data_t& data : dataset.data) positive += data.label;
    negative = dataset.size() - positive;

    return 1-((positive/dataset.size())*(positive/dataset.size())+(negative/dataset.size())*(negative/dataset.size()));
}

/*
double gini_crit::discrete_gain(const dataset_t& dataset,std::size_t attr, double cutv)
{
    // TODO
}
*/
