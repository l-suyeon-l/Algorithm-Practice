#include <iostream>
#include <vector>
#include <cmath>
#define INF 999999

using namespace std;

typedef vector<vector<int>> matrix_t;

int count(int A);
bool isIn(int i, int A);
int diff(int A, int j);
int minimum(int n, int i, int &minJ, int A, matrix_t& W, matrix_t& D);
void travel(int n, matrix_t& W, matrix_t& D, matrix_t& P, int &minlength);
void tour(int v, int A, matrix_t& P);

int main(void)
{
    int n, m, u, v, w, minlength;
    matrix_t W, D, P;

    cin >> n >> m;  // n : 그래프의 정점 개수, m : 그래프의 간선 개수
    W.resize(n + 1, vector<int>(n + 1, INF));
    D.resize(n + 1, vector<int>(pow(2, n - 1), INF));   // 
    P.resize(n + 1, vector<int>(pow(2, n - 1), INF));   // INF로 초기화

    for (int i = 1; i <= n; i++)
        W[i][i] = 0;                // 인접매트릭스 대각선(vi -> vi) 0으로 초기화
    
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;         // 정점 u, v 가중치 w
        W[u][v] = w;                // directed graph이므로 u->v에만 w저장
    }

    travel(n, W, D, P, minlength);
    cout << minlength << "\n";      // 최단경로 값 출력

    cout << "1 ";
    tour(1, pow(2, n - 1) - 1, P);                  // A는 0부터 시작하므로 pow() - 1 해줘야 함
    for (int i = 1; i <= n; i++)                    // D의 row 수
        for (int j = 0; j < pow(2, n - 1); j++)     // D의 column 수
            if (D[i][j] != INF)                     // v1 -> vi -> A -> v1 경로가 있다면(무한대가 아니면)
                cout << i << " " << j << " " << D[i][j] << "\n";    // vi와 j(A의 번호 값) 출력 후 해당 값들의 최소경로 출력

    return 0;
}

int count(int A)    // 부분집합 A의 원소 개수 cnt
{
    int cnt = 0;
    for (; A != 0; A >>= 1)
        if (A & 1) cnt++;
    return cnt;
}

bool isIn(int i, int A) // vertex i가 부분집합 A에 포함되어 있는지 아닌지
{
    return (A & (1 << (i - 2))) != 0;   // 포함되어 있으면 return (포함 안되어 있으면 0값이 나옴)
}

int diff(int A, int j)  // 부분집합 A에서 vertex j 제거
{
    return (A & ~(1 << (j - 2)));   // vertex j가 제거된 A return
}

int minimum(int n, int i, int &minJ, int A, matrix_t& W, matrix_t& D)
{
    int minV = INF;
    for (int j = 2; j <= n; j++) {                  // vertex 2 ~ n까지
        if (!isIn(j, A)) continue;                  // vj가 A에 없다면 continue
        int value = W[i][j] + D[j][diff(A, j)];     // vi -> vj -> (vj를 뺀 부분집합 A)
        if (minV > value) {                         // vertex j에 따른 value가 minV보다 작다면
            minV = value;                           // minV 초기화
            minJ = j;                               // 그 때의 vj 번호를 minJ에 기록
        }
    }
    return minV;
}

void travel(int n, matrix_t& W, matrix_t& D, matrix_t& P, int &minlength)
{
    int i, j, k, A;

    int subset_size = pow(2, n - 1);    // 가능한 vertex의 부분집합은 총 2^(n-1)개 (v1은 제외)
    for (i = 2; i <= n; i++)
        D[i][0] = W[i][1];              // vi -> A(공집합) -> v1 == W[i][1]
    for (k = 1; k <= n - 2; k++)
        for (A = 0; A < subset_size; A++) {             // 모든 부분집합(A=0 ~ subset_size) 탐색
            if (count(A) != k)  continue;               // A의 원소 개수가 k개가 아니면 continue
            for (i = 2; i <= n; i++) {                  // vertex 2 ~ n까지
                if (isIn(i, A)) continue;               // vi가 A에 있다면 continue (vi->A를 구해야하기 때문에 A에 있으면 안됨)
                D[i][A] = minimum(n, i, j, A, W, D);    // vi -> A -> v1로 가는 최소거리
                P[i][A] = j;                            // j : minimum함수에서 찾은 최단경로에서 부분집합 A의 첫번째 도달 정점
            }
        }
    A = subset_size - 1;                    // v1을 제외한 모든 정점이 있는 부분집합
    D[1][A] = minimum(n, 1, j, A, W, D);    // v1 -> A -> v1로 가는 최소거리
    P[1][A] = j;                            // v1 -> vj (j는 첫번째 도달 정점)
    minlength = D[1][A];
}

void tour(int v, int A, matrix_t& P)    // 최단경로 순서 출력
{
    int k = P[v][A];                // k = vertex v -> A일 때 A에서 첫번째로 도달하는 vertex 번호
    if (A == 0)                     // A에 원소가 없다면 이동할 vertex가 없음 -> v1으로 이동(starting vertex)
        cout << "1" << "\n";
    else {                          
        cout << k << " ";           // vertex v 다음 vertex k 출력
        tour(k, diff(A, k), P);     // A에서 vertex k를 뺀 후 tour 재귀호출
    }
}