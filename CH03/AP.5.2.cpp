#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int bin(int n, int k);

int main(void)
{
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d", bin(n, k));
}

int bin(int n, int k)
{
    int temp, temp2;
    vector<int> B(n + 1);
    if (k > n / 2)
        k = n - k;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0;  j <= min(i, k); j++) {
            if ((j == 0) || (j == n)) {
                B[j] = 1;
                temp = 1;
            }
            else {
                temp2 = B[j];
                B[j] = (B[j] + temp) % 10007;
                temp = temp2;
            }
        }
    }
    return B[k];
}