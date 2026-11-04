# Práctica 2 POO

Regresión lineal en C++ con datos de ventas de helados y notas de estudiantes.

La primera mitad termina al entrenar y probar la regresión simple con el CSV de helados. La segunda cubre el caso multivariable, la evaluación completa, el análisis de memoria y el informe.

## Ejecutar desde la raíz del repositorio

Con Clang y PowerShell:

~~~powershell
New-Item -ItemType Directory -Force build | Out-Null
clang++ -std=c++17 src/main.cpp -o build/practica2.exe
./build/practica2.exe data/Ice_cream_selling_data.csv
clang++ -std=c++17 tests/regression.cpp -o build/regression-test.exe
./build/regression-test.exe
~~~

El programa entrena con 39 observaciones y reserva 10 para comparar las ventas reales y las predicciones. Con el CSV incluido, la pendiente es aproximadamente −0.40641 y el intercepto es 16.1298.

La prueba usa cuatro puntos de la recta y = −2x + 3. Comprueba los dos coeficientes y que para x = 4 el modelo prediga −5.
