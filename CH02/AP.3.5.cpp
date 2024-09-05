#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
typedef vector<vector<int>> matrix_t;
matrix_t ivltion(int b, matrix_t A);
matrix_t matrixmult(matrix_t A, matrix_t B);

int main(void)
{
    int b;
    scanf("%d %d", &n, &b);
    matrix_t A(n+1, vector<int>(n+1));
    matrix_t Z(n+1, vector<int>(n+1));
    for (int i=1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &A[i][j]);
    
    Z = ivltion(b, A);
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            printf("%d", Z[i][j]);
            if (j != n)
                printf(" ");
        }
        if (i != n)
            printf("\n");
    }
}

matrix_t ivltion(int b, matrix_t A)
{
    if (b == 1)
        return A;
    else if (b % 2 == 0) {
        return matrixmult(ivltion(b/2, A), ivltion(b/2, A));
    }
    else if (b % 2 == 1) {
        return matrixmult(ivltion(1, A), ivltion(b-1, A));
    }
}

matrix_t matrixmult(matrix_t A, matrix_t B)
{
    int idx, sum;
    matrix_t Z(n+1, vector<int>(n+1));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            sum = 0;
            for (int k=1; k<=n; k++) {
                idx = (A[i][k] % 1000) * (B[k][j] % 1000);
                sum = sum + (idx % 1000);
            }
            Z[i][j] = (sum % 1000);
        }
    }
    return Z;
}