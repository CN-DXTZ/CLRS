// d叉最大堆
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

class dHeap
{
private:
    int *A;
    int D;
    int size;
    int capacity;
    int parent(int i) { return (i - 1) / D; };
    int child(int i, int c) { return (i * D) + c + 1; };
    void maxDHeapify(int i);
    void buildMaxDHeap(void);

public:
    dHeap(int *, int, int);
    int extractMax();
    void increaseKey(int, int);
    void insert(int);
    void printDHeap();
};

dHeap::dHeap(int *a, int len, int d)
{
    A = a;
    D = d;
    size = len;
    capacity = len;
    buildMaxDHeap();
}

// 维护堆的性质，下降该节点
void dHeap::maxDHeapify(int i)
{
    int end = parent(size - 1);
    while (i <= end)
    {
        int currChild = child(i, 0);
        int largest = i;
        for (int j = 0; j < D; j++)
        {
            if (currChild < size && A[currChild] > A[largest])
                largest = currChild;
            currChild++;
        }
        if (largest != i)
        {
            swap(A[i], A[largest]);
            i = largest;
        }
        else
            break;
        // printdHeap();
    }
}

// 建堆
void dHeap::buildMaxDHeap()
{
    for (int i = parent(size - 1); i >= 0; i--)
    {
        maxDHeapify(i);
        // printDHeap();
    }
}

// 去掉并返回具有最大关键字的元素
int dHeap::extractMax()
{
    if (size < 1)
        printf("heap underflow\n");
    int max = A[0];
    A[0] = A[size - 1];
    size--;
    maxDHeapify(0);
    return max;
}

// 将第i个元素的键值增加到key并上升该节点（插入，一次幅值）
void dHeap::increaseKey(int i, int key)
{
    if (key < A[i])
        printf("new key is smaller than current key\n");
    while (i > 0 && A[parent(i)] < key)
    {
        A[i] = A[parent(i)];
        i = parent(i);
        // printHeap();
    }
    A[i] = key;
}

// 插入新键值key
void dHeap::insert(int key)
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
void dHeap::printDHeap()
{
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// 测试1：建堆
void test1()
{
    int a3[] = {7, 4, 0, 6, 2, 1, 15, 13, 9, 5, 12, 8};
    int a4[] = {7, 4, 0, 6, 2, 1, 15, 13, 9, 5, 12, 8};
    dHeap dhp3 = dHeap(a3, GET_LEN(a3), 3);
    dhp3.printDHeap();
    dHeap dhp4 = dHeap(a4, GET_LEN(a4), 4);
    dhp4.printDHeap();
}

// 测试2：extractMax
void test2()
{
    int a[] = {7, 4, 0, 6, 2, 1, 15, 13, 9, 5, 12, 8};
    dHeap dhp3 = dHeap(a, GET_LEN(a), 3);
    dhp3.printDHeap();
    printf("max: %d\n", dhp3.extractMax());
    dhp3.printDHeap();
}

// 测试3：increaseKey
void test3()
{
    int a[] = {7, 4, 0, 6, 2, 1, 15, 13, 9, 5, 12, 8};
    dHeap dhp3 = dHeap(a, GET_LEN(a), 3);
    dhp3.printDHeap();
    dhp3.increaseKey(4, 17);
    dhp3.printDHeap();
}

// 测试4：insert
void test4()
{
    int a[] = {7, 4, 0, 6, 2, 1, 15, 13, 9, 5, 12, 8};
    dHeap dhp3 = dHeap(a, GET_LEN(a), 3);
    dhp3.printDHeap();
    dhp3.insert(17);
    dhp3.printDHeap();
}

int main()
{
    // test1();
    // test2();
    // test3();
    test4();
    return 0;
}
