#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cnt = 0;
void quicksort(int low, int high, vector<int>& S);
void partition(int low, int high, int& pivotpoint, vector<int>& S);

int main(void)
{
    int n, i, low, high;
    scanf("%d", &n);
    low = 1; high = n;
    vector<int> S(n + 1);
    for (i = 1; i <= n; i++)
        scanf("%d", &S[i]);
    quicksort(low, high, S);

    for (i = 1; i <= n; i++) {
        printf("%d", S[i]);
        if (i != n)
            printf(" ");
    }
    printf("\n%d", cnt);
}

void quicksort(int low, int high, vector<int>& S)
{
    int pivotpoint;

    if (low < high) {
        partition(low, high, pivotpoint, S);
        quicksort(low, pivotpoint - 1, S);
        quicksort(pivotpoint + 1, high, S);
    }
}

void partition(int low, int high, int& pivotpoint, vector<int>& S)
{
    int i, j, pivotitem;

    pivotitem = S[low];
    j = low;
    for (i = low + 1; i <= high; i++) {
        if (S[i] < pivotitem) {
            j++;
            swap(S[i], S[j]);
            cnt++;
        }
    }
    pivotpoint = j;
    swap(S[low], S[pivotpoint]);
    cnt++;
}