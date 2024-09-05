#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> Triangle;
Triangle path, cost;
int rSum(int row, int col, Triangle T, Triangle& cost);
void tpath(int n, Triangle T, Triangle cost, Triangle path);

int main(void)
{
    int n;
    scanf("%d", &n);
    Triangle T(n, vector<int>(n));
    cost.resize(n, vector<int>(n, -1));
    path.resize(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            scanf("%d", &T[i][j]);

    printf("%d", rSum(0, 0, T, cost));
    printf("\n");
    tpath(n, T, cost, path);

    return 0;
}

int rSum(int row, int col, Triangle T, Triangle& cost)
{
    if (row == T.size() - 1)
        return T[row][col];
    else if (cost[row][col] == -1)
        cost[row][col] = T[row][col] + max(rSum(row + 1, col, T, cost), rSum(row + 1, col + 1, T, cost));
    return cost[row][col];
}

void tpath(int n, Triangle T, Triangle cost, Triangle path)
{
    for (int i = 0; i < n; i++)         //여기 아니면 rSum 함수에 if - 에 넣기
        cost[n - 1][i] = T[n - 1][i];

    int row = 0, col = 0;
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= n; j++) {
            if (cost[i + 1][j] > cost[i + 1][j + 1])
                path[i][j] = 0;
            else path[i][j] = 1;
        }
    }

    while (n--) {
        printf("%d", T[row][col]);
        if (path[row][col] == 0)
            row++;
        else if (path[row][col] == 1) {
            row++; col++;
        }
        if (n != 0) printf(" ");
    }
}