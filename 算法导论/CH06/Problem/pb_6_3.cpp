// Young氏矩阵
#include <iostream>
#include <cstdio>
#include <climits>
#include <ctime>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

class Young
{
private:
    int **A;
    int size;
    int M, N;
    void minHeapify(int i, int j);
    void buildMinHeap(void);

public:
    Young(int *a, int len, int m, int n);
    ~Young();
    int extractMin();
    void decreaseKey(int i, int j, int key);
    void insert(int key);
    void sort();
    int find(int key);
    void printYoung();
};

Young::Young(int *a, int len, int m, int n)
{
    size = len;
    M = m, N = n;
    int k = 0;
    A = new int *[m];
    for (int i = 0; i < M; i++)
    {
        A[i] = new int[N];
        for (int j = 0; j < N; j++)
        {
            if (k < size)
                A[i][j] = a[k++];
            else
                A[i][j] = INT32_MAX;
        }
    }
    buildMinHeap();
}

Young::~Young()
{
    for (int i = 0; i < M; i++)
        delete[] A[i];
    delete[] A;
}

// 维护堆的性质，下降该节点（插入，一次幅值）
void Young::minHeapify(int i, int j)
{
    while (i < M && j < N && (N * i + j) < size)
    {
        int nextI = i + 1, nextJ = j + 1;
        int smallestI = i, smallestJ = j;
        if (nextJ < N && (N * i + nextJ) < size && A[i][nextJ] < A[smallestI][smallestJ])
            smallestI = i, smallestJ = nextJ;
        if (nextI < M && (N * nextI + j) < size && A[nextI][j] < A[smallestI][smallestJ])
            smallestI = nextI, smallestJ = j;
        if (smallestI != i || smallestJ != j)
        {
            swap(A[i][j], A[smallestI][smallestJ]);
            i = smallestI, j = smallestJ;
        }
        else
            break;
    }
    // printYoung();
}

// 建堆
void Young::buildMinHeap()
{
    for (int i = (size - 1) / N; i >= 0; i--)
        for (int j = N - 1; j >= 0; j--)
            minHeapify(i, j);
}

// 去掉并返回具有最大关键字的元素
int Young::extractMin()
{
    if (size < 1)
        printf("heap underflow\n");
    int min = A[0][0];
    A[0][0] = A[(size - 1) / N][(size - 1) % N];
    A[(size - 1) / N][(size - 1) % N] = INT32_MAX;
    size--;
    minHeapify(0, 0);
    return min;
}

// 将第i个元素的键值减少到key并上升该节点（插入，一次幅值）
void Young::decreaseKey(int i, int j, int key)
{
    if (key > A[i][j])
        printf("new key is larger than current key\n");

    A[i][j] = key;
    while (i >= 0 && j >= 0 && (N * i + j) > 0)
    {
        int nextI = i - 1, nextJ = j - 1;
        int largestI = i, largestJ = j;
        if (nextJ >= 0 && A[i][nextJ] > A[largestI][largestJ])
            largestI = i, largestJ = nextJ;
        if (nextI >= 0 && A[nextI][j] > A[largestI][largestJ])
            largestI = nextI, largestJ = j;
        if (largestI != i || largestJ != j)
        {
            swap(A[i][j], A[largestI][largestJ]);
            i = largestI, j = largestJ;
        }
        else
            break;
    }
}

// 插入新键值key
void Young::insert(int key)
{
    size++;
    A[(size - 1) / N][(size - 1) % N] = INT32_MAX;
    decreaseKey((size - 1) / N, (size - 1) % N, key);
}

// 排序
void Young::sort()
{
    for (int i = size - 1; i > 0; i--)
    {
        swap(A[0][0], A[(size - 1) / N][(size - 1) % N]);
        size--;
        minHeapify(0, 0);
    }
}

// 寻找其中一个key的位置
int Young::find(int key)
{
    int i = M - 1, j = 0;

    while (i >= 0 && j < N)
    {
        // printf("%d  %d\n", i, j);
        if (A[i][j] == key)
            return i * M + j;

        if (A[i][j] < key)
            j++;
        else
            i--;
    }
    return -1;
}

// 打印Young
void Young::printYoung()
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%12d", A[i][j]);
        printf("\n");
    }
    printf("-----------------------------\n");
}

// 测试1：建堆
void test1()
{
    int a[] = {9, 16, 3, 2, 4, 8, 5, 14, 12};
    Young y = Young(a, GET_LEN(a), 4, 4);
    y.printYoung();
}

// 测试2：extractMin
void test2()
{
    int a[] = {9, 16, 3, 2, 4, 8, 5, 14, 12};
    Young y = Young(a, GET_LEN(a), 4, 4);
    y.printYoung();
    printf("min: %d\n", y.extractMin());
    y.printYoung();
}

// 测试3：insert
void test3()
{
    int a[] = {9, 16, 3, 2, 4, 8, 5, 14, 12};
    Young y = Young(a, GET_LEN(a), 4, 4);
    y.printYoung();
    y.insert(7);
    y.printYoung();
    y.insert(1);
    y.printYoung();
}

// 测试4：sort
void test4()
{
    srand(time(NULL));
    int a[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 16; j++)
            swap(a[j], a[(rand() % 16)]);

        Young y = Young(a, GET_LEN(a), 4, 4);
        cout << "origin" << endl;
        y.printYoung();
        y.sort();
        cout << "sorted" << endl;
        y.printYoung();
    }
}

// 测试5：find
void test5()
{
    srand(time(NULL));
    int a[16];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 16; j++)
            a[j] = rand() % 16;

        int m = 4, n = 4;
        Young y = Young(a, GET_LEN(a), 4, 4);
        y.printYoung();
        int key = rand() % 16;
        int f = y.find(key);
        if (f < 0)
            printf("%d is not exist\n", key);
        else
            printf("%d at (%d,%d)\n", key, (f - 1) / n + 1, f % n);
    }
}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();
    return 0;
}
