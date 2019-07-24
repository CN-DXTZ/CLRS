// 二分查找（迭代）
#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

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

    return ((v <= A[p]) ? p : p + 1); // 等于号为v==A[p]时，小于号为v<A[0]时
}

int main()
{
    int A[] = {1, 3, 5, 7};
    int v1 = 0;
    int v2 = 1;
    int v3 = 2;
    int v4 = 3;
    int v5 = 4;
    int v6 = 5;
    int v7 = 6;
    int v8 = 7;
    int v9 = 8;

    cout << binary_search(A, 0, GET_LEN(A) - 1, v1) << endl;
    cout << binary_search(A, 0, GET_LEN(A) - 1, v2) << endl;
    cout << binary_search(A, 0, GET_LEN(A) - 1, v3) << endl;
    cout << binary_search(A, 0, GET_LEN(A) - 1, v4) << endl;
    cout << binary_search(A, 0, GET_LEN(A) - 1, v5) << endl;
    cout << binary_search(A, 0, GET_LEN(A) - 1, v6) << endl;
    cout << binary_search(A, 0, GET_LEN(A) - 1, v7) << endl;
    cout << binary_search(A, 0, GET_LEN(A) - 1, v8) << endl;
    cout << binary_search(A, 0, GET_LEN(A) - 1, v9) << endl;
    return 0;
}