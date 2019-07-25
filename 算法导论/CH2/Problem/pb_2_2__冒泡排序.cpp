// 冒泡排序
#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void bubble_sort(int A[], int length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = length-1; j > i; j--)
        {
            if (A[j] < A[j - 1])
            {
                int tmp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = tmp;
            }
        }
    }
}

int main()
{
    int A[] = {5, 2, 4, 7, 1, 3, 2, 6};
    int length = GET_LEN(A);

    bubble_sort(A, length);
    for (int i = 0; i < length; i++)
        cout << A[i] << endl;

    return 0;
}