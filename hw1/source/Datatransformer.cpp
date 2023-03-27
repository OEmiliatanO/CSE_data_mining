#include "../include/Datatransformer.h"

dataset_t Datatransformer_t::gaussian_noise(const dataset_t& dataset_, double mu, double sigma)
{
	std::default_random_engine genator;
	std::normal_distribution<double> normal_rd(mu, sigma);
	auto rd = std::bind(normal_rd, genator);
	dataset_t dataset{dataset_};
	for (auto& data : dataset.data)
	{
		data.point += point_t{data.point.size(), rd};
	}
	return dataset;
}

struct sigma_mu
{
	double sigma, mu;
	sigma_mu() = default;
	sigma_mu(double mu_, double sigma_): sigma{sigma_}, mu{mu_} {}
};

dataset_t Datatransformer_t::normalize(const dataset_t& dataset_)
{
	dataset_t dataset{dataset_};
	std::vector<sigma_mu> colinfo;
	std::vector<double> sum, sum2;

	sum.resize(dataset_.column());
	std::fill(sum.begin(), sum.end(), 0);
	sum2.resize(dataset_.column());
	std::fill(sum2.begin(), sum2.end(), 0);
	colinfo.resize(dataset_.column());

	for (auto& data : dataset.data)
	{
		for (std::size_t i = 0; i < colinfo.size(); ++i)
		{
			sum[i] += data.point[i];
			sum2[i] += data.point[i]*data.point[i];
		}
	}
	
	for (std::size_t i = 0; i < colinfo.size(); ++i)
	{
		colinfo[i].sigma = sqrt((sum2[i] - sum[i]*sum[i]/dataset_.size())/dataset_.size());
		//if (sum2[i] - sum[i]*sum[i]/dataset_.size() < 0) std::cerr << "Datatransformer::normalize(): sqrt(negative)" << std::endl;
		colinfo[i].mu = sum[i] / dataset_.size();
	}

	for (auto& data : dataset.data)
	{
		for (std::size_t i = 0; i < colinfo.size(); ++i)
			data.point[i] = (data.point[i] - colinfo[i].mu) / colinfo[i].sigma;
	}
	return dataset;
}
