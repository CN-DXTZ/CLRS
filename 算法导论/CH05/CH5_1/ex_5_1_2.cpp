#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

int random(int a, int b)
{
    int diff = b - a;
    int p = 0, d = diff;
    while (d)
    {
        d = d >> 1;
        p++;
    }
    while (true)
    {
        int ans = 0;
        for (int i = 0; i < p && ans <= diff; i++)
            ans = ans << 1 | rand() % 2;
        if (ans <= diff)
            return ans + a;
    }
}

int main()
{
    srand(time(NULL));
    int test[8][2] = {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 7}, {1, 8}, {1, 9}, {1, 10}};

    for (int i = 0; i < 8; i++)
    {
        int a[11] = {};
        int j = 10000;
        while (j--)
            a[random(test[i][0], test[i][1])]++;
        for (int k = 0; k < 11; k++)
            printf("%6d ", a[k]);
        printf("\n");
    }
    return 0;
}