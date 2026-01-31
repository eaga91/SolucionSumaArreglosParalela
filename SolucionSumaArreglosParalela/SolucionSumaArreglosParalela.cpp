// SolucionSumaArreglosParalela.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>              // Para imprimir en consola
#include <omp.h>                 // Librería OpenMP

#define N 1000                   // Tamaño del arreglo
#define chunk 200               // Tamaño del bloque (pedazos) que se reparte
#define mostrar 10               // Cuántos valores imprimir

void imprimeArreglo(float* d);   // Prototipo de función

int main() {                     // Inicio del programa
    std::cout << "Etapa 6: Suma paralela con OpenMP + info de hilos.\n"; // Mensaje

    // 1) Mostrar info general del ambiente (antes de correr el for)
    // omp_get_num_procs(): cuántos "procesadores" lógicos detecta OpenMP (aprox. hilos disponibles)
    std::cout << "Procesadores logicos detectados (omp_get_num_procs): "
        << omp_get_num_procs() << "\n";

    // omp_get_max_threads(): cuántos hilos OpenMP usaría como máximo por defecto
    std::cout << "Max hilos OpenMP por defecto (omp_get_max_threads): "
        << omp_get_max_threads() << "\n";

    // 2) Declarar arreglos
    float a[N], b[N], c[N];      // a y b: entrada. c: resultado
    int i;                       // Variable índice

    // 3) Generación de datos para a y b
    for (i = 0; i < N; i++) {    // Recorremos todo el arreglo
        a[i] = i * 10.0f;        // Valor ejemplo para a
        b[i] = (i + 3) * 2.5f;   // Valor ejemplo para b
    }

    // 4) Definir tamaño del bloque
    int pedazos = chunk;         // pedazos = chunk 

    // 5) Bloque paralelo SOLO para imprimir cuántos hilos se están usando realmente
    // #pragma omp parallel: crea un equipo de hilos
#pragma omp parallel
    {
        // #pragma omp single: solo UN hilo imprime (para que no se repita muchas veces)
#pragma omp single
        {
            // omp_get_num_threads(): devuelve el número real de hilos en el equipo actual
            std::cout << "Hilos realmente usados en esta region paralela (omp_get_num_threads): "
                << omp_get_num_threads() << "\n\n";
        }
    }

    // 6) FOR PARALELO (la suma)
#pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)
    for (i = 0; i < N; i++) {    // OpenMP reparte estas iteraciones entre hilos
        c[i] = a[i] + b[i];      // Suma elemento a elemento
    }

    // 7) Imprimir parte de los arreglos para comprobar
    std::cout << "Primeros " << mostrar << " de a:\n";    // Título
    imprimeArreglo(a);           // Imprime a

    std::cout << "Primeros " << mostrar << " de b:\n";    // Título
    imprimeArreglo(b);           // Imprime b

    std::cout << "Primeros " << mostrar << " de c (a+b paralelo):\n"; // Título
    imprimeArreglo(c);           // Imprime c

    // 8) Verificación rápida
    bool ok = true;              // Asumimos que está bien
    for (int k = 0; k < mostrar; k++) { // Revisamos los primeros "mostrar"
        if (c[k] != a[k] + b[k]) {      // Si no coincide con a+b...
            ok = false;                 // marcamos fallo
            break;                      // salimos
        }
    }

    std::cout << "\nVerificacion rapida: " << (ok ? "OK" : "FALLO") << "\n"; // Resultado final

    return 0;                    // Fin del programa
}

// Función que imprime los primeros "mostrar" valores del arreglo
void imprimeArreglo(float* d) {
    for (int x = 0; x < mostrar; x++) { // Recorremos solo una parte
        std::cout << d[x] << " - ";     // Imprimimos el valor
    }
    std::cout << "\n";                 // Salto de línea
}


    // 
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
