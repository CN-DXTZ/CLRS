// 插入排序（递归，线性查找）
#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void insertion_sort(int A[], int length)
{
    if (length > 1)
    {
        insertion_sort(A, length - 1);
        int key = A[length - 1];
        int i = (length - 1) - 1;
        while (i >= 0 && A[i] > key)
        {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
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