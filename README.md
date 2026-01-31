# SolucionSumaArreglosParalela (OpenMP) Enrique Garcia 

Este proyecto implementa la suma elemento a elemento de dos arreglos usando programación paralela con **OpenMP** en **C++**.

## Objetivo
Demostrar cómo un ciclo `for` puede paralelizarse cuando cada iteración es independiente, calculando un tercer arreglo `c` tal que:

- `c[i] = a[i] + b[i]`

Además, el programa imprime información del ambiente de ejecución (procesadores lógicos detectados y número de hilos usados por OpenMP) y muestra una parte de los arreglos para validar el resultado.


## Parámetros principales
En el código se usan las siguientes constantes:

- `N`: tamaño de los arreglos
- `chunk`: tamaño del bloque que se asigna a cada hilo con `schedule(static, chunk)`
- `mostrar`: cantidad de elementos a imprimir (para no saturar la consola)

Ejemplo:
- `N = 1000`
- `chunk = 100` (en una segunda ejecución se puede cambiar a 50 o 200)
- `mostrar = 10`

## ¿Qué hace el programa?
1. Genera dos arreglos `a` y `b` con valores de prueba.
2. Ejecuta un `for` paralelo con OpenMP para calcular `c[i] = a[i] + b[i]`.
3. Imprime los primeros `mostrar` elementos de `a`, `b` y `c`.
4. Realiza una verificación rápida para confirmar que `c` corresponde a la suma de `a` y `b` en los primeros elementos.


## Autor
-Enrique Garcia Arias
