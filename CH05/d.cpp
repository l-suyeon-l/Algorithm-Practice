#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int n, m, T, cnt = 0, cnt_save, Cnt;
int Size;

vector<int> Cnt_list;
vector<int> visit;
vector<int> graph;
vector<vector<int>> moves = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

void knight(int i, int node, int start, int now);
bool promising(int i, int node, int first);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    Size = n * m - 1;

    visit.resize(n * m);
    graph.resize(n * m * n * m, 0);

    for (int i = 0; i <= Size; i++)
    {
        for (auto move : moves)
        {
            int row = i / m;
            int col = i % m;
            int nextRow = row + move[0];
            int nextCol = col + move[1];
            if (nextRow >= 0 && nextRow < n && nextCol >= 0 && nextCol < m)
            {
                int j = nextRow * m + nextCol;
                graph[i * n * m + j] = 1;
                graph[j * n * m + i] = 1;
            }
        }
    }

    knight(0, 0, 0, 0);
    cnt_save = cnt;

    visit.resize(n * m, 0);

    Cnt = 0;
    cin >> T;
    Cnt_list.resize(T);

    for (int i = 0; i < T; i++)
    {
        int s, f;
        cin >> s >> f;
        int vv = s * m + f;
        visit[0] = vv;
        knight(0, 0, vv, 0);
        Cnt_list[i] = Cnt;
        Cnt = 0;
    }

    cout << cnt_save << endl;
    for (int i = 0; i < T; i++)
    {
        cout << Cnt_list[i];
        if (i != T - 1)
            cout << endl;
    }
}

void knight(int i, int node, int start, int now)
{
    bool opt = true;
    if (promising(i, node, start))
    {
        if (i == n * m - 1)
        {
            cnt++;
        }
        else
        {
            for (int j = 0; j <= Size; j++)
            {
                if (graph[visit[i] * n * m + j] == 1)
                {
                    visit[i + 1] = j;
                    knight(i + 1, j, start, visit[i]);
                    visit[i + 1] = 0;
                }
            }
        }
    }
}

bool promising(int i, int node, int start)
{
    bool flag = true;
    bool opt;
    int now = 0;
    if (i == Size)
    {
        if (graph[visit[i] * n * m + start] != 1)
        {
            flag = false;
        }
        else if (graph[visit[i] * n * m + visit[i - 1]] == 1)
        {
            bool opt = true;
            for (int k = 0; k < i; k++)
            {
                if (visit[i] == visit[k])
                {
                    opt = false;
                    flag = false;
                    break;  // 중복 검사 중인 경우 루프 탈출
                }
            }
            if (opt)
            {
                Cnt++;
            }
        }
        else
        {
            flag = false;
        }
    }
    else if (i > 0 && graph[visit[i] * n * m + visit[i - 1]] != 1)
    {
        flag = false;
    }
    return flag;
}