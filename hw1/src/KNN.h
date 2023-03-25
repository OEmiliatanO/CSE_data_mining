#include <vector>
#include <utility>
#include "Data.h"

class KNN_t
{
    dataset_t train_data;
    KNN_t() = default;
    KNN_t(dataset_t dataset);
    dataset_t predict(dataset_t test_data);
    data_t predict(data_t data);
};
