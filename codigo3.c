#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *funcion_hilo_pesado(void *arg) {
    int id = *((int *) arg);
    printf("Hilo ejecutado: %d\n", id);   
    pthread_exit(NULL);
}

int main() {
    int num_hilos;
    
    
    printf("Ingrese el número de hilos: ");
    scanf("%d", &num_hilos);

    
    pthread_t *hilos = malloc(num_hilos * sizeof(pthread_t));
    int *ids = malloc(num_hilos * sizeof(int));

    
    for (int i = 0; i < num_hilos; i++) {
        ids[i] = i + 1; 
        pthread_create(&hilos[i], NULL, funcion_hilo_pesado, (void *) &ids[i]);
    }

   
    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
    }

  
    free(hilos);
    free(ids);

    return 0;
}