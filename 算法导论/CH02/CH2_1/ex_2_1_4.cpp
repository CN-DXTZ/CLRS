#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void binary_add(int A[], int B[], int c_length, int C[])
{
    int CF = 0;
    for (int i = c_length - 1; i >= 1; i--)
    {
        C[i] = A[i - 1] + B[i - 1] + CF;
        if (C[i] >= 2)
        {
            C[i] = C[i] - 2;
            CF = 1;
        }
        else
        {
            CF = 0;
        }
    }
    C[0] = CF;
}

int main()
{
    int A[] = {1, 0, 0, 1};
    int B[] = {1, 0, 1, 1};
    int n = GET_LEN(A);
    int c_length = n + 1;
    int C[c_length] = {};
    binary_add(A, B, c_length, C);

    for (int i = 0; i <= n; i++)
        cout << C[i] << endl;
    return 0;
}