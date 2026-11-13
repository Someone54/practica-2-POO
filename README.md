# Práctica 2 POO

Regresión lineal en C++ con datos de ventas de helados y notas de estudiantes.

El proyecto incluye una regresión lineal simple, una regresión lineal múltiple, un análisis de memoria y una prueba con resultados conocidos. Los cálculos fueron desarrollados directamente en C++ sin utilizar librerías externas de regresión o procesamiento estadístico.

## Archivos principales

- `src/LinearRegression.hpp`: contiene la clase de regresión lineal.
- `src/NumericCsv.hpp`: lee y valida los archivos CSV.
- `src/main.cpp`: ejecuta el modelo de ventas de helados.
- `src/studentScoresMain.cpp`: ejecuta el modelo de notas de estudiantes.
- `src/memoryAnalysis.cpp`: muestra las direcciones y tamaños de los objetos.
- `tests/regression.cpp`: comprueba la regresión simple con resultados conocidos.

## Requisitos

Para compilar el proyecto se necesita:

- CMake 3.16 o una versión posterior.
- Un compilador compatible con C++17.
- En Windows, Visual Studio Build Tools con las herramientas de C++ y el SDK de Windows.

## Compilar con CMake

Los comandos deben ejecutarse desde la raíz del repositorio.

En PowerShell:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

Con el generador de Visual Studio, los programas se crean dentro de:

```text
build\Release
```

## Ejecutar la regresión de helados

```powershell
.\build\Release\practica2.exe .\data\Ice_cream_selling_data.csv
```

Este programa utiliza 39 registros para entrenamiento y 10 para prueba. Muestra la pendiente, el bias y las comparaciones entre las ventas reales y las predicciones.

## Ejecutar la regresión de estudiantes

```powershell
.\build\Release\studentScores.exe .\data\student_exam_scores.csv
```

Este programa utiliza 160 registros para entrenamiento y 40 para prueba. Muestra los cuatro pesos, el bias, las notas reales, las predicciones y el resultado de R cuadrado.

Con los datos incluidos, el resultado esperado de R cuadrado es aproximadamente:

```text
0.8483
```

## Ejecutar el análisis de memoria

```powershell
.\build\Release\memoryAnalysis.exe
```

Este programa muestra:

- las direcciones de un objeto global, uno local y uno dinámico;
- el tamaño de cada objeto;
- el tamaño de un puntero;
- la dirección de un vector dinámico;
- el espacio aproximado usado por cinco objetos `LinearRegression`.

Las direcciones pueden cambiar en cada ejecución y pueden ser diferentes en otros computadores.

## Ejecutar la prueba de regresión

```powershell
.\build\Release\regressionTest.exe
```

La prueba utiliza datos con resultados conocidos. Comprueba que el modelo obtenga:

- un peso de `-2`;
- un bias de `3`;
- una predicción de `-5` para una entrada de `4`.

Si todos los resultados son correctos, muestra:

```text
Prueba correcta
```

## Conjuntos de datos

El proyecto utiliza los siguientes archivos:

```text
data/Ice_cream_selling_data.csv
data/student_exam_scores.csv
```

Los programas deben ejecutarse desde la raíz del repositorio para que puedan encontrar correctamente estos archivos.
