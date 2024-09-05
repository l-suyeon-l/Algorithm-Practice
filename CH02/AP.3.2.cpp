#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;
void mergesort(int n, vector<int>& S);
void merge(int h, int m, vector<int> U, vector<int> V, vector<int>& S);

int main(void)
{
    int n, i;
    scanf("%d", &n);
    vector<int> S(n+1);
    for (i=1; i<=n; i++)
        scanf("%d", &S[i]);
    mergesort(n, S);
    for (i=1; i<=n; i++) {
        printf("%d", S[i]);
        if (i != n)
            printf(" ");
    }
    printf("\n%d", cnt);
}

void mergesort(int n, vector<int>& S)
{
    if (n > 1){
        int h = n / 2, m = n - h;
        vector<int> U(h+1), V(m+1);
        cnt += h + m;
        for (int i = 1; i <= h; i++)
            U[i] = S[i];
        for (int i = h+1; i <= n; i++)
            V[i - h] = S[i];
        mergesort(h, U);
        mergesort(m, V);
        merge(h, m, U, V, S);
    }
}

void merge(int h, int m, vector<int> U, vector<int> V, vector<int>& S)
{
    int i = 1, j = 1, k = 1;
    while(i <= h && j <= m)
        S[k++] = (U[i] < V[j]) ? U[i++] : V[j++];
    if (i > h){
        while (j <= m)
            S[k++] = V[j++];
    }
    else {
        while (i <= h)
            S[k++] = U[i++];
    }
}