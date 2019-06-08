#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long steps = 1000000000;

double pi_omp();

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        printf("Run me with %s <max_threads> <n_executions_to_avg>\n", argv[0]);
        return -1;
    }

    int i, t, max_threads, execs;
    double start, delta;

    max_threads = atoi(argv[1]);
    execs = atoi(argv[2]);

    for (t = 1; t <= max_threads; t++) {

        double mean_time = 0, pi = 0;
        for (i = 0; i < execs; ++i) {
            omp_set_num_threads(t);

            start = omp_get_wtime();
            pi += pi_omp();
            delta = omp_get_wtime() - start;

            mean_time += delta;
        }
        mean_time /= execs;
        pi /= execs;

        printf("Running on %d threads: ", t);
        printf("PI = %.16g computed in %.4g seconds (on average of %d executions) \n", pi, mean_time, execs);
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