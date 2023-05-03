#ifndef __MST_H__
#define __MST_H__
#include <vector>
#include <cstdlib>
#include "../../../include/Data.h"

template<typename T, typename U>
class MST_t
{
public:
    double threhold;
    MST_t() = default;
    MST_t(double threhold_): threhold(threhold_) {}
    point_t<U> fit(std::vector<point_t<T>> X);
};

#endif
