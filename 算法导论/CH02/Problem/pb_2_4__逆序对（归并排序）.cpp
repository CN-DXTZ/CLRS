// 逆序对（归并排序）
#include <iostream>
#include <climits>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void merge(int A[], int p, int q, int r, int &cnt)
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
        {
            A[k] = R[j++];
            cnt += n1 - i;
        }
    }
}

void merge_sort(int A[], int p, int r, int &cnt)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(A, p, q, cnt);
        merge_sort(A, q + 1, r, cnt);
        merge(A, p, q, r, cnt);
    }
}

int main()
{
    int A[] = {5, 2, 4, 7, 1, 3, 2, 6};
    //           +1 +1    +4 +3 +4 +1 = 14
    int length = GET_LEN(A);
    int cnt = 0;

    merge_sort(A, 0, length - 1, cnt);
    for (int i = 0; i < length; i++)
        cout << A[i] << endl;
    cout << cnt << endl;
    return 0;
}