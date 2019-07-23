// 选择排序
#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void selection_sort(int A[], int length)
{
    for (int i = 0, j; i < (length - 1); i++)
    {
        int p_min = i;

        for (j = (i + 1); j < length; j++)
            if (A[j] < A[p_min])
                p_min = j;

        int tmp = A[p_min];
        A[p_min] = A[i];
        A[i] = tmp;
    }
}

int main()
{
    int A[] = {5, 2, 4, 6, 1, 3};
    int length = GET_LEN(A);

    selection_sort(A, length);
    for (int i = 0; i < length; i++)
        cout << A[i] << endl;
    return 0;
}