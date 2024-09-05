#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define INF 999999

using namespace std;

typedef vector<vector<int>> matrix_t;
string s;
int minimum(int i, int j, int& mink, vector<int>& d, matrix_t& M);
void minmult(int n, vector<int>& d, matrix_t& M, matrix_t& P);
void order(int i, int j, matrix_t& P, string& s);

int main(void)
{
    int n;
    scanf("%d", &n);
    vector<int> d(n + 1);
    for (int i = 0; i <= n; i++)
        scanf("%d", &d[i]);
    
    matrix_t P(n + 1, vector<int>(n + 1)), M(n + 1, vector<int>(n + 1));
    
    minmult(n, d, M, P);

    for (int i = 1; i <= n; i++) {      // 행렬 M 출력
        for (int j = i; j <= n; j++) {
            printf("%d", M[i][j]);
            if (j != n)
                printf(" ");
        }
        if (i != n)
            printf("\n");
    }
    printf("\n");
    for (int i = 1; i <= n; i++) {      // 행렬 P 출력
        for (int j = i; j <= n; j++) {
            printf("%d", P[i][j]);
            if (j != n)
                printf(" ");
        }
        if (i != n)
            printf("\n");
    }
    printf("\n");
    printf("%d", M[1][n]);
    printf("\n");
    cout<<s;
}

int minimum(int i, int j, int& mink, vector<int>& d, matrix_t& M)
{
    int minValue = INF, value;
    for (int k = i; k <= j - 1; k++) {
        value = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
        if (minValue > value) {
            minValue = value;
            mink = k;
        }
    }
    return minValue;
}

void minmult(int n, vector<int>& d, matrix_t& M, matrix_t& P)
{
    int i, j, k, diagonal;
    for (i = 1; i <= n; i++)
        M[i][i] = 0;
    for (diagonal = 1; diagonal <= n - 1; diagonal++)
        for (i = 1; i <= n - diagonal; i++) {
            j = i + diagonal;
            M[i][j] = minimum(i, j, k, d, M);
            P[i][j] = k;
        }

    order(i - 1, j, P, s);
}

void order(int i, int j, matrix_t& P, string& s)
{
    if (i == j) {
        s += string("(");
        s += string("A") + to_string(i);
        s += string(")");
    }
    else {
        int k = P[i][j];
        s += string("(");
        order(i, k, P, s);
        order(k + 1, j, P, s);
        s += string(")");
    }
}