// 插入排序
#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void insertion_sort(int A[], int length)
{
    for (int j = 1; j < length; j++)
    {
        int key = A[j];

        int i = j - 1;
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