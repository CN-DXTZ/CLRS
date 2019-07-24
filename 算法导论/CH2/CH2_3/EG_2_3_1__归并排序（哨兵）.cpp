// 归并排序（哨兵）
#include <iostream>
#include <climits>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void merge(int A[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1 + 1] = {}, R[n2 + 1] = {};
    memcpy(L, (A + p), sizeof(A[0]) * n1);
    memcpy(R, (A + q + 1), sizeof(A[0]) * n2);
    L[n1] = R[n2] = INT32_MAX;

    for (int k = p, i = 0, j = 0; k <= r; k++)
    {
        if (L[i] <= R[j])
            A[k] = L[i++];
        else
            A[k] = R[j++];
    }
}

void merge_sort(int A[], int p, int r)
{
    if (p < r) // 
    {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main()
{
    int A[] = {5, 2, 4, 7, 1, 3, 2, 6};
    int length = GET_LEN(A);

    merge_sort(A, 0, length - 1);
    for (int i = 0; i < length; i++)
        cout << A[i] << endl;

    return 0;
}