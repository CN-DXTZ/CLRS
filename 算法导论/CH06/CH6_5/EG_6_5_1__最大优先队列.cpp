// 最大优先队列
#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

class MaxPriorityQueue
{
private:
    int *A;
    int size;
    int capacity;
    int parent(int i) { return (i - 1) >> 1; };
    int left(int i) { return (i << 1) + 1; };
    int right(int i) { return (i << 1) + 2; };
    void maxHeapify(int i);
    void buildMaxHeap(void);

public:
    MaxPriorityQueue(int *, int);
    ~MaxPriorityQueue() { delete[] A; };
    int maximum() { return A[0]; };
    int extractMax();
    void increaseKey(int, int);
    void insert(int);
    void printArray();
    void printHeap(bool);
};

MaxPriorityQueue::MaxPriorityQueue(int *a, int n)
{
    A = new int[n];
    for (int i = 0; i < n; i++)
        A[i] = a[i];
    size = n;
    capacity = n;
    buildMaxHeap();
}

// 建堆
void MaxPriorityQueue::buildMaxHeap()
{
    int i = (size - 1) / 2;
    while (i >= 0)
        maxHeapify(i--);
}

// 维护堆的性质，下降该节点
void MaxPriorityQueue::maxHeapify(int i)
{
    while (i < (size >> 1))
    {
        int l = left(i), r = right(i);
        int largest = i;
        if (l < size && A[l] > A[largest])
            largest = l;
        if (r < size && A[r] > A[largest])
            largest = r;
        if (largest != i)
        {
            swap(A[i], A[largest]);
            i = largest;
        }
        else
            break;
    }
}

// 去掉并返回具有最大关键字的元素
int MaxPriorityQueue::extractMax()
{
    if (size < 1)
        printf("heap underflow\n");
    int max = A[0];
    A[0] = A[size - 1];
    size--;
    // printHeap(true);
    maxHeapify(0);
    // printHeap(true);
    return max;
}

// 将第i个元素的键值增加到key并上升该节点（交换，三次幅值）
void MaxPriorityQueue::increaseKey(int i, int key)
{
    if (key < A[i])
        printf("new key is smaller than current key\n");
    A[i] = key;
    // printHeap(true);
    while (i > 0 && A[parent(i)] < key)
    {
        swap(A[parent(i)], A[i]);
        i = parent(i);
        // printHeap(true);
    }
}
// 将第i个元素的键值增加到key并上升该节点（插入，一次幅值）
// void MaxPriorityQueue::increaseKey(int i, int key)
// {
//     if (key < A[i])
//         printf("new key is smaller than current key\n");
//     while (i > 0 && A[parent(i)] < key)
//     {
//         A[i] = A[parent(i)];
//         i = parent(i);
//         // printHeap(true);
//     }
//     A[i] = key;
// }

// 插入新键值key
void MaxPriorityQueue::insert(int key)
{
    size++;
    // 扩容
    if (size > capacity)
    {
        int *tmp1 = new int[capacity * 2];
        for (int i = 0; i < capacity; i++)
            tmp1[i] = A[i];
        delete[] A;
        A = tmp1;
        capacity *= 2;
    }
    A[size - 1] = INT32_MIN;
    increaseKey(size - 1, key);
}

// 打印堆
void MaxPriorityQueue::printHeap(bool isSize)
{
    int n_max = isSize ? size : capacity;

    int size_t = n_max, n_tab = 1;
    while (size_t)
    {
        size_t = size_t >> 1;
        n_tab = n_tab << 1;
    }

    int i = 0, n_num = 1;
    n_tab--;
    while (i < n_max)
    {
        for (int j = 0; j < n_num; j++)
        {
            if (i + 1 == n_num)
                for (int k = 0; k < (n_tab >> 1); k++)
                    printf("    ");
            else
                for (int k = 0; k < n_tab; k++)
                    printf("    ");
            if (i < n_max)
                printf("%4d", A[i++]);
            else
                break;
        }
        printf("\n");
        n_num = n_num << 1;
        n_tab = n_tab >> 1;
    }
    printf("----------------------------------------\n");
}

// 打印数组
void MaxPriorityQueue::printArray()
{
    for (int i = 0; i < capacity; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// 测试1：测试extract-max
void test1()
{
    int a[] = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    MaxPriorityQueue mpq = MaxPriorityQueue(a, GET_LEN(a));
    mpq.printHeap(true);
    printf("max: %d\n", mpq.extractMax());
    mpq.printHeap(true);
}

// 测试2：测试insert
void test2()
{
    int a[] = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    MaxPriorityQueue mpq = MaxPriorityQueue(a, GET_LEN(a));
    mpq.printHeap(true);
    mpq.insert(10);
    mpq.printHeap(true);
}

int main()
{
    // test1();
    test2();
    return 0;
}
