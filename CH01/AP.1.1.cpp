#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

void seqsearch(int n, vector<int> S, int x, int& location);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> S(n+1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);
    while (m--) {
        int x, location;
        scanf("%d", &x);
        seqsearch(n, S, x, location);
        if (location > 0)
            printf("%d is in %d.\n", x, location);
        else
            printf("%d is not in S.\n", x);
    }
}

void seqsearch(int n, vector<int> S, int x, int& location) {
   location = 1;
  while(location <= n && S[location] != x)
    location++;
  if (location > n)
    location = 0;
}