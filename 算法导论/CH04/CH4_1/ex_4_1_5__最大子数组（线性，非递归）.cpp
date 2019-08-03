// 最大子数组（线性，非递归）
#include <iostream>
#include <climits>
#include <ctime>
#include <windows.h>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

struct ans
{
    int low;
    int high;
    int sum;
};

ans find_maximum_subarray_linear(int A[], int length)
{
    int max_left = 0, max_right = 0, max_sum = A[0];
    int left = 0, sum = A[0];

    for (int i = 1; i < length; i++)
    {
        // 当前子数组和非负
        if (sum >= 0)
        {
            sum += A[i];
            // 当前子数组已知最大
            if (max_sum < sum)
            {
                max_left = left;
                max_right = i;
                max_sum = sum;
            }
        }
        // 新子数组
        else
        {
            left = i;
            sum = A[i];
        }
    }

    return {max_left, max_right, max_sum};
}

// 测试1——最大子数组（线性，非递归）函数测试
void test1_linear()
{
    int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int length = GET_LEN(A);

    ans answer = find_maximum_subarray_linear(A, length);
    cout << answer.low << " " << answer.high << " " << answer.sum << endl;
}

/*↓↓↓↓↓↓↓↓↓ 参见EG_4_1_1__最大子数组（分治）.cpp ↓↓↓↓↓↓↓↓↓*/
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
ans find_maximum_subarray_recursive(int A[], int low, int high)
{
    if (low == high)
        return {low, high, A[low]};
    else
    {
        int mid = (low + high) / 2;
        ans left = find_maximum_subarray_recursive(A, low, mid);
        ans right = find_maximum_subarray_recursive(A, mid + 1, high);
        ans cross = find_max_crossing_subarray(A, low, mid, high);
        if (left.sum >= right.sum && left.sum >= cross.sum)
            return left;
        else if (right.sum >= left.sum && right.sum >= cross.sum)
            return right;
        else
            return cross;
    }
}
/*↑↑↑↑↑↑↑↑↑ 参见EG_4_1_1__最大子数组（分治）.cpp ↑↑↑↑↑↑↑↑↑*/

// 测试2——最大子数组，线性和分治的效率比较
void test2_cmp_time()
{
    cout.setf(ios::fixed, ios::floatfield);
    srand(time(NULL));

    LARGE_INTEGER lFrequency;               //LARGE_INTEGER为数据类型
    QueryPerformanceFrequency(&lFrequency); //获取CPU的时钟频率
    LARGE_INTEGER lBeginCount, lEndCount;

    int n = 16;
    while (n <= 262144)
    {
        cout << "n = " << n << endl;

        int A[n];

        int time = 100;
        double t1 = 0, t2 = 0;
        ans answer;
        for (int j = 0; j < time; j++)
        {
            for (int i = 0; i < n; i++)
                A[i] = rand() % 100 - 50;

            QueryPerformanceCounter(&lBeginCount); //获取CPU计数器数字，放在计时开头
            answer = find_maximum_subarray_recursive(A, 0, n - 1);
            QueryPerformanceCounter(&lEndCount); //获得CPU计数器数字，放在计时结尾
            t1 += lEndCount.QuadPart - lBeginCount.QuadPart;
            // cout << answer.low << " " << answer.high << " " << answer.sum << " " << endl;

            QueryPerformanceCounter(&lBeginCount);
            answer = find_maximum_subarray_linear(A, n);
            QueryPerformanceCounter(&lEndCount);
            t2 += lEndCount.QuadPart - lBeginCount.QuadPart;
            // cout << answer.low << " " << answer.high << " " << answer.sum << " " << endl;
        }
        t1 = t1 * 1000000.0 / lFrequency.QuadPart / time;
        t2 = t2 * 1000000.0 / lFrequency.QuadPart / time;
        cout << "recursive:  " << t1 << endl;
        cout << "linear:     " << t2 << endl;

        n *= 4;
    }
}

int main()
{
    // test1_linear();
    // cout << "------------------" << endl;
    test2_cmp_time();
    return 0;
}