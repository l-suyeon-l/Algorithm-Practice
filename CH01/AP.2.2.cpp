#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>

using namespace std;

typedef long long long_t;

long_t fun(long_t n, long_t m, long_t p) {
    return ((n+1)/2)*(log2(m)+2)*(log2(p)+3);
}

int main() {
    long_t n, m, p;
    scanf("%lld %lld %lld", &n, &m, &p);
    printf("%lld", fun(n, m, p));
}