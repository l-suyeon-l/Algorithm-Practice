#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;
void mergesort2(int low, int high, vector<int>& S);
void merge2(int low, int mid, int high, vector<int>& S);

int main(void)
{
    int n, i, low, high;
    scanf("%d", &n);
    low = 1; high = n;
    vector<int> S(n+1);
    for (i=1; i<=n; i++)
        scanf("%d", &S[i]);
    mergesort2(low, high, S);
    for (i = 1; i <= n; i++) {
        printf("%d", S[i]);
        if (i != n)
            printf(" ");
    }
    printf("\n%d", cnt);
}

void mergesort2(int low, int high, vector<int>& S)
{
    if (low < high) {
        int mid = (low + high) / 2;
        mergesort2(low, mid, S);
        mergesort2(mid + 1, high, S);
        merge2(low, mid, high, S);
    }
}

void merge2(int low, int mid, int high, vector<int>& S)
{
    int i = low, j = mid + 1, k = 0;
    vector<int> U(high - low + 1);

    while (i <= mid && j <= high) {
        U[k++] = (S[i] < S[j]) ? S[i++] : S[j++];
        cnt++;
    }

    if (i > mid)
        while (j <= high) U[k++] = S[j++];
    else
        while (i <= mid) U[k++] = S[i++];

    for (int t = low; t <= high; t++)
        S[t] = U[t - low];
}