#include <iostream>
#include <cstdio>
#include <omp.h>

using namespace std;

int num_steps = 100000000;

int main(){
    double sum[8] = {0.0}, pi = 0, step;
    step = (double)1 / num_steps;
    omp_set_num_threads(8);
#pragma omp parallel
{
    int id = omp_get_thread_num();
    for (int i = id; i < num_steps; i=i+8){
        double x = (i + 0.5) * step;
        sum[id] += 4.0 / (1.0 + x * x);
    }
}
    for (int i = 0; i < 8; i++)
        pi += step * sum[i];
    printf("%.8lf\n", pi);
    return 0;
}