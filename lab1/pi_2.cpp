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
// #include <cstdio>
// #include <ctime>
// #include <omp.h>
// using namespace std;

// static long num_steps = 100000000;
// double step;
// #define NUM_THREADS 4
// int main()
// {
//     int i;
//     double x, pi, sum[NUM_THREADS];
//     step = 1.0 / (double)num_steps;
//     size_t start, end;
//     start = clock();

//     omp_set_num_threads(NUM_THREADS); // 设置 2 线程
// #pragma omp parallel                        // 并行域开始,每个线程 (OpenMP0 和 1) 都会执行该代码
//     {
//         double x;
//         int id;
//         id = omp_get_thread_num();
//         sum[id] = 0;
//         #pragma omp for // 未指定 chunk ,迭代平均分配给各线程( 0 和 1 ),连续划分
//         for (i = 0; i < num_steps; i++)
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

// } // 共 2 个线程参加计算,其中线程 0 进行迭代步 0~49999 ,线程 1 进行迭代步 50000~99999.