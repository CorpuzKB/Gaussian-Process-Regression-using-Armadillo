#include "Kernels.h"


Mat<double> Kernels::Kernel_l2Norm(Mat<double> X1, Mat<double> X2)
{
	Mat<double> K(X1.n_rows, X2.n_rows, fill::zeros);
	for (int i = 0; i < X1.n_rows; i++) {
		for (int j = 0; j < X2.n_rows; j++) {
			K(i, j) = pow(norm(X1.row(i) - X2.row(j), 2), 2);
		}
	}
	return K;
}

Mat<double> Kernels::Kernel_ExponentiatedQuadratic(Mat<double> X1, Mat<double> X2, double length_scale, double amplitude)
{
	Mat<double> K = Kernel_l2Norm(X1, X2);
	return pow(amplitude, 2) * exp(-K / (2 * pow(length_scale, 2)));
}

Mat<double> Kernels::Kernel_RationalQuadratic(Mat<double> X1, Mat<double> X2, double length_scale, double amplitude, double scale_mixture_rate)
{
	Mat<double> K = Kernel_l2Norm(X1, X2);
	return pow(amplitude, 2) * pow(1 + K / (2 * scale_mixture_rate * pow(length_scale, 2)), -scale_mixture_rate);
}

Mat<double> Kernels::Kernel_ExpSinSquared(Mat<double> X1, Mat<double> X2, double amplitude, double length_scale, double period)
{
	Mat<double> K = sqrt(Kernel_l2Norm(X1, X2));
	K = pow(sin(datum::pi * K / period), 2);
	return pow(amplitude, 2) * exp(-2 * K / (pow(length_scale, 2)));
}

Mat<double> Kernels::Kernel_Linear(Mat<double> X1, Mat<double> X2, double bias_variance, double slope_variance, double shift)
{
	Mat<double> K = (X1 - shift) * (X2 - shift).t();
	return pow(bias_variance, 2) + pow(slope_variance, 2) * K;
}
