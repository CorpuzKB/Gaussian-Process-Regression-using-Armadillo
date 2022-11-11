# Gaussian Process Regression in C++/Armadillo
This project is an experimental Gaussian Process regression in C++ using the Armadillo library. The project includes a regression on our [Manila Petroleum Prices]( https://kaggle.com/datasets/e567b9b606404ca157438818c6d2e82f9940b15d42f63cbe69a154b2ecfbc037) dataset. The hyperparameters are trained in [this Python notebook]() and are used in this project by updating the Parameters.txt file.
Early included kernels:
Kernel | Tensorflow Probability Counterpart
| :--- | :--- |
Linear  | [tfp.math.psd_kernels.Linear](https://www.tensorflow.org/probability/api_docs/python/tfp/math/psd_kernels/Linear)
ExpSinSquared  | [tfp.math.ExpSinSquared.RationalQuadratic](https://www.tensorflow.org/probability/api_docs/python/tfp/math/psd_kernels/ExpSinSquared)
RationalQuadratic  | [tfp.math.psd_kernels.RationalQuadratic](https://www.tensorflow.org/probability/api_docs/python/tfp/math/psd_kernels/RationalQuadratic)
ExponentiatedQuadratic  | [tfp.math.psd_kernels.ExponentiatedQuadratic](https://www.tensorflow.org/probability/api_docs/python/tfp/math/psd_kernels/ExponentiatedQuadratic)

