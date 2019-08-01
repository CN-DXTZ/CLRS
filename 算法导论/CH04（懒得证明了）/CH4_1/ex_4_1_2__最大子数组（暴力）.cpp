// 最大子数组（暴力）
#include <iostream>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

struct ans
{
    int low;
    int high;
    int sum;
};

ans find_maximum_subarray(int A[], int length)
{
    int max_sum = INT32_MIN;
    int left = 0, right = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = i, sum = 0; j < length; j++)
        {
            sum += A[j];
            if (sum > max_sum)
            {
                max_sum = sum;
                left = i;
                right = j;
            }
        }
    }
    return {left, right, max_sum};
}

int main()
{
    int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int length = GET_LEN(A);

    ans answer = find_maximum_subarray(A, length);
    cout << answer.low << " " << answer.high << " " << answer.sum << endl;
    return 0;
}