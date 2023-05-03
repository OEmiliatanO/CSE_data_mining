#ifndef __SVM_H__
#define __SVM_H__
#include <vector>
#include <cstdlib>
#include "../../../include/Data.h"

// U must be double or int
// note that SVM::predict returns +1 or -1
template<typename T, typename U>
class SVM_t
{
public:
    double C;
    double P;
    hyperplane_t<T> H;
    SVM_t() = default;
    SVM_t(double c, double p): C(c), P(p) {}

    void fit(const std::vector<point_t<T>>& X, const point_t<U>& Y);
    void fit(const dataset_t<T, U>& dataset);
    U predict(const point_t<T>& X);
	std::vector<U> predict(const dataset_t<T, U>& X);
private:
    point_t<T> SMO(const std::vector<point_t<T>>& X, const point_t<U>& Y);
    void set_hp(const point_t<T>& alpha, const std::vector<point_t<T>>& X, const point_t<U>& Y);
};

template<typename T, typename U>
void SVM_t<T, U>::fit(const std::vector<point_t<T>>& X, const point_t<U>& Y)
{
	this->H.n.resize(X.front().size());
    point_t<T> alpha = this->SMO(X, Y);
    this->set_hp(alpha, X, Y);
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
void SVM_t<T, U>::set_hp(const point_t<T>& alpha, const std::vector<point_t<T>>& X, const point_t<U>& Y)
{
    for (std::size_t i = 0; i < alpha.size(); ++i)
    {
        this->H.n += alpha[i] * Y[i] * X[i];
    }
    std::size_t k = 0;
    while (k < alpha.size() && (alpha[k] <= 0 || alpha[k] >= this->C)) ++k;
	if (k >= alpha.size()) { std::cerr << "didn't find supported vector. exit..." << std::endl; exit(1); }
    this->H.b = Y[k] - this->H.n * X[k];
}

template<typename T, typename Q> 
point_t<T> SVM_t<T, Q>::SMO(const std::vector<point_t<T>>& X, const point_t<Q>& Y)
{
    point_t<T> alpha;
    alpha.resize(X.size());
    for (std::size_t i = 0; i < alpha.size(); ++i)
        alpha[i] = this->C/2;
    
    while (true)
    {
        this->set_hp(alpha, X, Y);
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
        std::size_t j = -1;
        double maxd = std::numeric_limits<double>::lowest();
        for (std::size_t k = 0; k < alpha.size(); ++k)
        {
            if (maxd < std::abs(E[i] - E[k]))
            {
                maxd = std::abs(E[i] - E[k]);
                j = k;
            }
        }
        double U = (Y[i] * Y[j] < 0 ? std::max(0.0, alpha[j] - alpha[i]) : std::max(0.0, alpha[i] + alpha[j] - this->C));
        double V = (Y[i] * Y[j] < 0 ? std::min(C, C + alpha[j] - alpha[i]) : std::max(C, alpha[i] + alpha[j]));
        double K = X[i] * X[i] + X[j] * X[j] - 2.0 * X[i] * X[j];
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
