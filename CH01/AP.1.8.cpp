#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std; //이거 왜?

int main(void)
{
	int n;
	scanf("%d", &n);
	vector<int> S(n + 1);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &S[i]);
	}
	sort(S.begin() + 1, S.end()); //배열.begin은 0을 가리킴

	printf("%d %d %d", S[1], S[(n+1) / 2], S[n]);
	//n이 짝수일 때 홀수일 때 둘 다 해보기. 중앙값이 n/2인지 (n+1)/2인지 생각해보기
}