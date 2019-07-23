#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

int linear_search(int A[], int length, int v)
{
    int i;
    for (i = 0; i < length; i++)
        if (v == A[i])
            return i + 1;
    return i = -1;
}

int main()
{
    int A[] = {1, 2, 3, 4};
    int v1 = 3;
    int v2 = 5;
    
    cout << linear_search(A, GET_LEN(A), v1) << endl;
    cout << linear_search(A, GET_LEN(A), v2) << endl;
    return 0;
}