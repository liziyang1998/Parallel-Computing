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
    #pragma omp for
    for (int i = 0; i < num_steps; i++){
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
//     double pi = 0.0;
//     double sum = 0.0;
//     double x = 0.0;
//     step = 1.0 / (double)num_steps;
//     size_t start, end;
//     start = clock();

//     omp_set_num_threads(NUM_THREADS); // 设置 2 线程
// #pragma omp parallel private(x, sum)  // 该子句表示 x,sum 变量对于每个线程是私有的
//     {
//         int id;
//         id = omp_get_thread_num();
//         for (i = id, sum = 0.0; i < num_steps; i = i + NUM_THREADS)
//         {
//             x = (i + 0.5) * step;
//             sum += 4.0 / (1.0 + x * x);
//         }
//         #pragma omp critical // 指定代码段在同一时刻只能由一个线程进行执行
//         pi += sum * step;
//     }
//     printf("%lf\n", pi);
//     end = clock();
//     printf("time = %lf\n", double(end - start) / CLOCKS_PER_SEC);
// }
// // 共 2 个线程参加计算,其中线程 0 进行迭代步 0,2,4,... 线程 1 进行迭代步 1,3,5,.... 当被指定为 critical 的代码段
// //被 0 线程执行时, 1 线程的执行也到达该代码段, 则它将被阻塞知道 0 线程退出临界区。 国家高性能计算中心(合肥) 正在