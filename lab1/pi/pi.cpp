#include <cstdio>
#include <ctime>
#include <omp.h>
using namespace std;

const long long num_steps = 100000000; // 越大值越精确
double step;
int main(){
    double x, pi, sum = 0.0;
    step = 1.0 / (double)num_steps;
    size_t start, end;
    start = clock();

    for (int i = 1; i <= num_steps; i++)
    {
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    printf( "%lf\n", pi);
    end = clock();
    printf("time = %lf\n", double(end - start) / CLOCKS_PER_SEC);
}