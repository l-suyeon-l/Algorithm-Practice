#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, W, maxprofit = 0;
float bound;
vector<int> w, p;
vector<bool> include, bestset;

bool promising(int i, int profit, int weight);
void array_copy(vector<bool>& include, vector<bool>& index);
void knapsack4(int i, int profit, int weight);

int main(void)
{
    cin >> n >> W;                  // n : 아이템 개수, W : 가방 무게
    w.resize(n + 1);
    p.resize(n + 1);
    include.resize(n + 1);
    bestset.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];                // 아이템 무게
    for (int i = 1; i <= n; i++)
        cin >> p[i];                // 아이템 이익

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if ((p[i] / w[i]) < (p[j] / w[j])) {    // 아이템의 단위무게 별로 내림차순 정렬
                int temp = p[i];
                p[i] = p[j];
                p[j] = temp;

                temp = w[i];
                w[i] = w[j];
                w[j] = temp;
            }

    knapsack4(0, 0, 0);
    cout << maxprofit << endl;
    for (int i = 1; i <= n; i++)                                // i는 원소의 번호(1,3이면 원소 1, 3번이 최적집합 원소)
        if (bestset[i]) cout << w[i] << " " << p[i] << "\n";    // 최적 집합에 포함된 아이템들의 weight & profit 출력
    return 0;
}

bool promising(int i, int profit, int weight)
{
    int j, k, totweight;
    if (weight >= W) {  // W보다 weight가 더 크면 nonpromising
        cout << i << " " << weight << " " << profit << " " << (int)bound << " " << maxprofit << "\n";   // 상태공간 트리의 현재 노드 출력(nonpromising한 노드까지)
        return false;                                                                                   // false이므로 nonpromising한 노드 집합
    }
    else {
        j = i + 1;
        bound = profit;                             // bound : + 기존이익
        totweight = weight;                         // totweight : + 기존무게
        while (j <= n && totweight + w[j] <= W) {   // 원소(w[j])의 유효성 검사(W를 넘지 않으면 조건문 실행)
            totweight += w[j];                      // totweight : + 유효한(W를 넘지 않는) 원소의 무게
            bound += p[j];                          // bound : + 유효한(W를 넘지 않는) 원소의 이익
            j++;
        }
        k = j;
        if (k <= n)   // k가 n을 넘는 경우 : while문에서 작동한 원소(j번째 원소)가 마지막 원소였다는 의미. j++하고 나옴
            bound += (W - totweight) * ((float)p[k] / w[k]);    // bound 공식
        cout << i << " " << weight << " " << profit << " " << (int)bound << " " << maxprofit << "\n";   // 상태공간 트리의 현재 노드 출력(nonpromising한 노드까지)
        return bound > maxprofit;
    }
}

void array_copy(vector<bool>& include, vector<bool>& index)
{
    if (include.size() != index.size())                     // 복사할 index의 크기가 include의 크기와 다르면
        index.resize(include.size());                       // include 크기로 수정
    copy(include.begin(), include.end(), index.begin());    // copy
}

void knapsack4(int i, int profit, int weight)
{
    if (weight <= W && profit > maxprofit) {                        // 담을 수 있는 무게인데 현재 profit이 maxprofit보다 더 크면 업데이트
        maxprofit = profit;                                         // 최적 집합이므로 현재 profit ==> maxprofit
        array_copy(include, bestset);                               // 최적 아이템 집합(이익 최대집합)을 bestset에 복사
    }

    if (promising(i, profit, weight)) {
        include[i + 1] = true;                                      // 다음(i + 1) 아이템을 포함하면(left node)
        knapsack4(i + 1, profit + p[i + 1], weight + w[i + 1]);     // profit과 weight에 다음 아이템 추가하여 재귀호출
        include[i + 1] = false;                                     // 다음(i + 1) 아이템을 포함하지 않으면(right node)
        knapsack4(i + 1, profit, weight);                           // profit과 weight 갱신하지 않고 재귀호출
    }
}