#pragma once
#include <armadillo>
#include <string>
#include "Kernels.h"

using namespace arma;

class Gaussian_Process : public Kernels {
public:
	double observation_noise_variance = 0, bias_variance = 0, slope_variance = 0, shift = 0,
		periodic_amplitude = 0, periodic_length_scale = 0, periodic_period = 0, periodic_local_length_scale = 0,
		irregular_amplitude = 0, irregular_length_scale = 0, irregular_scale_mixture = 0,
		smooth_amplitude = 0, smooth_length_scale = 0, mean = 0, std = 0;
	Mat<double> predict_mean, predict_covariance, predict_std;
	std::string name;
	void init(vec params, std::string name = "");
	void RegressionModel(Mat<double> N, Mat<double> X, Mat<double> y);
	Mat<double> kernel(Mat<double> X1, Mat<double> X2);
};