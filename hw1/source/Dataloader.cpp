#include "../include/Dataloader.h"

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

void Dataloader_t::load(std::string_view& path, dataset_t& dataset)
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
        std::vector<double> data;
        for (auto& s : alldata)
        {
            double x = 0;
            auto result = std::from_chars(s.data(), s.data()+s.size(), x);
            if (result.ec == std::errc::invalid_argument)
            {
                std::cerr << "Dataloader_t::load: cannot convert string, \"" << s << "\" to double." << std::endl;
                x = 0;
            }
            data.emplace_back(x);
        }
        int label = (std::abs(data.back() - 1) <= minerr);
        data.pop_back();
        dataset.emplace_back(data, label);
    }
}

void Dataloader_t::load_test(std::string_view& path)
{
    this->load(path, this->test_data);
}
void Dataloader_t::load_test(std::string_view&& path)
{
    this->load(path, this->test_data);
}

void Dataloader_t::load_train(std::string_view& path)
{
    this->load(path, this->train_data);
}
void Dataloader_t::load_train(std::string_view&& path)
{
    this->load(path, this->train_data);
}

void Dataloader_t::load_test(const dataset_t& dataset)
{
    this->test_data = dataset;
}
void Dataloader_t::load_test(dataset_t&& dataset)
{
    this->test_data = std::move(dataset);
}
void Dataloader_t::load_train(const dataset_t& dataset)
{
    this->train_data = dataset;
}
void Dataloader_t::load_train(dataset_t&& dataset)
{
    this->train_data = std::move(dataset);
}

// unit test
#ifdef DATALOADER_TEST
int main()
{
    Dataloader_t dataloader;
    std::cout << "load test data..." << std::endl;
    dataloader.load_train("./data/testA/test_data.csv");
    std::cout << dataloader.train_data << std::endl;
    std::cout << "load train data..." << std::endl;
    dataloader.load_test("./data/testA/train_data.csv");
    std::cout << dataloader.test_data << std::endl;
    return 0;
}
#endif