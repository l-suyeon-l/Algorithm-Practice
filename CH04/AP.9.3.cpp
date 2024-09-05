#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct item* item_ptr;
typedef struct item {
    int id;
    int weight;
    int profit;
    int profit_per_unit;
} item_t;

int n;
vector<item_t> items;
vector<int> W;

bool compare_item(item_t i, item_t j);
void knapsack1(int& maxprofit, int& totweight, int W, vector<vector<int>>& rst);

int main(void)
{
    int T, maxprofit, totweight;
    scanf("%d", &n);                // n = 아이템의 개수
    items.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> items[i].weight;                                         // item의 무게 입력
    for (int i = 1; i <= n; i++)
        cin >> items[i].profit;                                         // item의 이익 입력
    for (int i = 1; i <= n; i++)
        items[i].profit_per_unit = items[i].profit / items[i].weight;   // item의 단위수익 저장

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (!compare_item(items[i], items[j])) {                    // item의 단위수익 내림차순 정렬
                item_t temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
    // sort(items.begin() + 1, items.end(), compare_item);

    scanf("%d", &T);                // T = 배낭 개수
    W.resize(T + 1);    
    for (int i = 1; i <= T; i++)
        cin >> W[i];                // W[i] = 배낭 무게

    for (int k = 1; k <= T; k++) {
        vector<vector<int>> rst(n + 2, vector<int>(2, 0));      // 배낭에 넣을 짐 목록 배열 : [][0] = 무게 & [][1] = 수익
        knapsack1(maxprofit, totweight, W[k], rst);
        printf("%d\n", maxprofit);
        int i = 1;                                              // 배열 rst의 시작은 [1]부터
        while (rst[i][0] != 0) {                                // rst의 값이 NULL(0)이 아닐 때까지 출력
            printf("%d %d", rst[i][0], rst[i][1]);
            i++;
            if (rst[i][0] != 0) printf("\n");                   // 다음 값이 NULL(0)이 아니면 '\n' 출력
        }
        if (k != T) printf("\n");                               // 마지막 배낭이면 '\n' 출력 안함
    }
}

bool compare_item(item_t i, item_t j) {
    if (i.profit_per_unit > j.profit_per_unit)
        return true;
    return false;
}

void knapsack1(int& maxprofit, int& totweight, int W, vector<vector<int>>& rst)
{
    maxprofit = totweight = 0;
    for (int i = 1; i <= n; i++) {                         // 아이템은 단위 무게 기준으로 내림차순 정렬돼있어야 함
        if (totweight + items[i].weight <= W) {                 // i번째 아이템의 무게가 남은 배낭 무게보다 작으면
            maxprofit += items[i].profit;           
            totweight += items[i].weight;
            rst[i][0] = items[i].weight; rst[i][1] = items[i].profit;             // 해당 아이템의 무게&수익 저장
        }
        else {                                                    // i번째 아이템의 무게가 남은 배낭 무게보다 크면
            maxprofit += (W - totweight) * items[i].profit_per_unit;
            rst[i][0] = (W - totweight);
            rst[i][1] = (W - totweight) * items[i].profit_per_unit;
            totweight += (W - totweight);                   // 해당 아이템의 무게&수익 중 남은 배낭무게만큼만 저장
            break;
        }
    }
}