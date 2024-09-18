#include <stdio.h>      // Biblioteca estándar para entrada/salida
#include <pthread.h>    // Biblioteca para usar hilos en C

// Estructura para almacenar el número y su factorial
typedef struct {
    int numero;                          // Número cuyo factorial se calculará
    unsigned long long factorial;        // Resultado del cálculo del factorial
} DatosHilo;

// Función que será ejecutada por cada hilo para calcular el factorial de un número
void *calcular_factorial(void *arg) {
    // Se recibe un puntero genérico y se convierte a un puntero de tipo DatosHilo
    DatosHilo *datos = (DatosHilo *) arg;
    int num = datos->numero;             // Extrae el número de la estructura para trabajar con él
    datos->factorial = 1;                // Inicializa el resultado del factorial como 1

    // Bucle para calcular el factorial del número
    for (int i = 1; i <= num; i++) {
        datos->factorial *= i;           // Multiplica el resultado acumulado por el índice actual
    }

    // Imprime el resultado parcial del cálculo desde el hilo
    printf("El factorial de %d es %llu\n", datos->numero, datos->factorial);

    pthread_exit(NULL);                  // Finaliza el hilo cuando termina su tarea
}

int main() {
    pthread_t hilos[3];                  // Array para almacenar los identificadores de 3 hilos
    DatosHilo datos[3] = {{4, 0}, {9, 0}, {13, 0}};  // Array con los números y sus factoriales inicializados a 0

    // Bucle para crear los hilos y asignarles la tarea de calcular el factorial
    for (int i = 0; i < 3; i++) {
        // Crea un hilo que ejecutará la función 'calcular_factorial'
        // Se pasa la dirección del elemento correspondiente del array 'datos' como argumento
        pthread_create(&hilos[i], NULL, calcular_factorial, (void *) &datos[i]);
    }

    // Bucle para esperar a que cada hilo termine antes de continuar
    for (int i = 0; i < 3; i++) {
        // Espera a que el hilo con el identificador correspondiente termine su ejecución
        pthread_join(hilos[i], NULL);
    }

    return 0;  // Finaliza el programa
}
