
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <cmath>
#define N 131072
#define MIN_SIZE 4

long cutoff = 0;
long count = 0;
long tasks = 0 ;

void count_key(long Nlen, long *a, long key) {
    int thread_id = omp_get_thread_num(); // Obtener el ID del hilo actual
    for (long i = 0; i < Nlen; i++) {
        if (a[i] == key) {
            #pragma omp atomic
            count++;
            printf("Hilo %d procesando a[%ld] = %ld, cuenta = %ld\n", thread_id, i, a[i], count);
        }
    }
}

void rec_count_key(long n, long *a, long key, int depth) {
    int thread_id = omp_get_thread_num(); // Obtener el ID del hilo actual
    // printf("Hilo %d - rec_count_key para n=%ld, depth=%d\n", thread_id, n, depth);

    if (n > MIN_SIZE) {
        long n2 = n / 2;
        if (depth == cutoff) {
            // printf("Hilo %d - Creando tareas paralelas en el cut-off depth=%d\n", thread_id, depth);
            tasks++;
            #pragma omp task
            {   
                rec_count_key(n2, a, key, depth + 1);
                rec_count_key(n - n2, a + n2, key, depth + 1);
            }
        } else {
            rec_count_key(n2, a, key, depth + 1);
            rec_count_key(n - n2, a + n2, key, depth + 1);
        }
    } else {
        if (depth <= cutoff) {
            tasks++;
            #pragma omp task
            count_key(n, a, key);
        } else {
            count_key(n, a, key);
        }
    }
}

int main() {
    srand(time(NULL));
    long a[N], key = 42;
    
    for (long i = 0; i < N; i++) {
        a[i] = rand() % N;
    }
    
    // Inserción manual del valor 'key'
    a[N % 43] = key; 
    a[N % 73] = key; 
    a[N % 3] = key;
    
    #pragma omp parallel
    {   
        cutoff =  log(omp_get_num_threads()) / log(2) ; // Calculamos el cut-off en base a cantidad de hilos y en ln(2) debido a que se divide en 2
        #pragma omp single
        rec_count_key(N, a, key, 0);  // Comenzamos con una profundidad de 0
    }

    printf("Número de veces que 'key' aparece: %ld\n", count);
    printf("Número de tareas generadas: %ld\n", tasks);
    printf("Cutoff: %ld\n", cutoff);
    return 0;
}
