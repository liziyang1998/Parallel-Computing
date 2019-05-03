#include <iostream>
#include <cstdio>
#include <omp.h>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
#define NUM_THREADS 8
#define INF 999999999
#define MAXN 10000005
int n;
int number[MAXN];
fstream fileName;

int fileIO(string file){
    fileName.open(file);
    if (!fileName.is_open()){
        printf("File Read Fail\n");
        return -1;
    }
    fileName >> n;
    for (int i = 0; i < n; i++)
        fileName >> number[i];
    for (int i = n; i < (n / NUM_THREADS  + 1) * NUM_THREADS; i++)
        number[i] = INF;
    fileName.close();
    return 0;
}

int PSRS(string file){
    fileName.open(file);
    if (!fileName.is_open()){
        printf("File Read Fail\n");
        return -1;
    }
    int blockSize = n / NUM_THREADS + 1;//块大小
    int sampling[NUM_THREADS * NUM_THREADS + 1] = {0};//正则采样
    int pivot[NUM_THREADS] = {0};//主元
    vector<int>pivot_array[NUM_THREADS];
    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
{
    int id = omp_get_thread_num();
    sort(number + id * blockSize, number + (id + 1) * blockSize);
    #pragma omp critical
    for (int i = 0; i < NUM_THREADS; i++){
        sampling[++sampling[0]] = number[id * blockSize + i * blockSize / NUM_THREADS];
    }
    #pragma omp barrier
    #pragma omp master
    {
        sort(sampling + 1, sampling + sampling[0] + 1);
        for (int i = 0; i < NUM_THREADS - 1; i++)
            pivot[i] = sampling[(i + 1) * NUM_THREADS + 1];
    }
    #pragma omp barrier
    #pragma omp critical
    for (int j = 0; j < blockSize; j++){
        for (int i = 0; i < NUM_THREADS; i++){
            if (number[id * blockSize + j] < pivot[i]){
                pivot_array[i].push_back(number[id * blockSize + j]);
                break;
            }
            else if (i == NUM_THREADS - 1){
                pivot_array[i].push_back(number[id * blockSize + j]);
            }
        }
    }

    #pragma omp barrier
    sort(pivot_array[id].begin(), pivot_array[id].end());
    #pragma omp master
    {
        vector<int>::iterator It;
        int cnt = 0;
        for (int i = 0; i < NUM_THREADS; i++){
            for (It = pivot_array[i].begin(); It != pivot_array[i].end(); It++){
                cnt++;
                if (cnt > n)break;
                fileName << (*It) << " ";
            }
        }
        fileName << endl;
    }
}
    fileName.close();
}

int main(int argc, char * argv[]){
    if (argc <= 2){
        printf("Paraments error\n");
        return 0;
    }
    if (fileIO(argv[1]) == -1){
        return 0;
    }
    // sort(number, number + n);
    if (PSRS(argv[2]) == -1){
        return 0;
    }
}