#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix_t;

void matrixmult(int n, matrix_t A, matrix_t B, matrix_t& C)
{
    int idx, sum;
    for (int a = 1; a <= n; a++) {
        for (int b = 1; b <= n; b++) {
            sum = 0;
            for (int i = 1; i <= n; i++) {
                idx = A[a][i] * B[i][b];
                sum = sum + idx;
            }
            C[a][b] = sum;
        }
    }
}

void matrixread(int n, matrix_t& M) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &M[i][j]);
}

int main() {
    int n;
    scanf("%d", &n);
 
    matrix_t A(n+1, vector<int>(n+1));
    matrixread(n, A);
    matrix_t B(n+1, vector<int>(n+1));
    matrixread(n, B);
    matrix_t C(n+1, vector<int>(n+1));
    matrixmult(n, A, B, C);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (j < n)
                printf("%d ", C[i][j]);
            else
                printf("%d\n", C[i][j]);
}