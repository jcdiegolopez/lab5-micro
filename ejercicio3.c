#include <omp.h>
#include <stdio.h>

int fibonacci(int n1 , int n2, int n){
    if(n = 0){
        return 
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

            }
            #pragma omp section
            {
                printf("Hilo %d sección 3\n", omp_get_thread_num());
            }
        }
    }
}
