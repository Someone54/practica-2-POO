#include "NumericCsv.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        const auto rows = readNumericCsv(argc > 1 ? argv[1] : "data/Ice_cream_selling_data.csv");
        std::cout << rows.size() << " filas, " << rows.front().size() << " columnas\n";
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
