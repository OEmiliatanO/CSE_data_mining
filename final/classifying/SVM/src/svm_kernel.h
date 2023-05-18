#ifndef __SVM_KERNEL_H__
#define __SVM_KERNEL_H__
#include <cmath>
#include <Data.h>
#include "utility.h"

template<typename T>
class svm_kernel_t
{
public:
    svm_kernel_t() = default;
	virtual ~svm_kernel_t() = default;

    virtual T operator()(const point_t<T>& xi, const point_t<T>& xj) = 0;
};

template<typename T>
class linear_kernel: public svm_kernel_t<T>
{
public:
    linear_kernel() = default;

    T operator()(const point_t<T>& xi, const point_t<T>& xj) override
    {
        return xi*xj;
    }
};

template<typename T>
class poly_kernel: public svm_kernel_t<T>
{
public:
    double gamma, degree, r;
    
    poly_kernel() = default;
    poly_kernel(double gamma_ = 1, double degree_ = 2, double r_ = 1): gamma{gamma_}, degree{degree_}, r{r_} {};

    T operator()(const point_t<T>& xi, const point_t<T>& xj) override
    {
        return pow(gamma + xi*xj, degree);
    }
};

template<typename T>
class rbf_kernel: public svm_kernel_t<T>
{
public:
    double gamma;

    rbf_kernel(double gamma_ = 1): gamma{gamma_} {};

    T operator()(const point_t<T>& xi, const point_t<T>& xj) override
    {
        return exp(-gamma * ((xi-xj) * (xi-xj)));
    }
};

template<typename T>
class sigmoid_kernel: public svm_kernel_t<T>
{
public:
    double gamma, r;

    sigmoid_kernel(double gamma_ = 1, double r_ = 1): gamma{gamma_}, r{r_} {};

    T operator()(const point_t<T>& xi, const point_t<T>& xj) override
    {
        //std::cerr << "tanh(gamma * (xi*xj) + r) = " << tanh(gamma * (xi*xj) + r) << std::endl;
        return tanh(gamma * (xi*xj) + r);
    }
};

#endif
