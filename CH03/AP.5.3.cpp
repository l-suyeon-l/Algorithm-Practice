#include <iostream>
#include <vector>
#include <algorithm>
#define INF 999

using namespace std;

typedef vector<vector<int>> matrix_t;
void floyd2(int n, matrix_t& W, matrix_t& D, matrix_t& P);
void path(matrix_t& P, int u, int v, vector<int>& p);

int main(void)
{
    int n, m, T, u, v, w;
    vector<int> p;
    matrix_t W, D, P, route;

    scanf("%d %d", &n, &m);
    W.resize(n + 1, vector<int>(n + 1, INF));
    D.resize(n + 1, vector<int>(n + 1, INF));
    P.resize(n + 1, vector<int>(n + 1, INF));

    for (int i = 1; i <= n; i++) {
        W[i][i] = 0;
        D[i][i] = 0;
        P[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        W[u][v] = w;
    }

    scanf("%d", &T);
    route.resize(T + 1, vector<int>(2, 0));
    for (int i = 1; i <= T; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &route[i][j]);
        }
    }

    floyd2(n, W, D, P);                 // 인접행렬 D, P 정리
    for (int i = 1; i <= n; i++) {      // D 출력
        for (int j = 1; j <= n; j++) {
            printf("%d", D[i][j]);
            if (j != n)
                printf(" ");
        }
        printf("\n");
    }
    for (int i = 1; i <= n; i++) {      // P 출력
        for (int j = 1; j <= n; j++) {
            printf("%d", P[i][j]);
            if (j != n)
                printf(" ");
        }
        printf("\n");
    }

    for (int i = 1; i <= T; i++) {
        if (D[route[i][0]][route[i][1]] == INF)
            printf("NONE");
        else {
            p.resize(0);
            path(P, route[i][0], route[i][1], p);

            if (p.empty())
                printf("%d %d", route[i][0], route[i][1]);
            else {
                printf("%d ", route[i][0]);
                while (!p.empty()) {
                    printf("%d ", p.front());
                    p.erase(p.begin());
                }
                printf("%d", route[i][1]);
            }
        }
        if (i != T)
            printf("\n");
    }
    return 0;
}

void floyd2(int n, matrix_t& W, matrix_t& D, matrix_t& P)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            D[i][j] = W[i][j];
            P[i][j] = 0;
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }
}

void path(matrix_t& P, int u, int v, vector<int>& p)
{
    int k = P[u][v];
    if (k != 0) {
        path(P, u, k, p);
        p.push_back(k);
        path(P, k, v, p);
    }
}