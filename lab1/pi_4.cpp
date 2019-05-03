#include <iostream>
#include <cstdio>
#include <omp.h>

using namespace std;

int num_steps = 100000000;

int main(){
    double pi = 0, step;
    step = (double)1 / num_steps;
    omp_set_num_threads(8);
#pragma omp parallel
{   
    int id = omp_get_thread_num(); 
    double sum = 0.0;
    for (int i = id; i < num_steps; i=i+8){ 
        double x = (i+0.5)*step; 
        sum += 4.0/(1.0+x*x); 
    }
    pi += sum*step; 

}
    printf("%.10lf\n", pi);
    return 0;
}