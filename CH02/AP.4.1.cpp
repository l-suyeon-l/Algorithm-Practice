#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int threshold, cnt = 0;   // matrixmult와 strassen 인자에서 제거함
typedef vector<vector<int>> matrix_t;
void print_matrix(int n, matrix_t& mat);
void resize(int n, matrix_t& mat);
void madd(int n, matrix_t A, matrix_t B, matrix_t& C);
void msub(int n, matrix_t A, matrix_t B, matrix_t& C);
void matrixmult(int n, matrix_t A, matrix_t B, matrix_t& C);
void partition(int m, matrix_t M, matrix_t& M11, matrix_t& M12, matrix_t& M21, matrix_t& M22);
void combine(int m, matrix_t& M, matrix_t M11, matrix_t M12, matrix_t M21, matrix_t M22);
void strassen(int n, matrix_t A, matrix_t B, matrix_t& C);


int main(void)
{
    int origin, n, k = 1, itg = 1;
    scanf("%d %d", &n, &threshold); //n, threshold 값 스캔
    origin = n;
    while (k < n) {
        k *= 2;
    }
    n = k;
    matrix_t A(n+1, vector<int>(n+1));
    matrix_t B(n+1, vector<int>(n+1));
    matrix_t C(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {  // A, B, C 함수 0으로 초기화
        for (int j = 1; j <= n; j++) {
            A[i][j] = 0; B[i][j] = 0; C[i][j] = 0;
        }
    }
    for (int i = 1; i <= origin; i++) {  // 정방행렬 A scanf
        for (int j = 1; j <= origin; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 1; i <= origin; i++) {  // 정방행렬 B scanf
        for (int j = 1; j <= origin; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    
    strassen(n, A, B, C);
    printf("%d\n", cnt);
    print_matrix(origin, C);
}

void print_matrix(int n, matrix_t& mat)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d", mat[i][j]);
            if (j != n)
                printf(" ");
        }
        if (i != n)
            printf("\n");
    }
}

void resize(int n, matrix_t& mat)
{
    mat.resize(n+1, vector<int>(n+1, 0));
}

void madd(int n, matrix_t A, matrix_t B, matrix_t& C)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void msub(int n, matrix_t A, matrix_t B, matrix_t& C)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void matrixmult(int n, matrix_t A, matrix_t B, matrix_t& C)
{
    int idx, sum;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sum = 0;
            for (int k = 1; k <= n; k++) {
                idx = A[i][k] * B[k][j];
                sum = sum + idx;
            }
            C[i][j] = sum;
        }
    }
    
}

void partition(int m, matrix_t M, matrix_t& M11, matrix_t& M12, matrix_t& M21, matrix_t& M22)
{
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            M11[i][j] = M[i][j];
            M12[i][j] = M[i][j+m];
            M21[i][j] = M[i+m][j];
            M22[i][j] = M[i+m][j+m];
        }
    }
}

void combine(int m, matrix_t& M, matrix_t M11, matrix_t M12, matrix_t M21, matrix_t M22)
{
    for (int i = 1; i <= m; i++) {
        for (int j = 1;  j <= m; j++) {
            M[i][j] = M11[i][j];
            M[i][j+m] = M12[i][j];
            M[i+m][j] = M21[i][j];
            M[i+m][j+m] = M22[i][j];
        }
    }
}

void strassen(int n, matrix_t A, matrix_t B, matrix_t& C)
{
    cnt++;
    if (n <= threshold) {
        matrixmult(n, A, B, C);
    }
    else {
        int m = n / 2;  // 본 행렬의 크기에서 2를 나눈 지역변수 m
        matrix_t A11, A12, A21, A22, B11, B12, B21, B22, C11, C12, C21, C22, M1, M2, M3, M4, M5, M6, M7, L, R;
        resize(n, A11); resize(n, A12); resize(n, A21); resize(n, A22); 
        resize(n, B11); resize(n, B12); resize(n, B21); resize(n, B22); 
        resize(n, C11); resize(n, C12); resize(n, C21); resize(n, C22); 
        resize(n, M1); resize(n, M2); resize(n, M3); resize(n, M4); resize(n, M5); resize(n, M6); resize(n, M7);
        resize(n, L); resize(n, R);

        partition(m, A, A11, A12, A21, A22);
        partition(m, B, B11, B12, B21, B22);

        /*M1*/ madd(m, A11, A22, L); madd(m, B11, B22, R); strassen(m, L, R, M1);
        /*M2*/ madd(m, A21, A22, L); strassen(m, L, B11, M2);
        /*M3*/ msub(m, B12, B22, R); strassen(m, A11, R, M3);
        /*M4*/ msub(m, B21, B11, R); strassen(m, A22, R, M4);
        /*M5*/ madd(m, A11, A12, L); strassen(m, L, B22, M5);
        /*M6*/ msub(m, A21, A11, L); madd(m, B11, B12, R); strassen(m, L, R, M6);
        /*M7*/ msub(m, A12, A22, L); madd(m, B21, B22, R); strassen(m, L, R, M7);

        /*C11*/ madd(m, M1, M4, L); msub(m, L, M5, R); madd(m, R, M7, C11);
        /*C12*/ madd(m, M3, M5, C12);
        /*C21*/ madd(m, M2, M4, C21);
        /*C22*/ madd(m, M1, M3, L); msub(m, L, M2, R); madd(m, R, M6, C22);
        
        combine(m, C, C11, C12, C21, C22);
    }
}