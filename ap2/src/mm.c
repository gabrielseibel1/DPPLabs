#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_THREADS 4

void mm_omp(const double *A, const double *B, double *C, int n) {
    int i, j, k;

    #pragma omp parallel for shared(A,B,C)
    for (i = 0; i < n; i++) {

        //#pragma omp parallel for shared(A,B,C)
        for (j = 0; j < n; j++) {

            double dot = 0;
            //#pragma omp parallel for reduction(+:dot) shared(A,B,C)
            for (k = 0; k < n; k++) {
                dot += A[i * n + k] * B[k * n + j];
            }

            C[i * n + j] = dot;
        }
    }
}

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    int i, j, n;
    double *A, *B, *C, start, delta;

    n = atoi(argv[1]);

    A = (double *) malloc(sizeof(double) * n * n);
    B = (double *) malloc(sizeof(double) * n * n);
    C = (double *) malloc(sizeof(double) * n * n);
    for (i = 0; i < n * n; i++) {
        A[i] = rand() / RAND_MAX;
        B[i] = rand() / RAND_MAX;
    }

    for (j = 1; j <= MAX_THREADS; j++) {
        printf(" running on %d threads: ", j);
        omp_set_num_threads(j);

        start = omp_get_wtime();
        mm_omp(A, B, C, n);
        delta = omp_get_wtime() - start;

        printf("MM computed in %.4g seconds\n", delta);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}