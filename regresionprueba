#pragma once

#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

// Esta clase crea y usa modelos de regresion lineal.
class LinearRegression {
public:
    /*
     * Entrena el modelo de regresion simple.
     *
     * x contiene los datos de entrada, como la temperatura.
     * y contiene los resultados, como las ventas de helado.
     */
    void fit(const std::vector<double>& x, const std::vector<double>& y) {
        // Debe existir la misma cantidad de entradas y resultados.
        if (x.size() != y.size() || x.size() < 2)
            throw std::invalid_argument(
                "Se necesitan al menos dos pares de datos"
            );

        // Calculamos el promedio de los valores de X.
        const long double meanX =
            std::accumulate(x.begin(), x.end(), 0.0L) / x.size();

        // Calculamos el promedio de los valores de Y.
        const long double meanY =
            std::accumulate(y.begin(), y.end(), 0.0L) / y.size();

        /*
         * Estas variables ayudan a encontrar la linea
         * que mejor representa los datos.
         */
        long double variance = 0, covariance = 0;

        // Recorremos todos los datos.
        for (std::size_t i = 0; i < x.size(); ++i) {
            // Calculamos la distancia entre X y su promedio.
            const long double dx = x[i] - meanX;

            variance += dx * dx;

            // Miramos como cambian X y Y juntos.
            covariance += dx * (y[i] - meanY);
        }

        // Si todos los valores de X son iguales,
        // no se puede crear una linea.
        if (variance == 0)
            throw std::invalid_argument(
                "La variable de entrada debe variar"
            );

        // Calculamos la inclinacion de la linea.
        const long double slope = covariance / variance;

        // Guardamos la inclinacion como el peso del modelo.
        const double weight = static_cast<double>(slope);

        // Calculamos el punto donde empieza la linea.
        const double intercept =
            static_cast<double>(meanY - slope * meanX);

        // Verificamos que los resultados sean numeros validos.
        if (!std::isfinite(weight) || !std::isfinite(intercept))
            throw std::invalid_argument(
                "Coeficientes fuera de rango"
            );

        // Guardamos lo que aprendio el modelo.
        weights = {weight};
        bias = intercept;
    }

    /*
     * Hace una prediccion con una sola entrada.
     * Esta funcion se usa para el caso de los helados.
     */
    double predict(double x) const {
        // No se puede predecir antes de entrenar.
        if (weights.empty())
            throw std::logic_error(
                "Primero entrene el modelo"
            );

        // Formula: prediccion = peso x entrada + bias.
        return weights.front() * x + bias;
    }

    // Permite consultar los pesos aprendidos.
    const std::vector<double>& getWeights() const {
        return weights;
    }

    // Permite consultar el bias aprendido.
    double getBias() const {
        return bias;
    }

    /*
     * Una matriz es un grupo de filas.
     *
     * Cada fila representa un estudiante.
     * Cada valor de la fila representa una caracteristica.
     */
    using Matrix = std::vector<std::vector<double>>;

    /*
     * Pone todas las columnas en una escala parecida.
     *
     * Esto ayuda porque la asistencia puede llegar a 100,
     * mientras que las horas de estudio llegan aproximadamente a 12.
     */
    Matrix data_scaling(const Matrix& data) {
        // La matriz debe contener datos.
        if (data.empty() || data.front().empty())
            throw std::invalid_argument("Matriz vacia");

        // Cantidad de estudiantes.
        const std::size_t rows = data.size();

        // Cantidad de caracteristicas por estudiante.
        const std::size_t columns = data.front().size();

        // Preparamos un promedio para cada columna.
        means.assign(columns, 0.0);

        // Preparamos una escala para cada columna.
        scales.assign(columns, 0.0);

        // Sumamos los valores de cada columna.
        for (const auto& row : data)
            for (std::size_t j = 0; j < columns; ++j)
                means[j] += row[j];

        // Dividimos para obtener el promedio de cada columna.
        for (double& mean : means)
            mean /= rows;

        /*
         * Calculamos que tanto se separan los valores
         * del promedio de su columna.
         */
        for (const auto& row : data)
            for (std::size_t j = 0; j < columns; ++j) {
                const double difference = row[j] - means[j];
                scales[j] += difference * difference;
            }

        // Terminamos de calcular la escala de cada columna.
        for (double& scale : scales) {
            scale = std::sqrt(scale / rows);

            // Una columna que no cambia no puede escalarse.
            if (scale == 0)
                throw std::invalid_argument(
                    "Una columna no cambia"
                );
        }

        // Copiamos los datos para no cambiar la matriz original.
        Matrix result = data;

        // A cada valor le quitamos el promedio
        // y lo dividimos por la escala de su columna.
        for (auto& row : result)
            for (std::size_t j = 0; j < columns; ++j)
                row[j] =
                    (row[j] - means[j]) / scales[j];

        // Devolvemos la copia con los datos escalados.
        return result;
    }

