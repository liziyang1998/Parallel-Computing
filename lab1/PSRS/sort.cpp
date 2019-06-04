/* Merge sort in C++ */
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;
fstream fileName;

void Merge(int *A, int *L, int leftCount, int *R, int rightCount)
{
    int i, j, k;

    i = 0;
    j = 0;
    k = 0;

    while (i < leftCount && j < rightCount)
    {
        if (L[i] < R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }
    while (i < leftCount)
        A[k++] = L[i++];
    while (j < rightCount)
        A[k++] = R[j++];
}

// Recursive function to sort an array of integers.
void MergeSort(int *A, int n)
{
    int mid, i, *L, *R;
    if (n < 2)
        return; // base condition. If the array has less than two element, do nothing.

    mid = n / 2; // find the mid index.

    // create left and right subarrays
    // mid elements (from index 0 till mid-1) should be part of left sub-array
    // and (n-mid) elements (from mid to n-1) will be part of right sub-array
    L = new int[mid];
    R = new int[n - mid];

    for (i = 0; i < mid; i++)
        L[i] = A[i]; // creating left subarray
    for (i = mid; i < n; i++)
        R[i - mid] = A[i]; // creating right subarray

    MergeSort(L, mid);            // sorting the left subarray
    MergeSort(R, n - mid);        // sorting the right subarray
    Merge(A, L, mid, R, n - mid); // Merging L and R into A as sorted list.
    // the delete operations is very important
    delete[] R;
    delete[] L;
}

const int MAXN = 10000005;
int A[MAXN];

int main(int argc, char * argv[]){
    /* Code to test the MergeSort function. */

    int i, numberOfElements;
    size_t start, end;
    start = clock();

    fileName.open("1.txt");
    fileName >> numberOfElements;

    for (int i = 0; i < numberOfElements; i++)
        fileName >> A[i];
    fileName.close();

    MergeSort(A, numberOfElements);

    fileName.open("ans.txt");
    for (i = 0; i < numberOfElements; i++)
        fileName << A[i] << " ";
    fileName << endl;
    fileName.close();

    end = clock();
    printf("time = %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
