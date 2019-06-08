#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long steps = 1000000000;

double pi_omp();

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        printf("Run me with <exec> <max_threads>");
        return -1;
    }

    int t, max_threads;
    double pi, start, delta;

    max_threads = atoi(argv[1]);

    for (t = 1; t <= max_threads; t++) {
        printf("Running on %d threads: ", t);
        omp_set_num_threads(t);

        start = omp_get_wtime();
        pi = pi_omp();
        delta = omp_get_wtime() - start;

        printf("PI = %.16g computed in %.4g seconds\n", pi, delta);
    }
}

double pi_omp() {
    int i;
    double pi, x, sum = 0.0, step = 1.0 / (double) steps;

    #pragma omp parallel for reduction(+:sum) private(x)
    for (i = 0; i < steps; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    return pi;
}