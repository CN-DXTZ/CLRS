// 矩阵乘法
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <windows.h>
using namespace std;

struct pos
{
    int x, y;
};

// 输出矩阵
void mat_print(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    cout << "-----------\n";
}
// 回收矩阵内存空间
void mat_del(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete[] A[i];
    }
    delete[] A;
}

// 矩阵乘法 - 自然定义
int **square_matrix_multiply_naive(int **A, int **B, int n)
{
    int **C = new int *[n];
    for (int i = 0; i < n; i++)
    {
        C[i] = new int[n];
        memset(C[i], 0, sizeof(C[i]));
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

//矩阵乘法 - 分治
void matrix_add(int **A, int **B, int **C, pos cp, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[cp.x + i][cp.y + j] = A[i][j] + B[i][j];
}
int **square_matrix_multiply_recursive(int **A, pos ap, int **B, pos bp, int n)
{
    int **C = new int *[n];
    for (int i = 0; i < n; i++)
    {
        C[i] = new int[n];
        memset(C[i], 0, sizeof(C[i]));
    }

    if (n == 1)
        C[0][0] = A[ap.x][ap.y] * B[bp.x][bp.y];
    else
    {
        int half = n / 2;
        int c1 = 0, c2 = half;
        int a1x = ap.x, a1y = ap.y, a2x = ap.x + half, a2y = ap.y + half;
        int b1x = bp.x, b1y = bp.y, b2x = bp.x + half, b2y = bp.y + half;
        int **sub1, **sub2;

        sub1 = square_matrix_multiply_recursive(A, {a1x, a1y}, B, {b1x, b1y}, half);
        sub2 = square_matrix_multiply_recursive(A, {a1x, a2y}, B, {b2x, b1y}, half);
        matrix_add(sub1, sub2, C, {c1, c1}, half);
        mat_del(sub1, half), mat_del(sub2, half);
        sub1 = square_matrix_multiply_recursive(A, {a1x, a1y}, B, {b1x, b2y}, half);
        sub2 = square_matrix_multiply_recursive(A, {a1x, a2y}, B, {b2x, b2y}, half);
        matrix_add(sub1, sub2, C, {c1, c2}, half);
        mat_del(sub1, half), mat_del(sub2, half);
        sub1 = square_matrix_multiply_recursive(A, {a2x, a1y}, B, {b1x, b1y}, half);
        sub2 = square_matrix_multiply_recursive(A, {a2x, a2y}, B, {b2x, b1y}, half);
        matrix_add(sub1, sub2, C, {c2, c1}, half);
        mat_del(sub1, half), mat_del(sub2, half);
        sub1 = square_matrix_multiply_recursive(A, {a2x, a1y}, B, {b1x, b2y}, half);
        sub2 = square_matrix_multiply_recursive(A, {a2x, a2y}, B, {b2x, b2y}, half);
        matrix_add(sub1, sub2, C, {c2, c2}, half);
        mat_del(sub1, half), mat_del(sub2, half);
    }
    return C;
}

// 矩阵乘法 - Strassen
// 矩阵一阶运算
int **matrix_1st_order_oper(int **A, pos ap, int **B, pos bp, int n, bool isadd)
{
    int **C = new int *[n];
    for (int i = 0; i < n; i++)
    {
        C[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            if (isadd)
                C[i][j] = A[ap.x + i][ap.y + j] + B[bp.x + i][bp.y + j];
            else
                C[i][j] = A[ap.x + i][ap.y + j] - B[bp.x + i][bp.y + j];
        }
    }
    return C;
}
int **square_matrix_multiply_Strassen(int **A, pos ap, int **B, pos bp, int n)
{
    int **C = new int *[n];
    for (int i = 0; i < n; i++)
    {
        C[i] = new int[n];
        memset(C[i], 0, sizeof(C[i]));
    }

    if (n == 1)
        C[0][0] = A[ap.x][ap.y] * B[bp.x][bp.y];
    else
    {
        int half = n / 2;
        int a1x = ap.x, a1y = ap.y, a2x = ap.x + half, a2y = ap.y + half;
        int b1x = bp.x, b1y = bp.y, b2x = bp.x + half, b2y = bp.y + half;

        int **S[10];
        S[0] = matrix_1st_order_oper(B, {b1x, b2y}, B, {b2x, b2y}, half, false);
        S[1] = matrix_1st_order_oper(A, {a1x, a1y}, A, {a1x, a2y}, half, true);
        S[2] = matrix_1st_order_oper(A, {a2x, a1y}, A, {a2x, a2y}, half, true);
        S[3] = matrix_1st_order_oper(B, {b2x, b1y}, B, {b1x, b1y}, half, false);
        S[4] = matrix_1st_order_oper(A, {a1x, a1y}, A, {a2x, a2y}, half, true);
        S[5] = matrix_1st_order_oper(B, {b1x, b1y}, B, {b2x, b2y}, half, true);
        S[6] = matrix_1st_order_oper(A, {a1x, a2y}, A, {a2x, a2y}, half, false);
        S[7] = matrix_1st_order_oper(B, {b2x, b1y}, B, {b2x, b2y}, half, true);
        S[8] = matrix_1st_order_oper(A, {a1x, a1y}, A, {a2x, a1y}, half, false);
        S[9] = matrix_1st_order_oper(B, {b1x, b1y}, B, {b1x, b2y}, half, true);

        int **P[7];
        P[0] = square_matrix_multiply_Strassen(A, {a1x, a1y}, S[0], {0, 0}, half);
        P[1] = square_matrix_multiply_Strassen(S[1], {0, 0}, B, {b2x, b2y}, half);
        P[2] = square_matrix_multiply_Strassen(S[2], {0, 0}, B, {b1x, b1y}, half);
        P[3] = square_matrix_multiply_Strassen(A, {a2x, a2y}, S[3], {0, 0}, half);
        P[4] = square_matrix_multiply_Strassen(S[4], {0, 0}, S[5], {0, 0}, half);
        P[5] = square_matrix_multiply_Strassen(S[6], {0, 0}, S[7], {0, 0}, half);
        P[6] = square_matrix_multiply_Strassen(S[8], {0, 0}, S[9], {0, 0}, half);

        for (int i = 0; i < half; i++)
            for (int j = 0; j < half; j++)
            {
                C[i][j] = P[4][i][j] + P[3][i][j] - P[1][i][j] + P[5][i][j];
                C[i][j + half] = P[0][i][j] + P[1][i][j];
                C[i + half][j] = P[2][i][j] + P[3][i][j];
                C[i + half][j + half] = P[4][i][j] + P[0][i][j] - P[2][i][j] - P[6][i][j];
            }

        for (int i = 0; i < 10; i++)
            mat_del(S[i], half);
        for (int i = 0; i < 7; i++)
            mat_del(P[i], half);
    }
    return C;
}

// 测试1——三种矩阵算法正确性测试
void test1()
{
    int n = 8;
    int **A = new int *[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = new int[n];
        for (int j = 0; j < n; j++)
            A[i][j] = i * 2 + j + 1;
    }
    mat_print(A, n);

    int **C;

    C = square_matrix_multiply_naive(A, A, n);
    mat_print(C, n);
    mat_del(C, n);

    C = square_matrix_multiply_recursive(A, {0, 0}, A, {0, 0}, n);
    mat_print(C, n);
    mat_del(C, n);

    C = square_matrix_multiply_Strassen(A, {0, 0}, A, {0, 0}, n);
    mat_print(C, n);
    mat_del(C, n);
}

// 测试1——三种矩阵算法效率测试
void test2()
{
    cout.setf(ios::fixed, ios::floatfield);
    srand(time(NULL));

    LARGE_INTEGER lFrequency;               //LARGE_INTEGER为数据类型
    QueryPerformanceFrequency(&lFrequency); //获取CPU的时钟频率
    LARGE_INTEGER lBeginCount, lEndCount;

    printf("                        time        exprate \n");
    int n = 64;
    int tn = 0;
    double t[10][3] = {};
    while (n <= 16384)
    {
        cout << "n = " << n << endl;

        double t1 = 0, t2 = 0, t3 = 0;
        int **A = new int *[n];
        for (int i = 0; i < n; i++)
        {
            A[i] = new int[n];
            for (int j = 0; j < n; j++)
                A[i][j] = rand() % 100 - 50;
        }
        int **C;

        QueryPerformanceCounter(&lBeginCount); //获取CPU计数器数字，放在计时开头
        C = square_matrix_multiply_naive(A, A, n);
        QueryPerformanceCounter(&lEndCount); //获得CPU计数器数字，放在计时结尾
        t[tn][0] = (lEndCount.QuadPart - lBeginCount.QuadPart) * 1000000.0 / lFrequency.QuadPart;
        mat_del(C, n);

        QueryPerformanceCounter(&lBeginCount); //获取CPU计数器数字，放在计时开头
        C = square_matrix_multiply_recursive(A, {0, 0}, A, {0, 0}, n);
        QueryPerformanceCounter(&lEndCount); //获得CPU计数器数字，放在计时结尾
        t[tn][1] = (lEndCount.QuadPart - lBeginCount.QuadPart) * 1000000.0 / lFrequency.QuadPart;
        mat_del(C, n);

        QueryPerformanceCounter(&lBeginCount); //获取CPU计数器数字，放在计时开头
        C = square_matrix_multiply_Strassen(A, {0, 0}, A, {0, 0}, n);
        QueryPerformanceCounter(&lEndCount); //获得CPU计数器数字，放在计时结尾
        t[tn][2] = (lEndCount.QuadPart - lBeginCount.QuadPart) * 1000000.0 / lFrequency.QuadPart;
        mat_del(C, n);

        printf("naive:     %20.2f %10.2f\n", t[tn][0], ((tn > 0) ? (t[tn][0] / t[tn - 1][0]) : 0));
        printf("recursive: %20.2f %10.2f\n", t[tn][1], ((tn > 0) ? (t[tn][1] / t[tn - 1][1]) : 0));
        printf("Strassen:  %20.2f %10.2f\n", t[tn][2], ((tn > 0) ? (t[tn][2] / t[tn - 1][2]) : 0));

        mat_del(A, n);
        n *= 2;
        tn++;
    }
}

int main()
{
    // test1();
    test2();
    return 0;
}