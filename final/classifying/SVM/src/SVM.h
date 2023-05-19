#ifndef __SVM_H__
#define __SVM_H__
#include <vector>
#include <cstdlib>
#include <memory>
#include <vector>
#include "Data.h"
#include "svm_kernel.h"

// U must be double or int
// note that SVM::predict returns +1 or -1
template<typename T, typename U>
class SVM_t
{
public:
    double C;
    double P;
    std::shared_ptr<svm_kernel_t<double>> kernel;
    point_t<double> alpha;
    std::vector<point_t<T>> X;
    point_t<U> Y;
    double b;

    SVM_t() { kernel = std::make_shared<linear_kernel<T>>(); };
    SVM_t(double c, double p): C(c), P(p) { kernel = std::make_shared<linear_kernel<T>>(); }

    void fit(const std::vector<point_t<T>>& X, const point_t<U>& Y);
    void fit(const dataset_t<T, U>& dataset);
    U predict(const point_t<T>& X);
	std::vector<U> predict(const dataset_t<T, U>& X);
private:
    void SMO();
    void set_shift();
};

template<typename T, typename U>
void SVM_t<T, U>::fit(const std::vector<point_t<T>>& X, const point_t<U>& Y)
{
    this->X = X, this->Y = Y;
    if (X.empty() or Y.empty()) return;
    this->SMO();
    this->set_shift();
}
template<typename T, typename U>
void SVM_t<T, U>::fit(const dataset_t<T, U>& X)
{
    this->fit(X.data, X.label);
}

template<typename T, typename U> 
U SVM_t<T, U>::predict(const point_t<T>& x)
{
    double res = 0;
    
    for (std::size_t i = 0; i < this->alpha.size(); ++i)
        res += this->alpha[i] * this->Y[i] * (*this->kernel)(this->X[i], x);
    res += this->b;

    return sign(res);
}
template<typename T, typename U> 
std::vector<U> SVM_t<T, U>::predict(const dataset_t<T, U>& X)
{
    std::vector<U> res;
    for (auto x : X)
        res.emplace_back(this->predict(x));
    return res;
}

template<typename T, typename U>
void SVM_t<T, U>::set_shift()
{
    // find sv
    auto is_sv = [&](double alpha_){ return alpha_ > 0 && alpha_ < this->C; };
    auto k = std::find_if(this->alpha.begin(), this->alpha.end(), is_sv) - this->alpha.begin();
    //while (k < this->alpha.size() && (this->alpha[k] <= 0 || this->alpha[k] >= this->C)) ++k;
	if (k >= (long long)this->alpha.size()) { std::cerr << "didn't find supported vector. exit..." << std::endl; exit(1); }

    double res = 0;
    for (std::size_t i = 0; i < this->alpha.size(); ++i)
        res += this->alpha[i] * this->Y[i] * (*this->kernel)(this->X[i], this->X[k]);
    this->b = this->Y[k] - res;
}

template<typename T, typename Q> 
void SVM_t<T, Q>::SMO()
{
    std::random_device rd;
    std::default_random_engine gen(0);
    std::uniform_real_distribution<> unid(0, this->C);
    alpha.clear();
    alpha.resize(X.size());
    for (std::size_t i = 0; i < alpha.size(); ++i)
        alpha[i] = unid(gen);
    
    while (true)
    {
        this->set_shift();
        double W0 = 0;
        for (std::size_t n = 0; n < alpha.size(); ++n)
        {
            W0 += alpha[n];
            for (std::size_t m = 0; m < alpha.size(); ++m)
                W0 -= 0.5*alpha[n]*alpha[m] * Y[n]*Y[m] * (*this->kernel)(X[n], X[m]);
        }
        //std::cerr << alpha << std::endl;

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
        double K = (*this->kernel)(X[i], X[i]) + (*this->kernel)(X[j], X[j]) - 2.0 * (*this->kernel)(X[i], X[j]);
        double new_alpha_j = alpha[j] + Y[j] * (E[i] - E[j]) / K;
        if (not std::isfinite(new_alpha_j))
        {
            std::cerr << "alpha[j] = " << alpha[j] << std::endl;
            std::cerr << "Y[j] = " << Y[j] << std::endl;
            std::cerr << "E[i] = " << E[i] << std::endl;
            std::cerr << "E[j] = " << E[j] << std::endl;
            std::cerr << "K = " << K << std::endl;
        }
        if (alpha[j] > V) alpha[j] = V;
        else if (alpha[j] < U) alpha[j] = U;
        alpha[i] = alpha[i] + Y[i] * Y[j] * (alpha[j] - new_alpha_j);
        alpha[j] = new_alpha_j;
        
        double W1 = 0;
        for (std::size_t n = 0; n < alpha.size(); ++n)
        {
            W1 += alpha[n];
            for (std::size_t m = 0; m < alpha.size(); ++m)
                W1 -= 0.5*alpha[n]*alpha[m] * Y[n]*Y[m] * (*this->kernel)(X[n], X[m]);
        }
        //std::cerr << (W1 - W0) / W0 << std::endl;
        if (not std::isfinite((W1 - W0) / W0))
        {
            std::cerr << "in SVM::SMO(): (W1 - W0) / W0 = " << (W1 - W0) / W0 << std::endl;
            exit(1);
        }
        if ((W1 - W0) / W0 < this->P)
            break;
    }
}

#endif
