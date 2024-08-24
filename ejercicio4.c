#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int x = 0;
    int y = 0;

    #pragma omp parallel for shared(x) private(y)
    for(int i = 0; i < 100; i++){
        
        x++;
        y++;
        printf("Hilo %d, x: %d, y: %d\n", omp_get_thread_num(), x, y);
    }
    printf("Finalizado Hilo %d, x: %d, y: %d\n", omp_get_thread_num(), x, y);
    return 0;
}