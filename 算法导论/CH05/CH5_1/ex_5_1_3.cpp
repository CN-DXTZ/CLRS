#include <iostream>
#include <ctime>
using namespace std;

int biased_random(int p) // 1的概率为 p%
{
    if (rand() % 100 < p)
        return 1;
    else
        return 0;
}

int random_01(int p)
{
    int x, y;
    while (true)
    {
        x = biased_random(p);
        y = biased_random(p);
        if (x != y)
            return x;
    }
}

int main()
{
    srand(time(NULL));
    int test[4] = {11, 33, 77, 99};

    for (int i = 0; i < 4; i++)
    {
        int a[2][2] = {};
        int j = 100000;
        while (j--)
        {
            a[0][biased_random(test[i])]++;
            a[1][random_01(test[i])]++;
        }
        printf("%6d%6d    %6d%6d\n", a[0][0], a[0][1], a[1][0], a[1][1]);
    }
    return 0;
}