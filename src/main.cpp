#include "LinearRegression.hpp"
#include "NumericCsv.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        const auto rows = readNumericCsv(argc > 1 ? argv[1] : "data/Ice_cream_selling_data.csv");
        if (rows.front().size() != 2 || rows.size() < 3)
            throw std::invalid_argument("Se necesitan dos columnas y al menos tres filas");

        std::vector<double> temperatures, sales;
        for (std::size_t i = 0; i < rows.size(); ++i) {
            if (i % 5 == 0) continue;
            temperatures.push_back(rows[i][0]);
            sales.push_back(rows[i][1]);
        }
        LinearRegression model;
        model.fit(temperatures, sales);
        std::cout << "Entrenamiento: " << sales.size() << ", prueba: " << rows.size() - sales.size()
                  << "\nPendiente: " << model.getWeights().front() << ", intercepto: " << model.getBias()
                  << "\nTemperatura,Real,Prediccion\n";
        for (std::size_t i = 0; i < rows.size(); i += 5)
            std::cout << rows[i][0] << ',' << rows[i][1] << ',' << model.predict(rows[i][0]) << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
