#include <iostream>
#include <vector>
#include <string>

using namespace std;

void sum_of_subsets(int i, int weight, int total);
bool promising(int i, int weight, int total);

int W, cnt = 0;
vector<int> w;          // 원소가 들어있는 벡터
vector<bool> include;   // k번째 원소의 포함여부
string str;

int main(void)
{
    int n, total = 0;
    cin >> n >> W;
    w.resize(n + 1);
    include.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        total += w[i];
    }

    sum_of_subsets(0, 0, total);    // 0번째 level, 0 weight에서 시작
    cout << cnt << '\n' << str;     // str : 모든 부분집합이 저장돼있음

    return 0;
}

void sum_of_subsets(int i, int weight, int total)   // i : 현재 레벨, weight : 현재 포함된 총 무게, total : 현재이후의 값들의 합
{
    if (promising(i, weight, total)) {      // promising하면
        if (weight == W) {                  // 원소의 합이 W이면
            cnt++;                          // 원소의 합이 W인 부분집합의 개수 cnt(전역변수)
             for (int k = 1; k <= i; k++){  // i는 현재까지 생성된 레벨
                if (include[k]) {           // k번째 원소가 포함되면 : include[k] == true (아래 else문에서 결정됨)
                    str += to_string(w[k]); // 출력을 위해 부분집합(int형)을 str으로 저장하기
                    if (k != i)
                        str += " ";
                    else str += "\n";
                }
            }
            /* for (int k = 1; k <= i; k++) {
                cout << w[k];
                if (k != i) cout << " ";
                else cout << "\n";
            }*/
        }
        else {                              // 원소의 합이 W이 아니면
            include[i + 1] = true;  // 현재 무게 포함(left)
            sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1]);
            include[i + 1] = false; // 현재 무게 미포함(right)
            sum_of_subsets(i + 1, weight, total - w[i + 1]);    // 남은 total무게는 포함시키지 않더라도 업데이트
        }
    }
}

bool promising(int i, int weight, int total)
{
    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
    // (현재 값과 남은 값의 합이 W 이상) && (W 무게와 같거나 다음 노드 무게까지의 합이 W 이하) 면 promising
}