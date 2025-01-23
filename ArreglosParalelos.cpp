// ArreglosParalelos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.


// iostream - Librería que permite trabajar con operaciones de entrada y salida de la consola
#include <iostream>
// omp - Librería que permite ejecutar programación paralela empleando mútiples hilos
#include <omp.h>
#include <random> // Librería para generar números aleatorios

// Declaración de variables
#define N 1000 // Tamaño de los arreglos
#define chunk 100 // Variable empleada para dividir las iteraciones en bloques 
#define mostrar 10 // Listado máximo de elementos a desplegar en pantalla

void imprimeArreglo(float *d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    // Inicialización del generador de números aleatorios para el índice
    std::random_device rd;  // Semilla no determinista
    std::mt19937 gen(rd()); // Generador de Mersenne Twister
    std::uniform_int_distribution<> distrib(0, 1000); // Distribución aleatoria para índices


    for (i = 0; i < N; i++) {
        int random_index = distrib(gen);  // Genera un índice aleatorio
        a[i] = random_index * 10;
        b[i] = (random_index + 3) * 3.7;
    }
    
    int pedazos = chunk;

    // #pragma omp parallel for - Permite paralelizar los bucles for dividiendo las iteraciones entre varios hilos
    //shared - Permite especificar las variables que seran compartidas entre los hilos
    // private(i) - Permite indicar que la variable será privada para cada hilo, lo permite llevar a cabo la iteración
    // schedule static - Controla como se distribuyen las iteraciones del bucle entre los hilos
    #pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)

    // Se realiza la suma de los arreglos
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    // Se imprimen resultados en la Consola
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

}

// Los datos a imprimir de los arreglos son separados por guiones y acotados a máximo 10 valores en pantalla
void imprimeArreglo(float *d) {
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}
