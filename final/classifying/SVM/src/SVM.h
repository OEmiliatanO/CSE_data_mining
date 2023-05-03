#ifndef __SVM_H__
#define __SVM_H__
#include <vector>
#include "../../../include/Data.h"

// U must be double or int
template<typename T, typename U>
class SVM_t
{
public:
    double C;
    double P;
    hyperplane_t H;
    SVM_t() = default;
    SVM_t(double c, double p): C(c), P() {}

    void fit(const std::vector<point_t<T>>& X, const std::vector<U>& Y);
    void fit(const dataset_t<T, U>& dataset);
    U predict(const point_t<T>& X);
private:
    point_t<T> SMO(const std::vector<point_t<T>>& X, const std::vector<U>& Y);
    void set_hp(const point_t<T>& alpha);
}

template<typename T, typename U>
void SVM_t<T, U>::fit(const std::vector<point_t<T>>& X, const std::vector<U>& Y)
{
    point_t<T> alpha = this->SMO(X, Y);
    this->set_hp(alpha);
}
template<typename T, typename U>
void SVM_t<T, U>::fit(const dataset_t<T, U>& X)
{
    this->fit(X.data, X.label);
}

template<typename T, typename U> 
U SVM_t<T, U>::predict(const point_t<T>& x)
{
    return (H.n * x + H.b > 0 ? 1 : -1);
}
template<typename T, typename U> 
std::vector<U> SVM_t<T, U>::predict(const dataset_t<T, U>& X)
{
    std::vector<U> res;
    for (auto x : X)
        res.emplace_back(H.n * x + H.b > 0 ? 1 : -1);
    return res;
}

template<typename T, typename U> 
void SVM_t<T, U>::set_hp(const point_t<T>& alpha)
{
    for (std::size_t i = 0; i < alpha.size(); ++i)
        this->H.n += alpha[i] * Y[i] * X[i];
    std::size_t k = 0;
    while (alpha[k] <= 0 || alpha[k] >= this->C) ++k;
    this->H.b = Y[k] - this->H.n * X[k];
}

template<typename T, typename U> 
point_t<T> SMO(const std::vector<point_t<T>>& X, const std::vector<U>& Y)
{
    point_t<T> alpha;
    alpha.resize(x[0].size())
    for (std::size_t i = 0; i < alpha.size(); ++i)
        alpha[i] = 1;
    
    while (true)
    {
        this->set_hp(alpha);
        double W0 = 0;
        for (std::size_t i = 0; i < alpha.size(); ++i)
        {
            W0 += alpha[i];
            for (std::size_t j = 0; j < alpha.size(); ++j)
                W0 -= 0.5*alpha[i]*alpha[j]*Y[i]*Y[j]*X[i]*X[j];
        }

        std::vector<double> E;
        E.resize(alpha.size());
        for (std::size_t k = 0; k < alpha.size(); ++k)
            E[k] = this->predict(X[k]) - Y[k];
        std::size_t i = rand() % alpha.size();
        std::size_t j = 0;
        double maxd = std::numeric_limits<double>::lowest
        for (std::size_t k = 0; k < alpha.size(); ++k)
        {
            if (maxd < std::abs(E[i] - E[k]))
            {
                maxd = std::abs(E[i] - E[k]);
                j = k;
            }
        }
        double U = (Y[i] * Y[j] < 0 ? std::max(0, alpha[j] - alpha[i]) : std::max(0, alpha[i] + alpha[j] - C));
        double V = (Y[i] * Y[j] < 0 ? std::min(C, C + alpha[j] - alpha[i]) : std::max(C, alpha[i] + alpha[j]));
        double K = X[i] * X[i] + X[j] * X[j] - 2 * X[i] * X[j];
        double new_alpha_j = alpha[j] + Y[j] * (E[i] - E[j]) / K;
        if (alpha[j] > V) alpha[j] = V;
        else if (alpha[j] < U) alpha[j] = U;
        alpha[i] = alpha[i] + Y[i] * Y[j] * (alpha[j] - new_alpha_j);
        alpha[j] = new_alpha_j;

        double W1 = 0;
        for (std::size_t i = 0; i < alpha.size(); ++i)
        {
            W1 += alpha[i];
            for (std::size_t j = 0; j < alpha.size(); ++j)
                W1 -= 0.5*alpha[i]*alpha[j]*Y[i]*Y[j]*X[i]*X[j];
        }
        if ((W1 - W0) / W0 < this->P)
            break;
    }
    return alpha;
}

#endif
