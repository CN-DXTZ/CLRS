#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

// 霍纳规则
int horner_rule(int A[], int x, int length)
{
    int y = 0;
    for (int i = length - 1; i >= 0; i--)
        y = A[i] + x * y;
    return y;
}

// 朴素多项式求值
int naive_poly_eval(int A[], int x, int length)
{
    int y = 0;
    for (int i = 0; i < length; i++)
    {
        int pi = A[i];
        for (int j = 0; j < i; j++)
            pi *= x;
        y += pi;
    }
    return y;
}

int main()
{
    int A[] = {1, 2, 3, 4};
    int x = 2;
    int length = GET_LEN(A);

    cout << horner_rule(A, x, length) << endl;
    cout << naive_poly_eval(A, x, length) << endl;

    return 0;
}