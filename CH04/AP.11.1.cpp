#include <iostream>
#include <vector>
#include <map>

using namespace std;

int knapsack3(int n, int W, vector<int>& w, vector<int>& p, map<pair<int, int>, int> &P);

int main(void)
{
    int n, T;
    vector<int> w, p, W;
    map<pair<int, int>, int> P;     // P[pair<트리 레벨, 현재 가방무게>] = 현재이익

    cin >> n;                       // 아이템 개수
    w.resize(n + 1);
    p.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];                // 아이템 무게
    for (int i = 1; i <= n; i++)
        cin >> p[i];                // 아이템 이익
    
    cin >> T;
    W.resize(T);
    for (int i = 0; i < T; i++)
        cin >> W[i];                // T개의 가방 무게

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if ((p[i] / w[i]) < (p[j] / w[j])) {    // 아이템의 단위무게 별로 내림차순 정렬
                int temp = p[i];
                p[i] = p[j];
                p[j] = temp;

                temp = w[i];
                w[i] = w[j];
                w[j] = temp;
            }
        }
    }
    
    for (int i = 0; i < T; i++) {
        P.clear();
        cout << knapsack3(n, W[i], w, p, P) << "\n";
    
        for (auto iter = P.begin(); iter != P.end(); iter++)    
            if (iter->first.first != 0 && iter->first.second != 0)                                      // P의 pair의 첫번째와 두번째가 0이 아니면
                cout << iter->first.first << " " << iter->first.second << " " << iter->second << "\n";  // P 출력
    }
}

int knapsack3(int n, int W, vector<int>& w, vector<int>& p, map<pair<int, int>, int> &P)
{
    if (n == 0 || W <= 0)   // P[0][w] == 0 && P[i][0] == 0
        return 0;
    // P에 원소 존재 : iterator반환 / 존재x : P.end() 반환
    int lvalue = (P.find(make_pair(n - 1, W)) != P.end()) ? P[make_pair(n - 1, W)] : knapsack3(n - 1, W, w, p, P);                      // P에 P[make_pair(x,x)]가 존재 : lvalue에 할당 / 존재x : knapsack3 호출
    int rvalue = (P.find(make_pair(n - 1, W - w[n])) != P.end()) ? P[make_pair(n - 1, W - w[n])] : knapsack3(n - 1, W - w[n], w, p, P); // P에 P[make_pair(x,x)]가 존재 : rvalue에 할당 / 존재x : knapsack3 호출
    P[make_pair(n, W)] = (w[n] > W) ? lvalue : max(lvalue, p[n] + rvalue);              // 현재 무게가 남은 무게 큼 : (무게를 줄이지 않은 다음 level 값) / 작음 : (그것과 무게를 줄이고 현재이익을 추가한 값 중 큰 값)
    return P[make_pair(n, W)];  // 배낭무게 W에서 최대이익
}