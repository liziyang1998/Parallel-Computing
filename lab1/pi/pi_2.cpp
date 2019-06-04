#include <iostream>
#include <cstdio>
#include <omp.h>
#include <ctime>

using namespace std;
const int NUM_THREADS = 16;
int num_steps = 100000000;

int main(){
    double sum[NUM_THREADS] = {0.0}, pi = 0, step;
    step = (double)1 / num_steps;
    double start, end;
    start = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
{
    int id = omp_get_thread_num();
    for (int i = id; i < num_steps; i=i+NUM_THREADS){
        double x = (i + 0.5) * step;
        sum[id] += 4.0 / (1.0 + x * x);
    }
}
    for (int i = 0; i < NUM_THREADS; i++)
        pi += step * sum[i];
    printf("%.8lf\n", pi);
    end = omp_get_wtime();
    printf("time = %lf\n", double(end - start));
    return 0;
}