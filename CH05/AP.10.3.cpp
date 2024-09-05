#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<bool>> matrix_t;
matrix_t W;
int n, m = 1, cnt = 0;
vector<int> vcolor;     // [i]번째 정점에 칠해져있는 색

bool promising(int i);
void m_coloring(int i);

int main(void)
{
    int k, a, b;
    cin >> n >> k;  // n : 정점의 수, k : 간선의 수
    vcolor.resize(n + 1);
    W.resize(n + 1, vector<bool>(n + 1, false));    // adjacent matrix
    for (int i = 1; i <= k; i++) {
        cin >> a >> b;              // 간선이 연결돼있는 vertex a, b
        W[a][b] = W[b][a] = true;   // adjacent matrix에 true
    }
    
    while(m <= 4) {     // 색깔의 수(m)가 각각 1, 2, 3, 4일 때 m_coloring 호출
        m_coloring(0);  
        if (cnt != 0)   // 해당 색의 수(m)으로 색칠이 가능하다면
            break;
        m++;            // 색칠이 불가능하면 색깔 하나 증가
    }
    cout << m << '\n' << cnt;   // 해당 color m으로 색칠할 수 있는 경우의 수 출력
}

void m_coloring(int i)  // i는 현재 정점의 위치 vi
{
    if (promising(i)) { // promising
        if (i == n) 
            cnt++;      // m값으로 색칠할 수 있는 경우의 수
        else            // nonpromising
            for (int color = 1; color <= m; color++) {  // 색을 번호로 지정
                vcolor[i + 1] = color;              // i + 1번째 정점을 color로 색칠해보면서
                m_coloring(i + 1);                  // m_coloring 재귀호출
            }
    }
}

/* n Queens 문제의 promising과 유사 */
bool promising(int i)   // vertex i에 대해
{
    int j = 1;          
    bool flag = true;

    while (j < i && flag) {                     // i보다 작은 vertex j와 비교 && flag가 true인 동안
        if (W[i][j] && vcolor[i] == vcolor[j])  // 인접 && 두 정점이 같은 색이면
            flag = false;                       // false : nonpromising
        j++;                                    // i보다 작은 vertex 하나씩 증가시키면서 비교
    }
    return flag;
}