// 矩阵乘法
#include <iostream>
#include <cstring>
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

/*↓↓↓↓↓↓↓↓↓ 改自EG_4_2_1__矩阵乘法.cpp ↓↓↓↓↓↓↓↓↓*/
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
        {
            cout << "S" << i + 1 << " = ";
            mat_print(S[i], half);
            mat_del(S[i], half);
        }

        for (int i = 0; i < 7; i++)
        {
            cout << "P" << i + 1 << " = ";
            mat_print(P[i], half);
            mat_del(P[i], half);
        }
    }
    if (n > 1)
        mat_print(C, n);
    return C;
}

int main()
{
    int n = 2;
    int **A = new int *[n], **B = new int *[n];
    int A_[n][n] = {{1, 3}, {7, 5}},
        B_[n][n] = {{6, 8}, {4, 2}};
    for (int i = 0; i < n; i++)
    {
        A[i] = new int[n];
        B[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            A[i][j] = A_[i][j];
            B[i][j] = B_[i][j];
        }
    }
    mat_print(A, n);

    int **C;

    C = square_matrix_multiply_Strassen(A, {0, 0}, B, {0, 0}, n);
    mat_print(C, n);
    mat_del(C, n);
    return 0;
}