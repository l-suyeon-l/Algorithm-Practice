#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int Collatz(unsigned int n);

int main(void)
{
    unsigned int n;
    scanf("%u", &n);
    Collatz(n);

    return 0;
}

int Collatz(unsigned int n)
{
    long long num = n;

    printf("%d ", num);
    if (num==1)
        return 1;
    else {
        if (num%2==0)
            return Collatz(num/2);
        else
            return Collatz(3*num+1);
    }
}