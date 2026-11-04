#pragma once

#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

class LinearRegression {
public:
    void fit(const std::vector<double>& x, const std::vector<double>& y) {
        if (x.size() != y.size() || x.size() < 2)
            throw std::invalid_argument("Se necesitan al menos dos pares de datos");

        const long double meanX = std::accumulate(x.begin(), x.end(), 0.0L) / x.size();
        const long double meanY = std::accumulate(y.begin(), y.end(), 0.0L) / y.size();
        long double variance = 0;
        long double covariance = 0;
        for (std::size_t i = 0; i < x.size(); ++i) {
            const long double dx = x[i] - meanX;
            variance += dx * dx;
            covariance += dx * (y[i] - meanY);
        }
        if (variance == 0)
            throw std::invalid_argument("La variable de entrada debe variar");

        const long double slope = covariance / variance;
        const double weight = static_cast<double>(slope);
        const double intercept = static_cast<double>(meanY - slope * meanX);
        if (!std::isfinite(weight) || !std::isfinite(intercept))
            throw std::invalid_argument("Coeficientes fuera de rango");
        weights = {weight};
        bias = intercept;
    }

    double predict(double x) const {
        if (weights.empty()) throw std::logic_error("Primero entrene el modelo");
        return weights.front() * x + bias;
    }

    const std::vector<double>& getWeights() const { return weights; }
    double getBias() const { return bias; }

private:
    std::vector<double> weights;
    double bias = 0;
};

