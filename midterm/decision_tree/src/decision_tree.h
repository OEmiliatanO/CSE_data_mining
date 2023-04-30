#ifndef __DECISION_TREE_H__
#define __DECISION_TREE_H__
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <tuple>
#include "../../include/Data.h"
#include "DT_criterion.h"

template<typename T, typename U>
class node_t;

template<typename T, typename U>
class tree_t;

template<typename T, typename U>
class decision_tree_t;

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const decision_tree_t<T, U>& tree);

template<typename T, typename U>
class node_t
{
public:
    // if this node is leaf, the label is matter
    bool leaf = false;
    U label;
    // otherwise, attr and cut are the important part
    std::size_t attr;
    T cutvalue;
    // left is no or <=, right is yes or >
    node_t<T, U> *l = nullptr, *r = nullptr;
    void add(node_t<T, U> *ladded, node_t<T, U> *radded);
    node_t() = default;
    ~node_t()
    { 
        if (l != nullptr) { delete l; }
        if (r != nullptr) { delete r; }
    }
};

template<typename T, typename U>
class tree_t
{
public:
    node_t<T, U>* root = nullptr;
    void add(node_t<T, U> *node, node_t<T, U> *ladded, node_t<T, U> *radded);
    tree_t() = default;
    ~tree_t()
    {
        if (root != nullptr) delete root;
    }
};


template<typename T, typename U>
class decision_tree_t
{
public:
    dataset_t<T, U> dataset;
    tree_t<T, U> tree;
    std::shared_ptr<DT_criterion<U>> criterion;
    
    void build(const dataset_t<T, U>& dataset_);
    
    point_t<U> predict(const dataset_t<T, U>& dataset_);
    U predict(const point_t<T>& data_);
    
    void dfs_build_tree(node_t<T, U> *&now, dataset_t<T, U> dataset);
    
    void set_criterion(std::shared_ptr<DT_criterion<U>> crit);

    friend std::ostream& operator<< <> (std::ostream& os, const decision_tree_t<T, U>& tree);
};

template<typename T, typename U>
static bool same_label(const dataset_t<T, U>& dataset)
{
    const auto& label = dataset.label[0];
    for (const auto& label_ : dataset.label)
        if (label_ != label) return false;
    return true;
}

template<typename T>
struct foo
{
    double infogain;
    std::size_t attr;
    std::size_t where;
    T cutv;
    std::vector<std::size_t> arg;
    foo() = default;
    foo(double infogain_, std::size_t attr_, std::size_t where_, T cutv_, const std::vector<std::size_t>& arg_): 
        infogain{infogain_}, 
        attr{attr_}, 
        where{where_}, 
        cutv{cutv_},
        arg{arg_}
    {}
    friend bool operator<(const foo<T>& lhs, const foo<T>& rhs) { return lhs.infogain < rhs.infogain; }
};

template<typename T>
bool operator<(const foo<T>& lhs, const foo<T>& rhs) { return lhs.infogain < rhs.infogain; }

template<typename T>
static std::vector<std::size_t> argsort(const std::vector<point_t<T>>& vec, std::size_t attr, const std::function<bool(const std::pair<std::size_t, T>& lhs, const std::pair<std::size_t, T>& rhs)> comp)
{
    std::vector<std::pair<std::size_t, T>> arg;
    std::vector<std::size_t> result;
    for (std::size_t i = 0; i < vec.size(); ++i)
        arg.emplace_back(i, vec[i][attr]);
    std::sort(arg.begin(), arg.end(), comp);
    for (std::size_t i = 0; i < vec.size(); ++i)
        result.emplace_back(arg[i].first);
    return result;
}