    /*
     * Entrena el modelo de estudiantes.
     *
     * x contiene las caracteristicas de los estudiantes.
     * y contiene las notas reales.
     * steps indica cuantas veces se corrigen los pesos.
     * rate indica el tamano de cada correccion.
     */
    void fit(
        const Matrix& x,
        const std::vector<double>& y,
        std::size_t steps = 10000,
        double rate = 0.01
    ) {
        // Debe existir una nota por cada estudiante.
        if (x.empty() || x.size() != y.size())
            throw std::invalid_argument(
                "Datos invalidos"
            );

        // Escalamos los datos antes de entrenar.
        const Matrix scaledX = data_scaling(x);

        // Guardamos la cantidad de caracteristicas.
        // En este proyecto son cuatro.
        const std::size_t columns = x.front().size();

        // Todos los pesos empiezan en cero.
        weights.assign(columns, 0.0);

        // El bias empieza en el promedio de las notas.
        bias =
            std::accumulate(y.begin(), y.end(), 0.0)
            / y.size();

        /*
         * Repetimos el entrenamiento varias veces.
         * En cada repeticion intentamos bajar el error.
         */
        for (std::size_t step = 0; step < steps; ++step) {
            // Aqui guardamos cuanto debe cambiar cada peso.
            std::vector<double> weightChange(columns, 0.0);

            // Aqui guardamos cuanto debe cambiar el bias.
            double biasChange = 0.0;

            // Revisamos todos los estudiantes.
            for (std::size_t i = 0; i < scaledX.size(); ++i) {
                // La prediccion empieza con el bias.
                double prediction = bias;

                // Sumamos cada caracteristica multiplicada por su peso.
                for (std::size_t j = 0; j < columns; ++j)
                    prediction +=
                        weights[j] * scaledX[i][j];

                // Comparamos la prediccion con la nota real.
                const double error = prediction - y[i];

                // Usamos el error para corregir el bias.
                biasChange += error;

                // Usamos el error para corregir cada peso.
                for (std::size_t j = 0; j < columns; ++j)
                    weightChange[j] +=
                        error * scaledX[i][j];
            }

            // Este valor ayuda a calcular el tamano de la correccion.
            const double factor = 2.0 / scaledX.size();

            // Corregimos un poco el bias.
            bias -= rate * factor * biasChange;

            // Corregimos un poco cada peso.
            for (std::size_t j = 0; j < columns; ++j)
                weights[j] -=
                    rate * factor * weightChange[j];
        }

        /*
         * El entrenamiento utilizo datos escalados.
         * Aqui dejamos los pesos listos para recibir
         * los valores originales del archivo CSV.
         */
        for (std::size_t j = 0; j < columns; ++j) {
            weights[j] /= scales[j];
            bias -= weights[j] * means[j];
        }
    }

    /*
     * Predice la nota de un estudiante.
     *
     * features contiene:
     * 1. Horas estudiadas.
     * 2. Horas de sueno.
     * 3. Porcentaje de asistencia.
     * 4. Notas anteriores.
     */
    double predict(
        const std::vector<double>& features
    ) const {
        // Debe existir un peso por cada caracteristica.
        if (weights.empty() || features.size() != weights.size())
            throw std::invalid_argument(
                "Datos invalidos"
            );

        // La prediccion empieza con el bias.
        double result = bias;

        // Sumamos cada caracteristica multiplicada por su peso.
        for (std::size_t j = 0; j < weights.size(); ++j)
            result +=
                weights[j] * features[j];

        // Devolvemos la nota calculada.
        return result;
    }

    /*
     * Calcula R cuadrado.
     *
     * R cuadrado compara las predicciones con las notas reales.
     * Un resultado cercano a 1 significa que el modelo funciona bien.
     */
    double score(
        const Matrix& x,
        const std::vector<double>& y
    ) const {
        // Calculamos el promedio de las notas reales.
        const double mean =
            std::accumulate(y.begin(), y.end(), 0.0)
            / y.size();

        // Suma de los errores de las predicciones.
        double errorSum = 0.0;

        // Cambio total que existe entre las notas.
        double totalSum = 0.0;

        // Revisamos todas las notas de prueba.
        for (std::size_t i = 0; i < x.size(); ++i) {
            // Comparamos la nota real con la prediccion.
            errorSum +=
                std::pow(y[i] - predict(x[i]), 2);

            // Comparamos la nota real con el promedio.
            totalSum +=
                std::pow(y[i] - mean, 2);
        }

        // Aplicamos la formula de R cuadrado.
        return 1.0 - errorSum / totalSum;
    }

private:
    // Pesos que aprende el modelo.
    std::vector<double> weights;

    // Promedio de cada columna.
    std::vector<double> means;

    // Escala de cada columna.
    std::vector<double> scales;

    // Punto inicial de la formula.
    double bias = 0;
};
