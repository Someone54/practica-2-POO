#include "LinearRegression.hpp"

#include <cstddef>
#include <iostream>
#include <vector>

// Este objeto existe durante toda la ejecución.
LinearRegression globalModel;

int main() {
    // Este objeto existe solamente dentro de main.
    LinearRegression localModel;

    // Este objeto se crea en memoria dinámica.
    LinearRegression* dynamicModel =
        new LinearRegression;

    std::cout << "DIRECCIONES DE LOS OBJETOS"
              << std::endl;

    std::cout << "Objeto global:  "
              << &globalModel
              << std::endl;

    std::cout << "Objeto local:   "
              << &localModel
              << std::endl;

    std::cout << "Objeto dinamico:"
              << dynamicModel
              << std::endl;

    std::cout << std::endl;
    std::cout << "TAMANOS DE LOS OBJETOS"
              << std::endl;

    std::cout << "Tamano del objeto global: "
              << sizeof(globalModel)
              << " bytes"
              << std::endl;

    std::cout << "Tamano del objeto local: "
              << sizeof(localModel)
              << " bytes"
              << std::endl;

    std::cout << "Tamano del objeto dinamico: "
              << sizeof(*dynamicModel)
              << " bytes"
              << std::endl;

    std::cout << "Tamano del puntero: "
              << sizeof(dynamicModel)
              << " bytes"
              << std::endl;

    /*
     * Creamos un vector dinámico con cinco
     * objetos LinearRegression.
     */
    const std::size_t modelCount = 5;

    std::vector<LinearRegression>* models =
        new std::vector<LinearRegression>(modelCount);

    std::cout << std::endl;
    std::cout << "VECTOR DINAMICO"
              << std::endl;

    std::cout << "Direccion del vector: "
              << models
              << std::endl;

    std::cout << "Direccion de sus elementos: "
              << models->data()
              << std::endl;

    std::cout << "Cantidad de modelos: "
              << models->size()
              << std::endl;

    std::cout << "Tamano del objeto vector: "
              << sizeof(*models)
              << " bytes"
              << std::endl;

    std::cout << "Tamano de un modelo: "
              << sizeof(LinearRegression)
              << " bytes"
              << std::endl;

    /*
     * Esta es una aproximación del espacio reservado
     * para los cinco objetos que contiene el vector.
     */
    const std::size_t elementsSize =
        models->capacity()
        * sizeof(LinearRegression);

    std::cout << "Espacio aproximado de los elementos: "
              << elementsSize
              << " bytes"
              << std::endl;

    std::cout << "Espacio aproximado total: "
              << sizeof(*models) + elementsSize
              << " bytes"
              << std::endl;

    // Liberamos la memoria creada con new.
    delete dynamicModel;
    delete models;

    dynamicModel = nullptr;
    models = nullptr;

    return 0;
}
