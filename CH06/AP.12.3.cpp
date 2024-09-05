#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define INF 999999

using namespace std;

typedef vector<int> ordered_set;
typedef struct node *node_pointer;
typedef struct node {
    int level;
    ordered_set path;
    int bound;
} nodetype;
struct compare {
    bool operator()(node_pointer u, node_pointer v) {
        if (u->bound > v->bound)
            return true;
        return false;
    }
};
typedef priority_queue<node_pointer, vector<node_pointer>, compare> priority_queue_of_node;
typedef vector<vector<int>> matrix_t;

int n;
matrix_t W;

int length(ordered_set path);
bool hasOutgoing(int v, ordered_set path);
bool hasIncoming(int v, ordered_set path);
int bound(node_pointer v);
bool isIn(int i, ordered_set A);
node_pointer create_node(int level, ordered_set path);
int remaining_vertex(ordered_set path);
void travel2(ordered_set &opttour, int &minlength);

int main(void)
{
    int m, u, v, w, minlength;
    ordered_set opttour;

    cin >> n >> m;
    W.resize(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; i++)
        W[i][i] = 0;
    
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        W[u][v] = w;
    }
    travel2(opttour, minlength);
    cout << minlength << "\n";
    for (int i = 0; i < opttour.size(); i++) {
        if (i != opttour.size() - 1)
            cout << opttour[i] << " ";
        else cout << opttour[i];
    }

    return 0;
}

int length(ordered_set path)    // path의 length 구하기
{
    vector<int>::iterator it;
    int len = 0;
    for (it = path.begin(); it != path.end(); it++) // path의 첫번째 원소부터 마지막 원소까지 (path.end()는 마지막 원소 다음 위치를 가리킴)
        if (it != path.end() - 1)                   // path의 마지막 원소가 아니면
            len += W[*it][*(it + 1)];               // W[현재 vertex][다음 vertex] 더하기
    return len;
}

bool hasOutgoing(int v, ordered_set path)   // vertex v가 path의 outgoing vertex인지
{
    vector<int>::iterator it;
    for (it = path.begin(); it != path.end() - 1; it++) // 마지막 원소는 outgoing vertex가 아니므로 제외
        if (*it == v) return true;
    return false;
}

bool hasIncoming(int v, ordered_set path)   // vertex v가 path의 incoming vertex인지
{
    vector<int>::iterator it;
    for (it = path.begin() + 1; it != path.end(); it++) // 첫번째 원소는 incoming vertex가 아니므로 제외
        if (*it == v) return true;
    return false;
}

int bound(node_pointer v)   // bound는 현재 경로에서 남은 vertex로 가는 거리 중 최단거리를 합한 값(갈 수 있는 vertex인지 상관없음)
{
    int lower = length(v->path);                // 처음 length를 lower bound로
    for (int i = 1; i <= n; i++) {              // i : outgoing vertex로 설정
        if (hasOutgoing(i, v->path)) continue;  // vi가 가리키는 vertex가 있다면
        int min = INF;                          // min을 INF로 초기화
        for (int j = 1; j <= n; j++) {          // j : incoming vertex로 설정
            if (i == j) continue;                                       // vi == vj 이면 안됨
            if (j == 1 && i == v->path[v->path.size() - 1]) continue;   // 현재 path의 마지막 원소는 v1으로 가지 못함 (마지막 v1은 자동할당)
            if (hasIncoming(j, v->path)) continue;                      // vj를 가리키는 vertex가 있다면
            // 위의 조건에 모두 해당하지 않으면
            if (min > W[i][j]) min = W[i][j];                           // 해당 vi와 vj의 가중치가 min보다 작으면 min으로 설정
        }
        lower += min;                                                   // outgoing vertex i의 최소거리를 lower에 더하기
    }
    return lower;
}

bool isIn(int v, ordered_set path)
{
    vector<int>::iterator it;
    for (it = path.begin(); it != path.end(); it++)
        if (*it == v) return true;
    return false;
}

node_pointer create_node(int level, ordered_set path)
{
    //node_pointer v = (node_pointer)malloc(sizeof(nodetype));
    node_pointer v = new nodetype;
    v->level = level;
    v->path.assign(path.begin(), path.end());
    return v;
}

void travel2(ordered_set &opttour, int &minlength)
{
    priority_queue_of_node PQ;
    node_pointer u, v;
    u = new nodetype;
    v = new nodetype;

    minlength = INF;
    v->level = 0; v->path.push_back(1); v->bound = bound(v);
    PQ.push(v);
    cout << v->level << " " << v->bound << " " << v->path[0] << "\n";
    while(!PQ.empty()) {
        v = PQ.top(); PQ.pop();
        if (v->bound < minlength) {
            for (int i = 2; i <= n; i++) {
                if (isIn(i, v->path)) continue;             // v->path에 vertex i가 이미 있으면(true) continue
                u = create_node(v->level + 1, v->path);     // 다음 level이 포함된 노드 생성
                u->path.push_back(i);                       // path에 vertex i 추가

                if (u->level == n - 2) {    // 마지막 vertex이면 (처음과 마지막은 starting vertex이기 때문) ex)sample1에서 '3'이면  
                    for (int i = 1; i <= n; i++)        // v->path에 없는 vertex이면 추가     
                        if (isIn(i, u->path)) continue;
                        else u->path.push_back(i);      // vertex 1을 제외하고 하나가 존재할 것임            
                    u->path.push_back(1);               // 첫번째 vertex를 다시 마지막에 추가

                    if (length(u->path) < minlength) {  // 현재 경로 u가 가장 짧으면 minlength&opttour 업데이트★
                        minlength = length(u->path);
                        opttour.assign(u->path.begin(), u->path.end());
                    }

                    
                    u->bound = bound(u);
                    if (u->bound > INF)
                        cout << u->level << " " << "INF" << " ";
                    else cout << u->level << " " << u->bound << " ";
                    for (int i = 0; i < u->path.size(); i++) {
                            if (i != u->path.size() - 1)
                                cout << u->path[i] << " ";
                            else cout << u->path[i] << "\n";
                        }
                }
                else {                      // 마지막 vertex가 아니면
                    u->bound = bound(u);    // path에 추가한 vertex i를 포함한 u에 대해 bound 계산

                    /* 아래 if문 안에 넣으면 u->bound가 INF일 때 출력안됨 */
                    if (u->bound > INF)
                        cout << u->level << " " << "INF" << " ";        // INF : 이동할 수 있는 vertex가 없음
                    else cout << u->level << " " << u->bound << " ";
                    for (int i = 0; i < u->path.size(); i++) {
                        if (i != u->path.size() - 1)
                            cout << u->path[i] << " ";
                        else cout << u->path[i] << "\n";
                    }
                    
                    if (u->bound < minlength)   // u->bound가 minlength보다 작아야지 PQ에 들어갈 최소한의 조건이 존재 (애초에 path가 될 수 없다)
                        PQ.push(u);             // 초반에는 minlength가 INF이기 때문에 계산에 사용되지 않을 node도 push됨
                }
            }
        }
    }
}
/*
현재 출력 알고리즘 : u->path에 들어가있는 경로 기준으로 남은 vertex들을 하나씩 추가해서 계산된 bound들 출력.. PQ에 들어가든 안들어가든 계산한거 모두
pop() : PQ에 들어간 node 중 계산에 사용된 node만 출력
push() : 계산에 사용되지 않아도 PQ에 들어간 node 출력
*/