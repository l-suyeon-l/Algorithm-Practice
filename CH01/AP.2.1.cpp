#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long long_t;

long_t fun(long_t n) {
    return 2*pow(n,2);
}

int main() {
    long_t n;
    scanf("%lld", &n);
    printf("%lld", fun(n));
}