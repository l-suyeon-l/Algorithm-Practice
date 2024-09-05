#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long LongInt;
int cnt = 0;

LongInt fib(LongInt n);

int main(void)
{
	LongInt n;
	scanf("%llu", &n);
	if (n >= 0 && n <= 30) {
        printf("%llu", fib(n));
        printf("\n%d", cnt);
    }
	return 0;
}

LongInt fib(LongInt n)
{
	cnt++;
	if (n <= 1)
		return n;
	else return (fib(n - 1) + fib(n - 2)) % 1000000;
}