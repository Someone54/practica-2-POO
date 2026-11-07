#include "LinearRegression.hpp"
#include "NumericCsv.hpp"

#include <cstddef>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Una matriz guarda varias filas. Cada fila representa un estudiante.
using Matrix = std::vector<std::vector<double>>;

// Un vector guarda una sola lista de numeros. En este programa se usa para guardar las notas.
using Vector = std::vector<double>;

int main(int argc, char* argv[]) {
    try {
        // Si se escribe una ruta al ejecutar el programa, usamos esa ruta. Si no se escribe ninguna, usamos el archivo por defecto.
        const std::string path = argc > 1
            ? argv[1]
            : "data/student_exam_scores.csv";

        // Lee el archivo CSV. Cada fila del archivo se convierte en un vector de numeros.
        const Matrix rows = readNumericCsv(path);

        // El archivo debe tener al menos una fila con datos.
        if (rows.empty()) {
            throw std::invalid_argument(
                "El archivo no contiene estudiantes"
            );
        }

        /*
         * Cada fila debe tener cinco columnas:
         * 1. Horas estudiadas.
         * 2. Horas de sueno.
         * 3. Porcentaje de asistencia.
         * 4. Notas anteriores.
         * 5. Nota del examen.
         */
        constexpr std::size_t expectedColumns = 5;
        constexpr std::size_t featureCount = 4;

        // Revisamos que el archivo tenga las cinco columnas esperadas.
        if (rows.front().size() != expectedColumns) {
            throw std::invalid_argument(
                "El archivo debe tener cinco columnas"
            );
        }

        /*
         * X guarda las caracteristicas de los estudiantes. Y guarda las notas reales.
         * Train contiene los datos para entrenar.
         * Test contiene los datos para probar.
         */
        Matrix xTrain;
        Matrix xTest;
        Vector yTrain;
        Vector yTest;

        // Recorremos todos los estudiantes.
        for (std::size_t i = 0; i < rows.size(); ++i) {
            /*
             * Copiamos las primeras cuatro columnas:
             * - Horas estudiadas.
             * - Horas de sueno.
             * - Asistencia.
             * - Notas anteriores.
             */
            const Vector features(
                rows[i].begin(),
                rows[i].begin() + featureCount
            );

            // La quinta columna contiene la nota real del examen.
            const double examScore =
                rows[i][featureCount];

            /*
             * Cada quinta fila se guarda para probar el modelo. Las demas filas se usan para entrenarlo.
             * Esto deja aproximadamente: 80 % para entrenamiento y 20 % para prueba.
             */
            if (i % 5 == 0) {
                xTest.push_back(features);
                yTest.push_back(examScore);
            } else {
                xTrain.push_back(features);
                yTrain.push_back(examScore);
            }
        }

        // Creamos el modelo de regresion lineal.
        LinearRegression model;

        // El modelo aprende usando los estudiantes de entrenamiento.
        model.fit(xTrain, yTrain);

        // Mostramos los numeros con cuatro decimales.
        std::cout << std::fixed
                  << std::setprecision(4);

        // Mostramos cuantos datos se usaron para entrenar.
        std::cout << "Datos de entrenamiento: "
                  << xTrain.size()
                  << '
';

        // Mostramos cuantos datos se reservaron para probar.
        std::cout << "Datos de prueba: "
                  << xTest.size()
                  << '
';

        // Obtenemos los pesos que aprendio el modelo.
        const Vector& weights =
            model.getWeights();

        /*
         * El modelo debe tener cuatro pesos:
         * Peso 1: horas estudiadas.
         * Peso 2: horas de sueno.
         * Peso 3: asistencia.
         * Peso 4: notas anteriores.
         */
        for (std::size_t i = 0;
             i < weights.size();
             ++i) {
            std::cout << "Peso "
                      << i + 1
                      << ": "
                      << weights[i]
                      << '
';
        }

        // Mostramos el bias que aprendio el modelo.
        std::cout << "Bias: "
                  << model.getBias()
                  << '
';

        /*
         * Comparamos las notas reales con las predicciones. Esto permite ver que tan cerca quedo cada resultado.
         */
        std::cout << "
Nota real,Prediccion
";

        for (std::size_t i = 0;
             i < xTest.size();
             ++i) {
            std::cout << yTest[i]
                      << ','
                      << model.predict(xTest[i])
                      << '
';
        }

        /*
         * Calculamos R cuadrado. Un resultado cercano a 1 indica buenas predicciones.
         */
        std::cout << "
R cuadrado: "
                  << model.score(xTest, yTest)
                  << '
';

        return 0;
    } catch (const std::exception& error) {
        /*
         * Si ocurre un problema al leer los datos o entrenar, mostramos el mensaje del error.
         */
        std::cerr << "Error: "
                  << error.what()
                  << '
';

        return 1;
    }
}
