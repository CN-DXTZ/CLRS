#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

/*** 参见EG_2_3_1__归并排序（哨兵）.cpp ***/
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
/*** 参见EG_2_3_1__归并排序（哨兵）.cpp ***/

bool two_sum(int A[], int length, int v)
{
    merge_sort(A, 0, length - 1);
    int i = 0;
    int j = length - 1;
    while (i <= j)
    {
        int sum = A[i] + A[j];
        if (sum == v)
            return true;
        else if (sum < v)
            i++;
        else
            j--;
    }
    return false;
}

int main()
{
    int A[] = {5, 2, 4, 6, 1, 3};
    int length = GET_LEN(A);
    int v1 = 0;
    int v2 = 3;

    cout << two_sum(A, length, v1) << endl;
    cout << two_sum(A, length, v2) << endl;
    return 0;
}