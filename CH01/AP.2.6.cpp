#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int cnt;
int Collatz(unsigned int n);
int Collatzprint(unsigned int n);

int main(void)
{
    unsigned int a, b, n, m;
    vector<int> S(1000000);
    scanf("%u %u", &n, &m);
    for (int i = n; i <= m; i++){
        cnt = 0;
        Collatz(i);
        S[i] = cnt;
    }
    b = S[n];
    for (int i = n; i <= m; i++){
        if (b <= S[i]){
            b = S[i];
            a = i;
        }
    }
    printf("%u %u\n", a, b-1);
    Collatzprint(a);

    return 0;
}

int Collatz(unsigned int n)
{
    cnt++;
    long long num = n;

    if (num==1)
        return 1;
    else {
        if (num%2==0)
            return Collatz(num/2);
        else
            return Collatz(3*num+1);
    }
}

int Collatzprint(unsigned int n)
{
    long long num = n;

    printf("%d ", num);
    if (num==1)
        return 1;
    else {
        if (num%2==0)
            return Collatzprint(num/2);
        else
            return Collatzprint(3*num+1);
    }
}