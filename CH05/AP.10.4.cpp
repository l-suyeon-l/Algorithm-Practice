#include <iostream>
#include <vector>

using namespace std;

int n, cnt = 0;
vector<int> vindex;         // 해당 vertex의 방문 번째
vector<vector<bool>> W;     // vertex 방문 여부

bool promising(int i);
void hamiltonian(int i);

int main(void)
{
    int m, a, b;
    cin >> n >> m;                  // n : 정점의 개수, m : 간선의 개수
    vindex.resize(n + 1);
    W.resize(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; i++){
        cin >> a >> b;              // 간선이 연결된 정점 입력받기
        W[a][b] = W[b][a] = true;   // 무방향 그래프의 adjacent matrix
    }

    vindex[0] = 1;                  // 0번째로 방문한 vertex 1
    hamiltonian(0);

    cout << cnt;

    return 0;
}

void hamiltonian(int i)
{
    int j;
    
    if (promising(i)) {
        if (i == n - 1)                 // 왜 n이 아니라 n-1? 방문 번째는 0~n-1까지이기 때문이다
            cnt++;                      // n-1번째로 도착한 정점이 promising하다면 회로 개수 cnt(전역 변수)
        else
            for (j = 2; j <= n; j++) {  // 출발 정점이 1이므로 2부터 시작
                vindex[i + 1] = j;      // i + 1번째로 방문한 vertex j
                hamiltonian(i + 1);     // hamiltonian 재귀호출 (vindex[i+1] = j일 때 이하의 node가 전부 nonpromising이라면 윗노드로 올라감 : pruning)
            }
    }
}

bool promising(int i)
{
    int j;
    bool flag;
    if (i == n - 1 && !W[vindex[n - 1]][vindex[0]]) // 현재 n-1 vertex(마지막 정점) && n-1번째 방문한 정점과 0번째 방문한 정점이 연결되어 있지 않다면
        flag = false;
    else if (i > 0 && !W[vindex[i - 1]][vindex[i]]) // i가 0보다 큼 && i-1번째 방문한 정점과 i번째 방문한 정점이 연결되어 있지 않다면
        flag = false;
    else {
        flag = true;
        j = 1;
        while (j < i && flag) {                     // 현재 방문(i)과 이전 방문(j) 비교
            if (vindex[i] == vindex[j])             // 현재 방문한(i) 정점과 이전에 방문한(j) 정점이 같다면 hamiltonian이 아님(첫번째 정점 외에는 한 번만 방문)
                flag = false;
            j++;
        }
    }
    return flag;
}