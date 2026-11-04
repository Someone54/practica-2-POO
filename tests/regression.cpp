#include "../src/LinearRegression.hpp"
#include <cmath>
#include <iostream>

int main() {
    LinearRegression model;
    model.fit({-1, 0, 1, 2}, {5, 3, 1, -1});
    const auto close = [](double actual, double expected) {
        return std::abs(actual - expected) < 1e-10;
    };
    if (!close(model.getWeights().at(0), -2) || !close(model.getBias(), 3) ||
        !close(model.predict(4), -5)) {
        std::cerr << "Fallo en los coeficientes o la prediccion\n";
        return 1;
    }
    std::cout << "Prueba correcta\n";
}
