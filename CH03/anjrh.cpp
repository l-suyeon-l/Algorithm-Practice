#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> matrix_t;

int solve(int n, matrix_t C, matrix_t& P);
void path(int n, matrix_t D, matrix_t P, vector<int>& p);

int main(void)
{
    matrix_t T ,C, P;
    vector<int> p;
    int n;

    cin >> n;

    T.resize(n, vector<int>(n, 0));
    C.resize(n, vector<int>(n, 0));
    P.resize(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> T[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            C[i][j] = T[i][j];
        }
    }

    cout << solve(n, C, P) << endl;

    path(n, T, P, p);
    for (int i = 0; i < n; i++) {
        cout << p[i];
        if (i != n - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

int solve(int n, matrix_t C, matrix_t& P)
{
    for (int row = n - 2; row >= 0; row--) {
        for (int col = 0; col <= row; col++) {
            if (C[row + 1][col] > C[row + 1][col + 1]) {
                C[row][col] += C[row + 1][col];
                P[row][col] = 1;
            }
            else if (C[row + 1][col] < C[row + 1][col + 1]) {
                C[row][col] += C[row + 1][col + 1];
                P[row][col] = 2;
            }
            else {
                C[row][col] += C[row + 1][col + 1];
                P[row][col] = 3;
            }
        }
    }
    return C[0][0];
}

void path(int n, matrix_t D, matrix_t P, vector<int>& p)
{
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (P[i][j] == 1) {
            p.push_back(D[i][j]);
        }
        else if (P[i][j] == 2) {
            p.push_back(D[i][j]);
            j++;
        }
        else if (P[i][j] == 3) {
            p.push_back(D[i][j]);
            j++;
        }
        else {
            p.push_back(D[i][j]);
        }
    }
}