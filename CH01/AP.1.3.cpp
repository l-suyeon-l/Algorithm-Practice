#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

void exchange(int n, vector<int>& S);

int main() {
    int n;
    scanf("%d", &n);
    vector<int> S(n+1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);
    exchange(n, S);
    for (int i = 1; i <= n; i++)
        if (i < n)
            printf("%d ", S[i]);
        else
            printf("%d\n", S[i]);
}

void exchange(int n, vector<int>& S)
{
    int temp;
    for (int i=1; i<=n; i++){
        for (int j=i+1; j<=n; j++){
            if (S[i]>S[j]){
                temp=S[i];
                S[i]=S[j];
                S[j]=temp;
            }
        }
    }
}