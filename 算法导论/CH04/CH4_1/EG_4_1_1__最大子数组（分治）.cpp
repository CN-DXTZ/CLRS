// 最大子数组（归并）
#include <iostream>
#include <climits>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

struct ans
{
    int low;
    int high;
    int sum;
};

ans find_max_crossing_subarray(int A[], int low, int mid, int high)
{
    int left_sum = INT32_MIN;
    int left_p = 0;
    for (int i = mid, sum = 0; i >= low; i--)
    {
        sum += A[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            left_p = i;
        }
    }

    int right_sum = INT32_MIN;
    int right_p = 0;
    for (int i = mid + 1, sum = 0; i <= high; i++)
    {
        sum = sum + A[i];
        if (sum > right_sum)
        {
            right_sum = sum;
            right_p = i;
        }
    }

    return {left_p, right_p, left_sum + right_sum};
}

ans find_maximum_subarray(int A[], int low, int high)
{
    // cout << low << " " << high << " " << endl;
    if (low == high)
        return {low, high, A[low]};
    else
    {
        int mid = (low + high) / 2;
        ans left = find_maximum_subarray(A, low, mid);
        ans right = find_maximum_subarray(A, mid + 1, high);
        ans cross = find_max_crossing_subarray(A, low, mid, high);
        if (left.sum >= right.sum && left.sum >= cross.sum)
            return left;
        else if (right.sum >= left.sum && right.sum >= cross.sum)
            return right;
        else
            return cross;
    }
}

int main()
{
    int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int length = GET_LEN(A);

    ans answer = find_maximum_subarray(A, 0, length - 1);
    cout << answer.low << " " << answer.high << " " << answer.sum << endl;
    return 0;
}