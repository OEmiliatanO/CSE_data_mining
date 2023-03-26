#ifndef __DECISION_TREE_H__
#define __DECISION_TREE_H__
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <tuple>
#include "Data.h"
#include "DT_criterion.h"

struct node_t
{
    // if this node is leaf, the label is matter
    bool leaf = false;
    int label;
    // otherwise, attr and cut are the important part
    std::size_t attr;
    double cutvalue;
    // left is no or <=, right is yes or >
    node_t *l = nullptr, *r = nullptr;
    void add(node_t *ladded, node_t *radded);
    node_t() = default;
    ~node_t()
    { 
        if (l != nullptr) { delete l; }
        if (r != nullptr) { delete r; }
    }
};

struct tree_t
{
    node_t* root = nullptr;
    void add(node_t *node, node_t *ladded, node_t *radded);
    tree_t() = default;
    ~tree_t()
    {
        if (root != nullptr) delete root;
    }
};


class decision_tree_t
{
public:
    dataset_t dataset;
    tree_t tree;
    std::unique_ptr<DT_criterion> criterion;
    void build(const dataset_t& dataset_);
    dataset_t predict(const dataset_t& dataset_);
    data_t predict(const data_t& data_);
    void dfs_build_tree(node_t *&now, dataset_t dataset);
    void set_criterion(std::unique_ptr<DT_criterion> crit);
    friend std::ostream& operator<<(std::ostream& os, const decision_tree_t& tree);
};
#endif
