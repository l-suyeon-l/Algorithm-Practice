#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> matrix;
matrix DP;
int cnt = 0;

int bin(int n, int k);

int main(void)
{
    int n, k;
    scanf("%d %d", &n, &k);
    DP.resize(1001, vector<int>(1001, -1));
    printf("%d\n", bin(n , k));
    printf("%d", cnt);
}

int bin(int n, int k)
{
    cnt++;
    if (k == 0 || n == k)
        DP[n][k] = 1;
    else if (DP[n][k] == -1)
        DP[n][k] = (bin(n - 1, k) + bin(n - 1, k - 1)) % 10007;

    return DP[n][k];
}