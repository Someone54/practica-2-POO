#pragma once

#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

inline std::vector<std::vector<double>> readNumericCsv(const std::string& path) {
    std::ifstream file(path);
    if (!file) throw std::runtime_error("No se pudo abrir " + path);

    std::string line;
    if (!std::getline(file, line) || line.find_first_not_of(" \r\t") == std::string::npos)
        throw std::runtime_error("Falta la cabecera");

    const std::size_t columns = 1 + std::count(line.begin(), line.end(), ',');
    std::vector<std::vector<double>> rows;
    int lineNumber = 1;
    while (std::getline(file, line)) {
        ++lineNumber;
        std::istringstream fields(line);
        std::vector<double> row;
        std::string field;
        while (std::getline(fields, field, ',')) {
            std::istringstream input(field);
            double value;
            char extra;
            if (!(input >> value) || !std::isfinite(value) || (input >> extra))
                throw std::runtime_error("Valor invalido en linea " + std::to_string(lineNumber));
            row.push_back(value);
        }
        if (row.size() != columns || line.back() == ',')
            throw std::runtime_error("Columnas invalidas en linea " + std::to_string(lineNumber));
        rows.push_back(row);
    }
    if (file.bad() || rows.empty()) throw std::runtime_error("No se pudieron leer los datos");
    return rows;
}
