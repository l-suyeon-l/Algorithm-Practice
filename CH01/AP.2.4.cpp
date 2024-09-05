#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>

using namespace std;

typedef long long long_t;

long_t fun(long_t n) {
    int rst=(log2(n)/2)+1;
    return pow(8, rst);
}

int main() {
    long_t n;
    scanf("%lld", &n);
    printf("%lld", fun(n));
}