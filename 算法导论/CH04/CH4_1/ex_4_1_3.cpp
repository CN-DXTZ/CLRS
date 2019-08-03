// 最大子数组（暴力）
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

/*↓↓↓↓↓↓↓↓↓ 改自ex_4_1_2__最大子数组（暴力）.cpp ↓↓↓↓↓↓↓↓↓*/
ans find_maximum_subarra_brute_force(int A[], int low, int high)
{
    int max_sum = INT32_MIN;
    int left = low, right = high;
    for (int i = low; i < high; i++)
    {
        for (int j = i, sum = 0; j < high; j++)
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
/*↑↑↑↑↑↑↑↑↑ 改自ex_4_1_2__最大子数组（暴力）.cpp ↑↑↑↑↑↑↑↑↑*/

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

// 最大子数组 分治+暴力
ans find_maximum_subarray_recursive_brute_force(int A[], int low, int high, int n)
{
    if ((high - low) <= n)
        return find_maximum_subarra_brute_force(A, low, high);
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

// 测试1——性能交叉点
void test1_intersection()
{
    cout.setf(ios::fixed, ios::floatfield);
    srand(time(NULL));

    LARGE_INTEGER lFrequency;               //LARGE_INTEGER为数据类型
    QueryPerformanceFrequency(&lFrequency); //获取CPU的时钟频率
    LARGE_INTEGER lBeginCount, lEndCount;

    int n = 1;
    while (true)
    {
        cout << "n = " << n << endl;

        int A[n];

        int time = 1000;
        double t1 = 0, t2 = 0;
        for (int j = 0; j < time; j++)
        {
            for (int i = 0; i < n; i++)
                A[i] = rand() % 50 - 25;

            QueryPerformanceCounter(&lBeginCount); //获取CPU计数器数字，放在计时开头
            find_maximum_subarra_brute_force(A, 0, n - 1);
            QueryPerformanceCounter(&lEndCount); //获得CPU计数器数字，放在计时结尾
            t1 += lEndCount.QuadPart - lBeginCount.QuadPart;

            QueryPerformanceCounter(&lBeginCount);
            find_maximum_subarray_recursive(A, 0, n - 1);
            QueryPerformanceCounter(&lEndCount);
            t2 += lEndCount.QuadPart - lBeginCount.QuadPart;
        }
        t1 = t1 * 1000000.0 / lFrequency.QuadPart / time;
        t2 = t2 * 1000000.0 / lFrequency.QuadPart / time;
        cout << "brute-force: " << t1 << endl;
        cout << "recursive:   " << t2 << endl;

        double diff = t1 - t2;
        cout << "time difference: " << diff << endl;
        if (diff < 1)
            n++;
        else
            return;
    }
}

// 测试2——性能交叉点是否改变
void test2_intersection_is_exchange()
{
    cout.setf(ios::fixed, ios::floatfield);
    srand(time(NULL));

    LARGE_INTEGER lFrequency;               //LARGE_INTEGER为数据类型
    QueryPerformanceFrequency(&lFrequency); //获取CPU的时钟频率
    LARGE_INTEGER lBeginCount, lEndCount;

    int n = 1;
    while (true)
    {
        cout << "n = " << n << endl;

        int A[n];

        int time = 1000;
        double t1 = 0, t2 = 0, t3 = 0;
        for (int j = 0; j < time; j++)
        {
            for (int i = 0; i < n; i++)
                A[i] = rand() % 50 - 25;

            QueryPerformanceCounter(&lBeginCount); //获取CPU计数器数字，放在计时开头
            find_maximum_subarra_brute_force(A, 0, n - 1);
            QueryPerformanceCounter(&lEndCount); //获得CPU计数器数字，放在计时结尾
            t1 += lEndCount.QuadPart - lBeginCount.QuadPart;

            QueryPerformanceCounter(&lBeginCount);
            find_maximum_subarray_recursive(A, 0, n - 1);
            QueryPerformanceCounter(&lEndCount);
            t2 += lEndCount.QuadPart - lBeginCount.QuadPart;

            QueryPerformanceCounter(&lBeginCount);
            find_maximum_subarray_recursive_brute_force(A, 0, n - 1, 29);
            QueryPerformanceCounter(&lEndCount);
            t3 += lEndCount.QuadPart - lBeginCount.QuadPart;
        }
        t1 = t1 * 1000000.0 / lFrequency.QuadPart / time;
        t2 = t2 * 1000000.0 / lFrequency.QuadPart / time;
        t3 = t3 * 1000000.0 / lFrequency.QuadPart / time;
        cout << "brute-force:       " << t1 << endl;
        cout << "recursive:         " << t2 << endl;
        cout << "recursive_force:   " << t3 << endl;

        double diff = t1 - t2;
        if (diff < 1)
            n++;
        else
            return;
    }
}

// 测试3——n的选择
void test3_how_much_n()
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
        double t1 = 0, t2 = 0, t3 = 0;
        for (int j = 0; j < time; j++)
        {
            for (int i = 0; i < n; i++)
                A[i] = rand() % 100 - 50;

            QueryPerformanceCounter(&lBeginCount); //获取CPU计数器数字，放在计时开头
            find_maximum_subarray_recursive(A, 0, n - 1);
            QueryPerformanceCounter(&lEndCount); //获得CPU计数器数字，放在计时结尾
            t1 += lEndCount.QuadPart - lBeginCount.QuadPart;

            QueryPerformanceCounter(&lBeginCount);
            find_maximum_subarray_recursive_brute_force(A, 0, n - 1, 29);
            QueryPerformanceCounter(&lEndCount);
            t2 += lEndCount.QuadPart - lBeginCount.QuadPart;

            QueryPerformanceCounter(&lBeginCount);
            find_maximum_subarray_recursive_brute_force(A, 0, n - 1, 19);
            QueryPerformanceCounter(&lEndCount);
            t3 += lEndCount.QuadPart - lBeginCount.QuadPart;
        }
        t1 = t1 * 1000000.0 / lFrequency.QuadPart / time;
        t2 = t2 * 1000000.0 / lFrequency.QuadPart / time;
        t3 = t3 * 1000000.0 / lFrequency.QuadPart / time;
        cout << "recursive:        " << t1 << endl;
        cout << "recur_29_force:   " << t2 << endl;
        cout << "recur_19_force:   " << t3 << endl;

        n *= 2;
    }
}

int main()
{
    // test1_intersection();
    // test2_intersection_is_exchange();
    test3_how_much_n();
    return 0;
}