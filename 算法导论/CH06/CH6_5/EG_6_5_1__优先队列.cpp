// 最大优先队列
#include <iostream>
#include <cstdio>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

class Heap
{
private:
    int *A;
    int size;
    int capacity;
    int parent(int i) { return (i - 1) >> 1; };
    int left(int i) { return (i << 1) + 1; };
    int right(int i) { return (i << 1) + 2; };
    void max_Heapify(int i);
    void build_max_Heap(void);

public:
    Heap(int *, int);
    int get(int i) { return A[i]; };
    void set(int i, int value) { A[i] = value; };
    int getSize() { return size; };
    void heapSort(void);
    void printArray();
    void printHeap(bool);
};

Heap::Heap(int *a, int len)
{
    A = a;
    size = len;
    capacity = len;
    build_max_Heap();
}

// 维护堆的性质
void Heap::max_Heapify(int i)
{
    while (i < (size >> 1))
    {
        int l = left(i), r = right(i);
        int largest = i;
        if (l < size && A[l] > A[i])
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
        // printHeap();
    }
}

// 建堆
void Heap::build_max_Heap()
{
    int i = (size - 1) / 2;
    while (i >= 0)
        max_Heapify(i--);
}

// 打印堆
void Heap::printHeap(bool isSize)
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
void Heap::printArray()
{
    for (int i = 0; i < capacity; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// 堆排序
void Heap::heapSort()
{
    for (int i = size - 1; i > 0; i--)
    {
        swap(A[0], A[i]);
        size -= 1;
        max_Heapify(0);
        // printHeap(false);
    }
}

// 测试1：建堆
void test1_build_max_Heap()
{
    int a[] = {5, 3, 17, 10, 84, 19, 6, 22, 9};
    Heap heap = Heap(a, GET_LEN(a));
    heap.printHeap(false);
}

// 测试2：堆排序
void test2_heapsort()
{
    int a[] = {5, 13, 2, 25, 7, 17, 20, 8, 4};
    Heap heap = Heap(a, GET_LEN(a));
    heap.printHeap(false);
    heap.heapSort();
    heap.printHeap(false);
}

int main()
{
    // test1_build_max_Heap();
    test2_heapsort();
    return 0;
}
