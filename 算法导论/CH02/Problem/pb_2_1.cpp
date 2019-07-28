// 归并排序（哨兵）
#include <iostream>
#include <climits>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

/********** 参见EG_2_3_1__归并排序（哨兵）.cpp **********/
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
/********** 参见EG_2_3_1__归并排序（哨兵）.cpp **********/

/********** 改自EG_2_1_1__插入排序（迭代，线性查找）.cpp **********/
void insertion_sort(int A[], int p, int r)
{
    for (int j = p + 1; j <= r; j++)
    {
        int key = A[j];

        int i = j - 1;
        while (i >= p && A[i] > key)
        {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }
}
/********** 改自EG_2_1_1__插入排序（迭代，线性查找）.cpp **********/

void merge_insertion_sort(int A[], int p, int r, int k)
{
    if (p < r)
    {
        if ((r - p) <= k) // 插入排序
        {
            insertion_sort(A, p, r);
        }
        else // 归并排序
        {
            int q = (p + r) / 2;
            merge_insertion_sort(A, p, q, k);
            merge_insertion_sort(A, q + 1, r, k);
            merge(A, p, q, r);
        }
        
        // 打印过程
        // for (int i = 0; i < 8; i++)
        //     cout << A[i];
        // cout << endl;
    }
}

int main()
{
    int A[] = {5, 2, 4, 7, 1, 3, 2, 6};
    int length = GET_LEN(A);

    merge_insertion_sort(A, 0, length - 1, 4);
    for (int i = 0; i < length; i++)
        cout << A[i] << endl;

    return 0;
}