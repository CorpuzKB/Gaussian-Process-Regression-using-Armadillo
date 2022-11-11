#pragma once
#include <armadillo>

using namespace arma;

class Kernels
{
public:
	Mat<double> Kernel_l2Norm(Mat<double> X1, Mat<double> X2);
	Mat<double> Kernel_ExponentiatedQuadratic(Mat<double> X1, Mat<double> X2, double length_scale = 1.0, double amplitude = 1.0);
	Mat<double> Kernel_RationalQuadratic(Mat<double> X1, Mat<double> X2, double length_scale = 1.0, double amplitude = 1.0, double scale_mixture_rate = 1);
	Mat<double> Kernel_ExpSinSquared(Mat<double> X1, Mat<double> X2, double amplitude = 1.0, double length_scale = 1.0, double period = 1.0);
	Mat<double> Kernel_Linear(Mat<double> X1, Mat<double> X2, double bias_variance = 0.0, double slope_variance = 1.0, double shift = 0.0);
};
