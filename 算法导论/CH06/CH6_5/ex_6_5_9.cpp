// 最小优先队列
#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>
using namespace std;

#define GET_LEN(array) (sizeof(array) / sizeof(array[0]))

void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    void printListNode()
    {
        printf("%d", val);
        ListNode *ans = next;
        while (ans != NULL)
        {
            printf(" -> %d", ans->val);
            ans = ans->next;
        }
        printf("\n", val);
    }
};

class MinPriorityQueue
{
private:
    vector<ListNode *> A;
    int parent(int i) { return (i - 1) >> 1; };
    int left(int i) { return (i << 1) + 1; };
    int right(int i) { return (i << 1) + 2; };
    void minHeapify(int i);
    void buildMinHeap(void);

public:
    MinPriorityQueue(vector<ListNode *>);
    ListNode *minimum() { return A[0]; };
    ListNode *extractMin();
    void decreaseKey(int, int);
    void insert(int);
    void printHeap();
    ListNode *mergeKLists();
};

MinPriorityQueue::MinPriorityQueue(vector<ListNode *> a)
{
    A = a;
    buildMinHeap();
}

// 建堆
void MinPriorityQueue::buildMinHeap()
{
    int i = (A.size() - 1) / 2;
    while (i >= 0)
        minHeapify(i--);
}

// 维护堆的性质，下降该节点
void MinPriorityQueue::minHeapify(int i)
{
    int size = A.size();
    while (i < (size >> 1))
    {
        int l = left(i), r = right(i);
        int smallest = i;
        if (l < size && A[l]->val < A[smallest]->val)
            smallest = l;
        if (r < size && A[r]->val < A[smallest]->val)
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
ListNode *MinPriorityQueue::extractMin()
{
    int size = A.size();
    if (size < 1)
        printf("heap underflow\n");
    ListNode *min = A[0];
    A[0] = A[size - 1];
    size--;
    minHeapify(0);
    return min;
}

// 合并k个链表
ListNode *MinPriorityQueue::mergeKLists()
{
    ListNode *HEAD = new ListNode(0);
    ListNode *p = HEAD;
    while (!A.empty())
    {
        p = p->next = A[0];
        A[0] = A[0]->next;
        if (!A[0]) // 该链表访问完
        {
            A[0] = A.back();
            A.pop_back();
        }
        minHeapify(0);
        printHeap();
    }
    return HEAD->next;
}

// 打印堆
void MinPriorityQueue::printHeap()
{
    int n_max = A.size();

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
                printf("%4d", A[i++]->val);
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
    ListNode *l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);
    ListNode *l2 = new ListNode(0);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    ListNode *l3 = new ListNode(2);
    l3->next = new ListNode(6);
    vector<ListNode *> v = {l1, l2, l3};

    for (int i = 0; i < v.size(); i++)
        (*v[i]).printListNode();

    MinPriorityQueue mpq = MinPriorityQueue(v);
    mpq.printHeap();
    ListNode *ans = mpq.mergeKLists();
    (*ans).printListNode();
    return 0;
}
