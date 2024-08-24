#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n){
    if(n <= 1){
        return n;
    }else{
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

int main(){
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
            int n = 100;
            int factorial = 1;
            for(int i = 1; i <= n; i++) {
                factorial *= i;
            }
            printf("Hilo %d ejecutando seccion 1 factorial, con n %d y resultado %d\n", omp_get_thread_num(), n, factorial);
            }
            #pragma omp section
            {
                int n = 10;
                int fibo = fibonacci(n);
                printf("Hilo %d ejecutando seccion 2 fibonacci, con n %d y resultado %d\n", omp_get_thread_num(), n, fibo);
            }

            
            #pragma omp section
            {
                int n = 100;
                int array[100] = {};
                for(int i = 0; i < n; i++){
                    array[i] = rand() % 10000;
                }
                int max = 0;
                for(int i = 0; i < n; i++){
                    if(array[i] > max){
                        max = array[i];
                    }
                }
                printf("Hilo %d ejecutando seccion 3 maximo en array, con maximo %d\n", omp_get_thread_num(), max);
            }

        }
    }
}
