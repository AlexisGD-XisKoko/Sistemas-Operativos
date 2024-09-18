#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <regex.h>

#define NUM_THREADS 8    // Número de hilos que se utilizarán

// Estructura para pasar datos a los hilos
typedef struct {
    char *text_chunk;  // Fragmento de texto que procesa el hilo
    const char *word;  // Palabra que se busca en el fragmento
    int count;         // Conteo de ocurrencias de la palabra
    size_t size;       // Tamaño del fragmento de texto
} ThreadData;

// Función para contar ocurrencias de una palabra en una cadena
int contar_ocurrencias(const char *texto, const char *palabra) {
    regex_t regex;  // Estructura para la expresión regular
    regmatch_t matches[1];  // Resultados de la búsqueda de coincidencias
    int count = 0;

    // Crear una expresión regular que busque la palabra exacta
    char pattern[256];
    snprintf(pattern, sizeof(pattern), "\\b%s\\b", palabra);  // \b es un delimitador de palabra
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        perror("Error al compilar la expresión regular");
        return -1;
    }

    const char *ptr = texto;
    // Buscar coincidencias en el texto
    while (regexec(&regex, ptr, 1, matches, 0) == 0) {
        count++;
        ptr += matches[0].rm_eo;  // Mover el puntero después de la coincidencia
    }

    regfree(&regex);  // Liberar la memoria de la expresión regular
    return count;
}

// Función que será ejecutada por cada hilo
void *procesar_chunk(void *arg) {
    ThreadData *data = (ThreadData *)arg;  // Convertir el argumento a la estructura ThreadData
    data->count = contar_ocurrencias(data->text_chunk, data->word);  // Contar ocurrencias en el fragmento
    pthread_exit(NULL);  // Terminar el hilo
}

int main() {
    FILE *file = fopen("archivo_grande.txt", "r");  // Abrir el archivo en modo lectura
    if (file == NULL) {
        perror("No se puede abrir el archivo");
        return EXIT_FAILURE;
    }

    // Obtener el tamaño del archivo
    fseek(file, 0, SEEK_END);  // Mover el puntero al final del archivo
    long file_size = ftell(file);  // Obtener la posición del puntero (tamaño del archivo)
    fseek(file, 0, SEEK_SET);  // Volver al principio del archivo

    pthread_t threads[NUM_THREADS];  // Array para almacenar los identificadores de los hilos
    ThreadData thread_data[NUM_THREADS];  // Array para almacenar los datos de cada hilo
    int total_count = 0;  // Contador total de ocurrencias de la palabra
    long chunk_size = file_size / NUM_THREADS;  // Tamaño de cada bloque para los hilos
    long last_chunk_size = file_size - (chunk_size * (NUM_THREADS - 1));  // Tamaño del último bloque

    // Dividir el archivo en bloques y asignar a los hilos
    for (int i = 0; i < NUM_THREADS; i++) {
        long size = (i == NUM_THREADS - 1) ? last_chunk_size : chunk_size;  // Tamaño del bloque actual
        thread_data[i].text_chunk = malloc(size + 1);  // Asignar memoria para el bloque
        if (thread_data[i].text_chunk == NULL) {
            perror("No se pudo asignar memoria");
            return EXIT_FAILURE;
        }
        fread(thread_data[i].text_chunk, 1, size, file);  // Leer el bloque del archivo
        thread_data[i].text_chunk[size] = '\0';  // Asegurar que el texto esté terminado en null
        thread_data[i].word = "just";  // Palabra a buscar en el fragmento
        thread_data[i].size = size;  // Tamaño del fragmento
        pthread_create(&threads[i], NULL, procesar_chunk, (void *)&thread_data[i]);  // Crear el hilo
    }

    // Esperar la finalización de los hilos y sumar los conteos
    for (int j = 0; j < NUM_THREADS; j++) {
        pthread_join(threads[j], NULL);  // Esperar a que el hilo termine
        total_count += thread_data[j].count;  // Sumar el conteo del hilo al total
        free(thread_data[j].text_chunk);  // Liberar la memoria del fragmento
    }

    fclose(file);  // Cerrar el archivo

    printf("La palabra 'just' aparece %d veces en el archivo.\n", total_count);  // Imprimir el resultado

    return EXIT_SUCCESS;  // Terminar el programa
}
