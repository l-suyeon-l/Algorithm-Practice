#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int sum(int n, vector<int> S);

int main() {
    int n;
    scanf("%d", &n);
    vector<int> S(n+1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);
    printf("%d", sum(n, S));
}

int sum(int n, vector<int> S) {
   int rst = 0;
    for (int i = 1; i <= n; i++){
        rst = rst + S[i];
    }
    return rst;
}