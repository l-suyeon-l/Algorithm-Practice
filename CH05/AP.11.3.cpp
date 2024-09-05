#include <iostream>
#include <vector>

using namespace std;

int n, m, T, cnt = 0;
vector<int> row, col, vindex;
vector<bool> visited;
vector<bool> W;

int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};    // knight가 움직일 수 있는 행
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};    // knight가 움직일 수 있는 열

void hamiltonian(int i);
bool promising(int i);
int KnightTour(int pos, int count);

int main() {
    cin >> n >> m;                  // n : 행의 크기, m : 열의 크기
    cin >> T;                       // T : 출발정점의 개수
    row.resize(T);
    col.resize(T);
    visited.resize(n * m, false);   // 해밀턴 경로 : 방문 여부

    for (int i = 0; i < T; i++)
        cin >> row[i] >> col[i];    // T개의 출발정점 위치(row, col) 입력받기

    vindex.resize(n * m);
    W.resize(n * m * n * m, false);     // 시간복잡도를 줄이기 위해 W를 1차원 벡터로 생성

    for (int i = 0; i < n * m; i++) {   // W : knight가 이동할 수 있는 통로 유무
        int x = i / m;                  // x : i번째 칸의 행
        int y = i % m;                  // y : i번째 칸의 열

        for (int j = 0; j < 8; j++) {   // 8방향 중 j번째 방향
            int nx = x + dx[j];         // nx : i번째 칸에서 움직일 수 있는 j번째 행
            int ny = y + dy[j];         // ny : i번째 칸에서 움직일 수 있는 j번째 열

            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {   // nx와 ny가 체스보드 내에 존재한다면
                int nextV = nx * m + ny;                    // nextV : j번째 방향으로 움직여서 도착한 칸
                W[i * n * m + nextV] = true;                // 현재 칸(i)에서 이동 가능한 칸(nextV)으로 가는 간선
                W[nextV * n * m + i] = true;                // 이동 가능한 칸(nextV)에서 현재 칸(i)으로 가는 간선
            }
        }
    }

    vindex[0] = 0;              // 0번째로 방문한 vertex 0
    hamiltonian(0);
    cout << cnt << "\n";        // 해밀턴 회로 개수 출력

    for (int i = 0; i < T; i++) {
        int pos = row[i] * m + col[i];      // pos : 입력받은 row와 col에 대해 현재 칸 위치 계산
        visited[pos] = true;                // 현재 칸에 방문했다고 기록 (root 노드)
        cout << KnightTour(pos, 1) << "\n"; // KnightTour 실행
        visited[pos] = false;               // 다음 row, col을 위해 root 노드 방문 기록 삭제
    }

    return 0;
}

void hamiltonian(int i) {
    int j;

    if (promising(i)) {
        if (i == n * m - 1)                 // 방문번째는 0 ~ n*m-1까지이기 때문이다
            cnt++;                          // 마지막 칸에 도착하면 cnt++ (해밀턴 회로를 찾음)
        else {
            for (j = 1; j < n * m; j++) {   // 출발 정점이 0이므로 1부터 시작
                vindex[i + 1] = j;          // i + 1번째로 방문한 vertex j
                hamiltonian(i + 1);         // hamiltonian 재귀호출 (vindex[i+1] = j일 때 이하의 node가 전부 nonpromising이라면 윗노드로 올라감)
            }
        }
    }
}

bool promising(int i) {
    if (i == n * m - 1 && !W[vindex[n * m - 1] * n * m + vindex[0]])    // 현재 n*m-1번 칸(마지막 칸) && n*m-1번째 방문한 칸과 0번째 방문한 칸이 연결되어 있지 않다면
        return false;
    else if (i > 0 && !W[vindex[i - 1] * n * m + vindex[i]])            // i가 0보다 큼(첫번째 방문한 칸 제외) & i-1번째 방문한 정점과 i번째 방문한 정점이 연결되어 있지 않다면
        return false;
    else {          
        for (int j = 1; j < i; j++) {       // 현재 방문(i)과 이전 방문(j) 비교
            if (vindex[i] == vindex[j])     // 현재 방문한(i) 정점과 이전에 방문한(j) 정점이 같다면 hamiltonian이 아님(첫번재 정점 외에는 한 번만 방문)
                return false;
        }
    }
    return true;
}

int KnightTour(int pos, int count) {
    if (count == n * m)     // 모든 칸에 방문했다면
        return 1;

    int pCnt = 0;
    for (int i = 0; i < 8; i++) {       // 8개의 방향
        int nRow = pos / m + dx[i];     // nRow : 현재 위치의 행에서 i번째 방향으로 행 이동
        int nCol = pos % m + dy[i];     // nCol : 현재 위치의 행에서 i번째 방향으로 열 이동
        int nPos = nRow * m + nCol;     // nPos : i번째 방향으로 이동한 칸의 위치(공식 사용)

        if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && !visited[nPos]) { // nRow와 nCol이 체스 보드 내에 존재 && 현재 칸에 방문한 적이 없다면
            visited[nPos] = true;                                               // 현재 칸에 방문 기록
            pCnt += KnightTour(nPos, count + 1);                                // 경로가 존재하면 1 리턴, 아니면 0 리턴
            visited[nPos] = false;                                              // 재귀호출 후 현재 위치로 돌아와서 방문 초기화, i+1번째 방향으로 다시 진행
        }
    }
    return pCnt;
}