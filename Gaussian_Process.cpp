#include "Gaussian_Process.h"

void Gaussian_Process::init(vec params, std::string nm)
{
	observation_noise_variance = params(0);
	smooth_amplitude = params(1);  smooth_length_scale = params(2);
	bias_variance = params(10); slope_variance = params(11); shift = params(12);
	periodic_amplitude = params(3), periodic_length_scale = params(4), periodic_period = params(5);	periodic_local_length_scale = params(6);
	irregular_amplitude = params(7), irregular_length_scale = params(8), irregular_scale_mixture = params(9);
	name = nm;
}

Mat<double> Gaussian_Process::kernel(Mat<double> X1, Mat<double> X2)
{
	return   Kernel_Linear(X1, X2, bias_variance, slope_variance, shift)
		+ (Kernel_ExponentiatedQuadratic(X1, X2, periodic_local_length_scale)
			% Kernel_ExpSinSquared(X1, X2, periodic_amplitude, periodic_length_scale, periodic_period))
		+ Kernel_RationalQuadratic(X1, X2, irregular_length_scale, irregular_amplitude, irregular_scale_mixture)
		+ Kernel_ExponentiatedQuadratic(X1, X2);
}

void Gaussian_Process::RegressionModel(Mat<double> N, Mat<double> X, Mat<double> y)
{
	Mat<double> K_XX = kernel(X, X);
	Mat<double> K_XN = kernel(X, N);
	Mat<double> K_NN = kernel(N, N);
	Mat<double> K = K_XN.t() * inv_sympd(K_XX + observation_noise_variance * eye(K_XX.n_cols, K_XX.n_rows));
	predict_mean = K * (y);
	predict_covariance = K_NN - K * K_XN;
	predict_std = sqrt(predict_covariance.diag());
}