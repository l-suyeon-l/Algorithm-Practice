#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void binsearch(int n, vector<int> S, int x, int& location);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> S(n+1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);
    sort(S.begin() + 1, S.end());
    while (m--) {
        int x, location;
        scanf("%d", &x);
        binsearch(n, S, x, location);
        if (location > 0)
            printf("%d is in %d.\n", x, location);
        else
            printf("%d is not in S.\n", x);
    }
}

void binsearch(int n, vector<int> S, int x, int& location)
{
    location = 0;
    int first = 1, middle, last = n;
    while (first <= last && location == 0) {
        middle = (first + last) / 2;
        if (middle == 0) return; //없어도 while문 탈출

        if (S[middle] > x)
            last = middle - 1;
        else if (S[middle] < x)
            first = middle + 1;
        else { //S[middle] == x
            location = middle;
        }
    }
}