template<typename T, typename U>
void decision_tree_t<T, U>::dfs_build_tree(node_t<T, U> *&now, dataset_t<T, U> dataset)
{
    if (dataset.size() == 0) { std::cerr << "decision_tree_t::dfs_build_tree: dataset is empty." << std::endl; exit(1); }
    now = new node_t<T, U>{};
    if (same_label<T, U>(dataset))
    {
        now->leaf = true;
        now->label = dataset.label[0];
        return;
    }

    foo<T> maxgain {std::numeric_limits<double>::lowest(), 0, 0, 0, std::vector<std::size_t>{}};
    for (std::size_t attr = 0; attr < dataset.column(); ++attr)
    {
        std::vector<std::size_t> arg = argsort<T>(dataset.data, attr, [](const std::pair<std::size_t, T>& lhs, const std::pair<std::size_t, T>& rhs) { 
                    return lhs.second < rhs.second; 
                });

        point_t<U> sorted_label;
        for (const auto& id : arg) sorted_label.emplace_back(dataset.label[id]);

        for (std::size_t where = 1; where < dataset.data.size(); ++where)
        {
            std::size_t now = arg[where], prev = arg[where-1];
            if (std::abs(dataset.data[now][attr] - dataset.data[prev][attr]) <= minerr) continue;
            T cutv = (dataset.data[now][attr] + dataset.data[prev][attr]) / 2;
            maxgain = std::max(maxgain, foo{this->criterion->continuous_gain(sorted_label, attr, where), attr, where, cutv, arg});
            //std::cerr << this->criterion->continuous_gain(sorted_label, attr, where) << std::endl;
        }
    }

    now->attr = maxgain.attr;
    now->cutvalue = maxgain.cutv;
    
    dataset_t<T, U> ldataset, rdataset;
    std::size_t i = 0;
    for (; i < maxgain.where; ++i)
        ldataset.emplace_back(dataset.data[maxgain.arg[i]], dataset.label[maxgain.arg[i]]);

    for (; i < dataset.size(); ++i)
        rdataset.emplace_back(dataset.data[maxgain.arg[i]], dataset.label[maxgain.arg[i]]);

    // [ dataset.data.begin(), dataset.data.begin() + maxgain.where - 1 ]
    i = 0;
    for (auto& data : ldataset.data)
    {
        if (data[maxgain.attr] > maxgain.cutv) { std::cout << i << "/" << maxgain.where << ": ldataset: data[attr](" << data[maxgain.attr] << ") > cut value(" << maxgain.cutv << ")" << std::endl; exit(1); }
        ++i;
    }
    // [ dataset.data.begin() + maxgain.where, dataset.data.end() ]
    i = 0;
    for (auto& data : rdataset.data)
    {
        if (data[maxgain.attr] <= maxgain.cutv) { std::cout << i << "/" << dataset.size() - maxgain.where << ": rdataset: data[" << maxgain.attr << "](" << data[maxgain.attr] << ") <= cut value(" << maxgain.cutv << ")" << std::endl; exit(1); }
    }
    dfs_build_tree(now->l, ldataset);
    dfs_build_tree(now->r, rdataset);
}

template<typename T, typename U>
void decision_tree_t<T, U>::build(const dataset_t<T, U>& dataset_)
{
    if (this->tree.root != nullptr)
    {
        delete this->tree.root;
        this->tree.root = nullptr;
    }

    this->dataset = dataset_;

    dfs_build_tree(this->tree.root, this->dataset);
}

template<typename T, typename U>
static U decide_by(const node_t<T, U>* now, const point_t<T>& data)
{
    if (now == nullptr)
    {
        std::cerr << "decide_by: node is null" << std::endl;
        exit(1);
    }
    if (now->leaf)
        return now->label;
    return decide_by<T, U>((data[now->attr] > now->cutvalue ? now->r : now->l), data);
}

template<typename T, typename U>
U decision_tree_t<T, U>::predict(const point_t<T>& data_)
{
    return decide_by(this->tree.root, data_);
}

template<typename T, typename U>
point_t<U> decision_tree_t<T, U>::predict(const dataset_t<T, U>& dataset_)
{
    point_t<U> ret;
    for (const auto& data : dataset_)
       ret.emplace_back(this->predict(data));
    return ret;
}

template<typename T, typename U>
void decision_tree_t<T, U>::set_criterion(std::shared_ptr<DT_criterion<U>> crit)
{
    this->criterion = crit;
}

template<typename T, typename U>
std::ostream& print_tree(std::ostream& os, node_t<T, U> *now, int depth)
{
    for (int i = 0; i < depth; ++i) os << " ";
    if (now == nullptr) return os;
    if (now->leaf)
    {
        os << "label: " << now->label << std::endl;
        return os;
    }
    os << "left subtree: attr=" << now->attr << " < " << now->cutvalue << " , right subtree: attr=" << now->attr << " > " << now->cutvalue << std::endl;
    for (int i = 0; i < depth; ++i) os << " ";
    os << "left subtree:" << std::endl;
    print_tree(os, now->l, depth + 1);
    for (int i = 0; i < depth; ++i) os << " ";
    os << "right subtree:" << std::endl;
    print_tree(os, now->r, depth + 1);
    return os;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const decision_tree_t<T, U>& tree)
{
    return print_tree<T, U>(os, tree.tree.root, 0) << std::endl;
}

#endif
