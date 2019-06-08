#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void mm_omp(const double *A, const double *B, double *C, int n);

int main(int argc, const char **argv) {
    if (argc != 4) {
        printf("Run me with %s <square_matrix_size> <max_threads> <n_executions_to_avg>\n", argv[0]);
        return -1;
    }

    int i, t, n, max_threads, execs;
    double *A, *B, *C, start, delta;

    n = atoi(argv[1]);
    max_threads = atoi(argv[2]);
    execs = atoi(argv[3]);

    A = (double *) malloc(sizeof(double) * n * n);
    B = (double *) malloc(sizeof(double) * n * n);
    C = (double *) malloc(sizeof(double) * n * n);
    for (i = 0; i < n * n; i++) {
        A[i] = rand() / RAND_MAX;
        B[i] = rand() / RAND_MAX;
    }

    for (t = 1; t <= max_threads; t++) {

        double mean_time = 0;
        for (i = 0; i < execs; ++i) {
            omp_set_num_threads(t);

            start = omp_get_wtime();
            mm_omp(A, B, C, n);
            delta = omp_get_wtime() - start;

            mean_time += delta;
        }
        mean_time /= execs;

        printf("Running on %d threads: ", t);
        printf("MM computed in %.4g seconds (on average of %d executions) \n", mean_time, execs);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}

void mm_omp(const double *A, const double *B, double *C, int n) {
#pragma omp parallel for
    for (int i = 0; i < n; i++) {

        //#pragma omp parallel for shared(A,B,C)
        for (int j = 0; j < n; j++) {

            double dot = 0;
            //#pragma omp parallel for reduction(+:dot) shared(A,B,C)
            for (int k = 0; k < n; k++) {
                dot += A[i * n + k] * B[k * n + j];
            }

            C[i * n + j] = dot;
        }
    }
}
