#ifndef __DT_CRITERION_H__
#define __DT_CRITERION_H__
#include "../../include/Data.h"
#include <map>


template<typename U>
class DT_criterion
{
public:
    DT_criterion() = default;
    virtual double operator()(const point_t<U>& dataset) = 0;
    virtual double continuous_gain(const point_t<U>& dataset, std::size_t attr, std::size_t where);
    //virtual double discrete_attr_gain(const dataset_t& dataset, std::size_t attr, double cutv);
};

template<typename U>
class entropy_crit: public DT_criterion<U>
{
public:
    double operator()(const point_t<U>& dataset) override;
    //double discrete_gain(const dataset_t& dataset, std::size_t attr, double cutv) override;
};

template<typename U>
class gini_crit: public DT_criterion<U>
{
public:
    double operator()(const point_t<U>& dataset) override;
    //double discrete_gain(const dataset_t& dataset, std::size_t attr, double cutv) override;
};

template<typename T>
static double log2_(T x)
{
    return (x > 0 ? log2(x) : std::numeric_limits<double>::lowest());
}

// use attr-th column as prime attribution
template<typename U>
double DT_criterion<U>::continuous_gain(const point_t<U>& label_, [[maybe_unused]]std::size_t attr, std::size_t where)
{
    double I = (*this)(label_);
    point_t<U> llabel, rlabel;
    llabel.x.insert(llabel.x.end(), label_.x.begin(), label_.x.begin() + where);
    rlabel.x.insert(rlabel.x.end(), label_.x.begin() + where, label_.x.end());
    double linfo = (*this)(llabel), rinfo = (*this)(rlabel);
    return I - ( linfo * where/label_.size() + rinfo - rinfo * where/label_.size() );
}

template<typename U>
double entropy_crit<U>::operator()(const point_t<U>& label_)
{
    std::map<U, std::size_t> class_cnt;
    for (const auto& label : label_) ++class_cnt[label];

    double sum = 0;
    for (auto& [label, cnt] : class_cnt)
        sum += (double)cnt/label_.size() * (log2_(cnt) - log2_(label_.size()));

    return -sum;
}

/*
double entropy_crit::discrete_gain(const dataset_t& dataset, std::size_t attr, double cutv)
{
    // TODO
}
*/

template<typename U>
double gini_crit<U>::operator()(const point_t<U>& label_)
{
    std::map<U, std::size_t> class_cnt;
    for (const auto& label : label_) ++class_cnt[label];

    double sum = 0;
    for (auto& [label, cnt] : class_cnt)
        sum += ((double)cnt/label_.size()) * ((double)cnt/label_.size());

    return 1-sum;
}

/*
double gini_crit::discrete_gain(const dataset_t& dataset,std::size_t attr, double cutv)
{
    // TODO
}
*/
#endif
