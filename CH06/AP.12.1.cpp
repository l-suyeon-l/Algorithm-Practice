#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

typedef struct node *node_pointer;
typedef struct node {
    int level;
    int weight;
    int profit;
    float bound;
} nodetype;
struct compare {
    bool operator()(node_pointer u, node_pointer v) {
        if (u->bound < v->bound)
            return true;
        return false;
    }
};
typedef priority_queue<node_pointer, vector<node_pointer>, compare> priority_queue_of_node;

int n, W, maxprofit;
vector<int> p, w;

float bound(node_pointer u);
node_pointer create_node(int level, int weight, int profit);
void knapsack6();

int main(void)
{
    cin >> n >> W;                                  // n : 아이템의 개수, W : 배낭무게
    w.resize(n + 1);
    p.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];                                // 아이템 무게 입력
    for (int i = 1; i <= n; i++)
        cin >> p[i];                                // 아이템 이익 입력
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if ((p[i] / w[i]) < (p[j] / w[j])) {    // 단위 이익 내림차순 정렬
                swap(p[i], p[j]);
                swap(w[i], w[j]);
            }
    knapsack6();
    cout << maxprofit;
    return 0;
}

float bound(node_pointer u)
{
    int j, k, totweight;
    float result;           // return값 (=bound)
    if (u->weight >= W)     // W보다 weight가 더 크면 nonpromising
        return 0;
    else {
        j = u->level + 1;                           // 현재 원소의 다음 원소부터 취급
        result = u->profit;                         // bound : + 기존이익
        totweight = u->weight;                      // totweight : + 기존무게
        while (j <= n && totweight + w[j] <= W) {   // 원소(w[j])의 유효성 검사(W를 넘지 않으면 조건문 실행)
            totweight += w[j];                      // totweight : + 유효한(W를 넘지 않는) 원소의 무게
            result += p[j];                         // bound : + 유효한(W를 넘지 않는) 원소의 이익
            j++;
        }
        k = j;
        if (k <= n)     // k가 n을 넘는 경우 : while문에서 작동한 원소(j번째 원소)가 마지막 원소였다는 의미. j++하고 나옴
            result += (W - totweight) * ((float)p[k] / w[k]);   // bound 공식
        return result;
    }
}

node_pointer create_node(int level, int weight, int profit)
{
    node_pointer v = new nodetype;
    v->level = level;
    v->weight = weight;
    v->profit = profit;
    v->bound = bound(v);    // bound 따로 계산 : level(몇 번째 원소인지), weight, profit 사용해서

    /*cout << v->level << " " << v->weight << " " << v->profit << " " << (int)v->bound << "\n";*/
    return v;
}

void knapsack6()    // Ch06 p.8 참고
{
    priority_queue_of_node PQ;
    node_pointer u, v;
    maxprofit = 0;
    PQ.push(create_node(0, 0, 0));      // (maxprofit, weight, bound) 노드 생성 후 PQ에 push
    /*cout << u->level << " " << u->weight << " " << u->profit << " " << (int)u->bound << "\n"; <(0, 0, 0) 노드 정보 출력하도록 수정*/
    while (!PQ.empty()) {
        v = PQ.top();   PQ.pop();       // v에 가장 첫번째 PQ 넣기 & PQ에서 빼내기
        /*cout << v->level << " " << v->weight << " " << v->profit << " " << (int)v->bound << "\n";*/
        if (v->bound > maxprofit) {     // bound(이익 가능성)이 maxprofit보다 크면 (작다면 갈 필요x, pruning)
            // 다음 원소(level+1) 포함한 경우의 노드 생성 u
            u = create_node(v->level + 1, v->weight + w[v->level + 1], v->profit + p[v->level + 1]);    
            if (u->weight <= W && u->profit > maxprofit)        // 현재 무게가 W보다 작음 && 현재 이익이 maxprofit보다 큼
                maxprofit = u->profit;                          // maxprofit 업데이트
            if (u->bound > maxprofit) {                         // bound가 maxprofit보다 크면(promising)
                PQ.push(u);                                     // PQ에 추가
                /*cout << u->level << " " << u->weight << " " << u->profit << " " << (int)u->bound << "\n";*/
            }
            // 다음 원소(level+1) 포함하지 않은 경우의 노드 생성 u
            u = create_node(v->level + 1, v->weight, v->profit);                                        
            if (u->bound > maxprofit) {                         // bound가 maxprofit보다 크면(promising)
                PQ.push(u);                                     // PQ에 추가
                /*cout << u->level << " " << u->weight << " " << u->profit << " " << (int)u->bound << "\n";*/
            }
        }
    }
}

/*
1. create_node에서 출력 : bound가 높은 순으로 출력되지만, 출력된 원소에 해당하는 레벨이 전부 출력된 후 다음으로 높은 bound 노드 출력됨
2. PQ.pop에서 출력 : PQ에 들어간 노드(promising) 중 bound가 높은 순으로 출력
3. PQ.push에서 출력 : PQ에 들어간 노드(promising) 순서대로 출력

create_node한 v 출력
0 0 0 115
1 2 40 115
1 0 0 82
2 7 70 115
2 2 40 98
3 17 120 0
3 7 70 80
3 12 90 98
3 2 40 50
4 17 100 0
4 12 90 90
90

PQ.top한 v 출력
0 0 0 115
1 2 40 115
2 7 70 115
2 2 40 98
3 12 90 98
1 0 0 82
3 7 70 80
90

PQ.push(u)한 u 출력
0 0 0 115
1 2 40 115
1 0 0 82
2 7 70 115
2 2 40 98
3 7 70 80
3 12 90 98
90
*/