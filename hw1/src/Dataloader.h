#include <vector>
#include <utility>
#include <string>
#include <string_view>
#include <map>
#include <fstream>
#include <charconv>
#include "Data.h"

class Dataloader_t
{
public:
    // record the name of i-th field
    std::vector<std::string_view> tags;
    // data
    dataset_t train_data, test_data;

    std::fstream fs;

    Dataloader_t() = default;

    void load(std::string_view& path, dataset_t& dataset);
    void load_test(std::string_view&& path);
    void load_test(std::string_view& path);
    void load_train(std::string_view&& path);
    void load_train(std::string_view& path);
};
