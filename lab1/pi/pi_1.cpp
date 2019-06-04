#include <cstdio>
#include <omp.h>
#include <iostream>
#include <ctime>

using namespace std;
const int NUM_THREADS = 16;
int num_steps = 100000000;

int main(){
    double pi, sum = 0.0, x, step;
    step = 1.0 / (double)num_steps;
    double start, end;
    start = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < num_steps; i++){
        double x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    printf("%.10lf\n", pi);
    end = omp_get_wtime();
    printf("time = %lf\n", double(end - start));
    return 0;
}