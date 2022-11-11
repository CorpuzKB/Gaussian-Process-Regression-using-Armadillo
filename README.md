# Gaussian Process Regression in C++/Armadillo
This Visual Studio solution is a personal experimental Gaussian Process regression in C++ using the Armadillo library. The project includes a regression on our [Manila Petroleum Products Prices](https://www.kaggle.com/datasets/kiocorpuz/manila-petroleum-prices?select=Manila+Petroleum+Price+Dataset.csv ) dataset. The hyperparameters are trained in [this IPython notebook](https://www.kaggle.com/code/kiocorpuz/gaussian-process-regression-for-mpppd) and are used in this project by updating the Parameters.txt file.
Early included kernels:
Kernel | Tensorflow Probability Counterpart
| :--- | :--- |
Linear  | [tfp.math.psd_kernels.Linear](https://www.tensorflow.org/probability/api_docs/python/tfp/math/psd_kernels/Linear)
ExpSinSquared  | [tfp.math.ExpSinSquared.RationalQuadratic](https://www.tensorflow.org/probability/api_docs/python/tfp/math/psd_kernels/ExpSinSquared)
RationalQuadratic  | [tfp.math.psd_kernels.RationalQuadratic](https://www.tensorflow.org/probability/api_docs/python/tfp/math/psd_kernels/RationalQuadratic)
ExponentiatedQuadratic  | [tfp.math.psd_kernels.ExponentiatedQuadratic](https://www.tensorflow.org/probability/api_docs/python/tfp/math/psd_kernels/ExponentiatedQuadratic)
