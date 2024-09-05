#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
unsigned int x;
int location, mid;

int binsearch2(int low, int high, vector<int>& S);

int main(void)
{
    unsigned int n, m;
    int low, high;

    scanf("%u %u", &n, &m);
    low = 1, high = n;
    vector<int> S(n+1);

    for (int i=1; i<=n; i++)
        scanf("%d", &S[i]);
    sort(S.begin(), S.end());

    for (int j=1; j<=m; j++) {
        scanf("%d", &x);
        location=0;
        printf("%d %d\n", location, binsearch2(low, high, S));
    }


}

int binsearch2(int low, int high, vector<int>& S)
{
    location++;

    if (low > high)
        return 0;
    else {
        mid = (low + high) / 2;
        if (x == S[mid])
            return mid;
        else if (x < S[mid])
            return binsearch2(low, mid - 1, S);
        else // x > S[mid]
            return binsearch2(mid + 1, high, S);
    }
}