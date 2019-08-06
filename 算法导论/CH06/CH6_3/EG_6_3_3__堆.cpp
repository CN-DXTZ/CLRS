// 堆
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
    void printHeap();
};

// 维护堆的性质
void Heap::max_Heapify(int i)
{
    while (2 * i <= size)
    {
        int l = left(i), r = right(i);
        int largest = i;
        if (l <= size && A[l] > A[i])
            largest = l;
        if (r <= size && A[r] > A[largest])
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

// 建堆
void Heap::build_max_Heap()
{
    int i = (size - 1) / 2;
    while (i >= 0)
        max_Heapify(i--);
}

Heap::Heap(int *a, int len)
{
    A = a;
    size = len;
    build_max_Heap();
}

void Heap::printHeap()
{
    int size_t = size;
    int n_tab = 1;
    while (size_t)
    {
        size_t = size_t >> 1;
        n_tab = n_tab << 1;
    }

    int i = 0;
    int n_num = 1;
    n_tab--;
    while (true)
    {
        for (int j = 0; j < n_num; j++)
        {
            if (i + 1 == n_num)
                for (int k = 0; k < (n_tab >> 1); k++)
                    printf("    ");
            else
                for (int k = 0; k < n_tab; k++)
                    printf("    ");
            if (i < size)
                printf("%4d", A[i++]);
            else
                return;
        }
        printf("\n");
        n_num = n_num << 1;
        n_tab = n_tab >> 1;
    }
}

int main()
{
    int a[] = {5, 3, 17, 10, 84, 19, 6, 22, 9};
    Heap heap = Heap(a, GET_LEN(a));
    heap.printHeap();
    return 0;
}
