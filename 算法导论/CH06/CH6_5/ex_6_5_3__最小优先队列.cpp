// 最小优先队列
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

class MinPriorityQueue
{
private:
    int *A;
    int size;
    int capacity;
    int parent(int i) { return (i - 1) >> 1; };
    int left(int i) { return (i << 1) + 1; };
    int right(int i) { return (i << 1) + 2; };
    void minHeapify(int i);
    void buildMinHeap(void);

public:
    MinPriorityQueue(int *, int);
    ~MinPriorityQueue() { delete[] A; };
    int minimum() { return A[0]; };
    int extractMin();
    void decreaseKey(int, int);
    void insert(int);
    void printHeap(bool);
};

MinPriorityQueue::MinPriorityQueue(int *a, int n)
{
    A = new int[n];
    for (int i = 0; i < n; i++)
        A[i] = a[i];
    size = n;
    capacity = n;
    buildMinHeap();
}

// 建堆
void MinPriorityQueue::buildMinHeap()
{
    printHeap(true);
    int i = (size - 1) / 2;
    while (i >= 0)
        minHeapify(i--);
}

// 维护堆的性质，下降该节点
void MinPriorityQueue::minHeapify(int i)
{
    while (i < (size >> 1))
    {
        int l = left(i), r = right(i);
        int smallest = i;
        if (l < size && A[l] < A[smallest])
            smallest = l;
        if (r < size && A[r] < A[smallest])
            smallest = r;
        if (smallest != i)
        {
            swap(A[i], A[smallest]);
            i = smallest;
        }
        else
            break;
    }
}

// 去掉并返回具有最大关键字的元素
int MinPriorityQueue::extractMin()
{
    if (size < 1)
        printf("heap underflow\n");
    int min = A[0];
    A[0] = A[size - 1];
    size--;
    // printHeap(true);
    minHeapify(0);
    // printHeap(true);
    return min;
}

// 将第i个元素的键值增加到key并上升该节点
void MinPriorityQueue::decreaseKey(int i, int key)
{
    if (key > A[i])
        printf("new key is larger than current key\n");
    while (i > 0 && A[parent(i)] > key)
    {
        A[i] = A[parent(i)];
        i = parent(i);
        // printHeap(true);
    }
    A[i] = key;
}

// 插入新键值key
void MinPriorityQueue::insert(int key)
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
    A[size - 1] = INT32_MAX;
    decreaseKey(size - 1, key);
}

// 打印堆
void MinPriorityQueue::printHeap(bool isSize)
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

int main()
{
    int a[] = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    MinPriorityQueue mpq = MinPriorityQueue(a, GET_LEN(a));
    mpq.printHeap(true);
    return 0;
}
