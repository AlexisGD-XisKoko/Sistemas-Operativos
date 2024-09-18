#include <stdio.h>
#include <pthread.h>

// Función que será ejecutada por cada hilo
void* calcularCuadrado(void* arg) {
    int num = *(int*)arg;   // Convertimos el argumento a un entero
    int cuadrado = num * num;
    printf("Hilo: El cuadrado de %d es %d\n", num, cuadrado);
    return NULL;            // Finalizamos el hilo
}

int main() {
    pthread_t hilos[3];     // Creamos un array para almacenar 3 identificadores de hilos
    int numeros[3] = {2, 4, 6};  // Array con números a los que se les calculará el cuadrado

    // Creamos 3 hilos, cada uno ejecutando la función calcularCuadrado
    for (int i = 0; i < 3; ++i) {
        pthread_create(&hilos[i], NULL, calcularCuadrado, (void*)&numeros[i]);
    }

    // Esperamos a que los 3 hilos terminen su ejecución
    for (int i = 0; i < 3; ++i) {
        pthread_join(hilos[i], NULL);
    }

    printf("Todos los hilos han terminado :)\n");

    return 0;
}
