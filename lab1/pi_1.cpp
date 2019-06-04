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
// #include <cstdio>
// #include <ctime>
// #include <omp.h>
// using namespace std;

// static long num_steps = 100000000;
// double step;
// #define NUM_THREADS 4
// int main(){
//     int i;
//     double x, pi, sum[NUM_THREADS];
//     step = 1.0 / (double)num_steps;
//     size_t start, end;
//     start = clock();

//     omp_set_num_threads(NUM_THREADS); // 设置 2 线程
// #pragma omp parallel private(i)       // 并行域开始,每个线程 (OpenMP0 和 1) 都会执行该代码
//     {
//         double x;
//         int id;
//         id = omp_get_thread_num();
//         for (i = id, sum[id] = 0.0; i < num_steps; i = i + NUM_THREADS)
//         {
//             x = (i + 0.5) * step;
//             sum[id] += 4.0 / (1.0 + x * x);
//         }
//     }
//     for (i = 0, pi = 0.0; i < NUM_THREADS; i++)
//         pi += sum[i] * step;
//     printf("%lf\n", pi);
//     end = clock();
//     printf("time = %lf\n", double(end - start) / CLOCKS_PER_SEC);
// }
// // 共 2 个线程参加计算,其中线程 0 进行迭代步 0,2,4,... 线程 1 进行迭代步 1,3,5,....