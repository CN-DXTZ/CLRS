// 插入排序（迭代，二分查找）
#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

/*↓↓↓↓↓↓↓↓↓ 参见ex_2_3_5__二分查找（迭代）.cpp ↓↓↓↓↓↓↓↓↓*/
int binary_search(int A[], int p, int q, int v)
{
    while (p < q)
    {
        int mid = (p + q) / 2;
        if (v <= A[mid])
            q = mid;
        else
            p = mid + 1;
    }

    return ((v <= A[p]) ? p : p + 1);
}
/*↑↑↑↑↑↑↑↑↑ 参见ex_2_3_5__二分查找（迭代）.cpp ↑↑↑↑↑↑↑↑↑*/

void insertion_sort(int A[], int length)
{
    for (int j = 1; j < length; j++)
    {
        int key = A[j];
        int i = binary_search(A, 0, j - 1, key);
        for (int k = j - 1; k >= i; k--)
            A[k + 1] = A[k];
        A[i] = key;
    }
}

int main()
{
    int A[] = {5, 2, 4, 6, 1, 3};
    int length = GET_LEN(A);

    insertion_sort(A, length);
    for (int i = 0; i < length; i++)
        cout << A[i] << endl;
    return 0;
}