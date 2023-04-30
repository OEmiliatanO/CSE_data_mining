#ifndef __DATALOADER_H__
#define __DATALOADER_H__
#include <vector>
#include <utility>
#include <string>
#include <string_view>
#include <map>
#include <fstream>
#include <charconv>
#include "Data.h"

template<typename T, typename U>
class Dataloader_t
{
public:
    // record the name of i-th field
    std::vector<std::string_view> tags;
    // data
    dataset_t<T, U> train_data, test_data;

    std::fstream fs;

    Dataloader_t() = default;

    void load(std::string_view& path, dataset_t<T, U>& dataset);
    void load_test(std::string_view&& path);
    void load_test(std::string_view& path);
    void load_train(std::string_view&& path);
    void load_train(std::string_view& path);
	
	void load_train(const dataset_t<T, U>& dataset);
	void load_train(dataset_t<T, U>&& dataset);
	void load_test(const dataset_t<T, U>& dataset);
	void load_test(dataset_t<T, U>&& dataset);
};

static std::vector<std::string_view> split(std::string_view s, char delimiter = ',')
{
    std::vector<std::string_view> ret;

    std::size_t cur;
    while ((cur = s.find(delimiter)) != std::string_view::npos)
    {
        ret.emplace_back(s.substr((size_t)0, cur));
        s = s.substr(cur+1);
    }
    ret.emplace_back(s);
    return ret;
}

template<typename T, typename U>
void Dataloader_t<T, U>::load(std::string_view& path, dataset_t<T, U>& dataset)
{
    dataset.clear();

    std::fstream fs;
    fs.open(path.data());
    if (fs.fail())
    {
        std::cerr << "fail to open the file: " << path << std::endl;
        std::cerr << "stop the process ..." << std::endl;
        exit(1);
    }
    auto& tags = this->tags;
    std::string s; fs >> s;
    std::string_view rawlabels{s};
    tags = split(rawlabels, ',');
    while (fs >> s)
    {
        std::string_view rawdata{s};
        std::vector<std::string_view> alldata = split(rawdata, ',');

        U label = std::atoi(alldata.back().data());
        alldata.pop_back();

        point_t<T> data;
        for (auto& s : alldata)
        {
            char *end_;
            T x = std::strtod(s.data(), &end_);
            data.emplace_back(std::move(x));
        }
        dataset.emplace_back(std::move(data), std::move(label));
    }
}

template<typename T, typename U>
void Dataloader_t<T, U>::load_test(std::string_view& path)
{
    this->load(path, this->test_data);
}
template<typename T, typename U>
void Dataloader_t<T, U>::load_test(std::string_view&& path)
{
    this->load(path, this->test_data);
}

template<typename T, typename U>
void Dataloader_t<T, U>::load_train(std::string_view& path)
{
    this->load(path, this->train_data);
}
template<typename T, typename U>
void Dataloader_t<T, U>::load_train(std::string_view&& path)
{
    this->load(path, this->train_data);
}

template<typename T, typename U>
void Dataloader_t<T, U>::load_test(const dataset_t<T, U>& dataset)
{
    this->test_data = dataset;
}
template<typename T, typename U>
void Dataloader_t<T, U>::load_test(dataset_t<T, U>&& dataset)
{
    this->test_data = std::move(dataset);
}
template<typename T, typename U>
void Dataloader_t<T, U>::load_train(const dataset_t<T, U>& dataset)
{
    this->train_data = dataset;
}
template<typename T, typename U>
void Dataloader_t<T, U>::load_train(dataset_t<T, U>&& dataset)
{
    this->train_data = std::move(dataset);
}


#endif
