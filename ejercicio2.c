#include <omp.h>
#include <stdio.h>

#define N 100000;

int main(){
    int n = N;
    int sum = 0; 
    double initTime = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for(int i=1; i<=n ;i++){
        printf("Hilo %d sumando %d\n", omp_get_thread_num(), i);
        sum += i;
    }
    double endTime = omp_get_wtime();
    double time = endTime - initTime;
    printf("La suma es %d y el tiempo es %d\n", sum, time);

}