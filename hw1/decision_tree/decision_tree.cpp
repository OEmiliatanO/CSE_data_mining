#include "src/decision_tree.h"

static double log2_(double x)
{
    return (x > 0 ? log2(x) : std::numeric_limits<double>::lowest());
}

// assume the data is all double
struct entgain_attr_where_value_t
{
    // entropy gained
    double entgain;
    // which column
    std::size_t attr;
    // where to cut (sorted)
    std::size_t where;
    // cut value
    double value;

    entgain_attr_where_value_t() = default;
    entgain_attr_where_value_t(double entgain_, std::size_t attr_, std::size_t where_, double value_): 
        entgain{entgain_},
        attr{attr_},
        where{where_},
        value{value_}
    {}

};
// comp
bool operator<(const entgain_attr_where_value_t& lhs, const entgain_attr_where_value_t& other) { return lhs.entgain < other.entgain; }
bool operator>(const entgain_attr_where_value_t& lhs, const entgain_attr_where_value_t& other) { return lhs.entgain > other.entgain; }
bool operator==(const entgain_attr_where_value_t& lhs, const entgain_attr_where_value_t& other) { return lhs.entgain == other.entgain; }
bool operator!=(const entgain_attr_where_value_t& lhs, const entgain_attr_where_value_t& other) { return lhs.entgain != other.entgain; }

bool operator<(entgain_attr_where_value_t&& lhs, entgain_attr_where_value_t&& other) { return lhs.entgain < other.entgain; }
bool operator>(entgain_attr_where_value_t&& lhs, entgain_attr_where_value_t&& other) { return lhs.entgain > other.entgain; }
bool operator==(entgain_attr_where_value_t&& lhs, entgain_attr_where_value_t&& other) { return lhs.entgain == other.entgain; }
bool operator!=(entgain_attr_where_value_t&& lhs, entgain_attr_where_value_t&& other) { return lhs.entgain != other.entgain; }

// use col-th column as prime attribution, find the cut point.
static entgain_attr_where_value_t entgain(dataset_t& dataset, std::size_t col, double ori_ent)
{
    std::stable_sort(dataset.data.begin(), dataset.data.end(), [&col](const auto& lhs, const auto& rhs){ 
            return lhs.point[col] < rhs.point[col]; 
        });

    std::vector<int> prefix;
    prefix.resize(dataset.size());
    prefix[0] = dataset.data[0].label;
    for (std::size_t i = 1; i < dataset.size(); ++i)
        prefix[i] += prefix[i-1] + dataset.data[i].label;

    entgain_attr_where_value_t maxent{std::numeric_limits<double>::lowest(), col, 0, 0};
    for (std::size_t where = 1; where < dataset.size(); ++where)
    {
        if (abs(dataset[where-1].point[col] - dataset[where].point[col]) <= minerr) continue;
        double cutv = (dataset[where-1].point[col] + dataset[where].point[col])/2;
        double front_pp = (double)where/dataset.size();
        double pfront = (double)prefix[where-1]/dataset.size();
        double pback  = (double)(prefix.back() - prefix[where-1])/(dataset.size() - where);
        double ent_front = -(pfront * log2_(pfront) + (where-pfront) * log2_(where-pfront));
        double ent_back  = -( pback * log2_( pback) + (where- pback) * log2_(where- pback));
        maxent = std::max(maxent, entgain_attr_where_value_t{ori_ent - ent_front * front_pp - ent_back * (1-front_pp), col, where, cutv}); 
    }
    return maxent;
}

static bool allsame(const dataset_t& dataset)
{
    const auto& label = dataset.data.front().label;
    for (const auto& data_ : dataset.data)
        if (data_.label != label) return false;
    return true;
}

void dfs_build_tree(node_t *&now, dataset_t dataset)
{
    now = new node_t{};
    if (allsame(dataset))
    {
        now->leaf = true;
        now->label = dataset.data.front().label;
        return;
    }

    int positive = 0, negative = 0;
    for (const data_t& data : dataset.data) positive += data.label;
    negative = dataset.size() - positive;

    double ori_ent = -( positive/dataset.size() * (log2_(positive)-log2_(dataset.size()))
            + negative/dataset.size() * (log2_(negative)-log2_(dataset.size())) );
        
    entgain_attr_where_value_t maxgain{std::numeric_limits<double>::lowest(), 0, 0, 0};
    for (std::size_t col = 0; col < dataset.column(); ++col)
    {
        maxgain = std::max(maxgain, entgain(dataset, col, ori_ent));
        //std::cerr << col << ": " << maxgain.entgain << std::endl;
    }

    now->attr = maxgain.attr;
    now->cutvalue = maxgain.value;
    
    dataset_t ldataset, rdataset;
    std::stable_sort(dataset.data.begin(), dataset.data.end(), [&](const auto& lhs, const auto& rhs){ 
            return lhs.point[maxgain.attr] < rhs.point[maxgain.attr]; 
        });
    // [ dataset.data.begin(), dataset.data.begin() + maxgain.where - 1 ]
    ldataset.data.insert(ldataset.data.end(), dataset.data.begin(), dataset.data.begin() + maxgain.where);
    for (const auto& data : ldataset.data)
        if (data.point[maxgain.attr] > maxgain.value)
        {
            //std::cerr << "dfs_build_tree: left dataset is wrong, data.point[maxgain.attr](" << std::setprecision(9) << maxgain.value << ") <= cutvalue(" << maxgain.value << ")" << std::endl;
            exit(1);
        }
    // [ dataset.data.begin() + maxgain.where, dataset.data.end() ]
    rdataset.data.insert(rdataset.data.end(), dataset.data.begin() + maxgain.where, dataset.data.end());
    for (const auto& data : rdataset.data)
        if (data.point[maxgain.attr] <= maxgain.value)
        {
            //std::cerr << "dfs_build_tree: right dataset is wrong, data.point[maxgain.attr](" << std::setprecision(9) << maxgain.value << ") <= cutvalue(" << maxgain.value << ")" << std::endl;
            exit(1);
        }

    dfs_build_tree(now->l, ldataset);
    dfs_build_tree(now->r, rdataset);
}

void decision_tree_t::build(const dataset_t& dataset_)
{
    this->dataset = dataset_;

    dfs_build_tree(this->tree.root, this->dataset);
}

static int decide_by(const node_t* now, const data_t& data)
{
    if (now == nullptr)
    {
        std::cerr << "decide_by: node is null" << std::endl;
        exit(1);
    }
    if (now->leaf)
        return now->label;
    return decide_by((data.point[now->attr] > now->cutvalue ? now->r : now->l), data);
}

dataset_t decision_tree_t::predict(const dataset_t& dataset_)
{
    dataset_t ret{dataset_};
    for (std::size_t i = 0; i < dataset_.size(); ++i)
       ret[i].label = decide_by(this->tree.root, dataset_[i]);
    return ret;
}

data_t decision_tree_t::predict(const data_t& data_)
{
    data_t ret{data_};
    ret.label = decide_by(this->tree.root, data_);
    return ret;
}


std::ostream& operator<<(std::ostream& os, const decision_tree_t& tree)
{
    // TODO
    os << "dataset = \n" << tree.dataset << std::endl;
    return os;
}
