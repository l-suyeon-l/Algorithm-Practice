#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
typedef unsigned long long LongInt;
int F[1000000] = { 0 };

LongInt fib2(int n);

int main(void)
{
	int n;
	F[0] = 0; F[1] = 1;
	scanf("%d", &n);
	printf("%llu", fib2(n));
}

LongInt fib2(int n)
{
	if (n <= 1) return F[n];
	else {
		for (int i = 2; i <= n; i++)
			F[i] = (F[i - 1] + F[i - 2]) % 1000000;
		return F[n];
	}
}