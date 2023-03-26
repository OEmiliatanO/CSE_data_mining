#include "src/decision_tree.h"
#include "src/DT_criterion.h"

static bool same_label(const dataset_t& dataset)
{
    const auto& label = dataset.data.front().label;
    for (const auto& data_ : dataset.data)
        if (data_.label != label) return false;
    return true;
}

struct foo
{
    double infogain;
    std::size_t attr;
    std::size_t where;
    double cutv;
    foo() = default;
    foo(double infogain_, std::size_t attr_, std::size_t where_, double cutv_): 
        infogain{infogain_}, 
        attr{attr_}, 
        where{where_}, 
        cutv{cutv_}
    {}
};

bool operator<(const foo& lhs, const foo& rhs) { return lhs.infogain < rhs.infogain; }

void decision_tree_t::dfs_build_tree(node_t *&now, dataset_t dataset)
{
    if (dataset.size() == 0) { std::cerr << "decision_tree_t::dfs_build_tree: dataset is empty." << std::endl; exit(1); }
    now = new node_t{};
    if (same_label(dataset))
    {
        now->leaf = true;
        now->label = dataset.data.front().label;
        return;
    }

    foo maxgain {std::numeric_limits<double>::lowest(), 0, 0, 0};
    for (std::size_t attr = 0; attr < dataset.column(); ++attr)
        for (std::size_t where = 1; where < dataset.data.size(); ++where)
        {
            std::stable_sort(dataset.data.begin(), dataset.data.end(), 
                    [&attr](const auto& lhs, const auto& rhs) { 
                        return lhs.point[attr] < rhs.point[attr]; 
                    });
            if (std::abs(dataset.data[where - 1].point[attr] - dataset.data[where].point[attr]) <= minerr) continue;
            double cutv = (dataset.data[where - 1].point[attr] + dataset.data[where].point[attr]) / 2;
            maxgain = std::max(maxgain, foo{this->criterion->continuous_gain(dataset, attr, where, cutv), attr, where, cutv});
        }

    now->attr = maxgain.attr;
    now->cutvalue = maxgain.cutv;
    
    dataset_t ldataset, rdataset;
    std::stable_sort(dataset.data.begin(), dataset.data.end(), 
            [&](const auto& lhs, const auto& rhs){ 
                return lhs.point[maxgain.attr] < rhs.point[maxgain.attr]; 
            });

    // [ dataset.data.begin(), dataset.data.begin() + maxgain.where - 1 ]
    ldataset.data.insert(ldataset.data.end(), dataset.data.begin(), dataset.data.begin() + maxgain.where);
    for (auto& data : ldataset.data)
    {
        if (data.point[maxgain.attr] > maxgain.cutv) { std::cout << "ldataset: data.point[attr](" << data.point[maxgain.attr] << ") > cut value(" << maxgain.cutv << ")" << std::endl; exit(1); }
    }
    // [ dataset.data.begin() + maxgain.where, dataset.data.end() ]
    rdataset.data.insert(rdataset.data.end(), dataset.data.begin() + maxgain.where, dataset.data.end());
    for (auto& data : rdataset.data)
    {
        if (data.point[maxgain.attr] <= maxgain.cutv) { std::cout << "rdataset: data.point[" << maxgain.attr << "](" << data.point[maxgain.attr] << ") <= cut value(" << maxgain.cutv << ")" << std::endl; exit(1); }
    }
    dfs_build_tree(now->l, ldataset);
    dfs_build_tree(now->r, rdataset);
}

void decision_tree_t::build(const dataset_t& dataset_)
{
    if (this->tree.root != nullptr)
    {
        delete this->tree.root;
        this->tree.root = nullptr;
    }

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

void decision_tree_t::set_criterion(std::unique_ptr<DT_criterion> crit)
{
    this->criterion = std::move(crit);
}

std::ostream& print_tree(std::ostream& os, node_t *now, int depth)
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

std::ostream& operator<<(std::ostream& os, const decision_tree_t& tree)
{
    return print_tree(os, tree.tree.root, 0) << std::endl;
}
