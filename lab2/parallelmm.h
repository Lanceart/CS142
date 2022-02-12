#include<thread>
#include<cilk/cilk.h>
#include<cilk/cilk_api.h>

void parallel_mm(int n, double* A, double* B, double* C, int size, int threshold) {



        cilk_for(int i = 0; i < n; i++){
                for (int k = 0; k < n; k++){
                        for (int j = 0; j < n; j++) {
                                C[i * size + j] += A[i * size + k] * B[k * size + j];
                        }
                }
        }
}
