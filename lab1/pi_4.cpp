#include <iostream>
#include <cstdio>
#include <omp.h>
#include <ctime>

using namespace std;
const int NUM_THREADS = 16;
int num_steps = 100000000;

int main(){
    double pi = 0, step;
    step = (double)1 / num_steps;
    double start, end;
    start = omp_get_wtime();

    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
{   
    int id = omp_get_thread_num(); 
    double sum = 0.0;
    for (int i = id; i < num_steps; i=i+NUM_THREADS){ 
        double x = (i+0.5)*step; 
        sum += 4.0/(1.0+x*x); 
    }
    pi += sum*step; 

}
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
// #pragma omp parallel for reduction( + : sum) private(x)
//     // 每个线程保留一份私有拷贝 sum , x 为线程私有,最后对线程中所以 sum 进行 + 规约, 并更新 sum 的全局值 for (i = 1; i <= num_steps; i++)

//     for (i = 1; i <= num_steps; i++)
//     {
//         x = (i - 0.5) * step;
//         sum += 4.0 / (1.0 + x * x);
//     }
//     pi = sum * step;
//     printf( "%lf\n", pi);
//     end = clock();
//     printf("time = %lf\n", double(end - start) / CLOCKS_PER_SEC);
// }
// // 共 2 个线程参加计算,其中线程 0 进行迭代步 0~49999 ,线程 1 进行迭代步 50000~99999.