#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int thread_id;
    char* message;
} ThreadArgs;

void* threadFunction(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    printf("Hilo %d: %s\n", thread_args->thread_id, thread_args->message);
    pthread_exit(NULL);
}

int main() {
    const int NUM_HILOS = 4;
    pthread_t threads[NUM_HILOS];
    ThreadArgs args[NUM_HILOS];

    // Inicializar los argumentos para cada hilo
    for (int i = 0; i < NUM_HILOS; i++) {
        args[i].thread_id = i + 1;
        args[i].message = "Hola desde un hilo!";
    }

    // Crear los hilos
    for (int i = 0; i < NUM_HILOS; i++) {
        if (pthread_create(&threads[i], NULL, threadFunction, (void*)&args[i]) != 0) {
            perror("Error al crear el hilo");
            exit(EXIT_FAILURE);
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_HILOS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error al unir el hilo");
            exit(EXIT_FAILURE);
        }
    }

    printf("Hilo principal: Todos los hilos han terminado su ejecución.\n");
    return 0;
}