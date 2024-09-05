#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix_t;

void lcs(string X, string Y, matrix_t& c, matrix_t& b);
void getLcs(int i, int j, matrix_t& b, string X, string& Z);

int main(void)
{
    string X, Y, Z;
    cin >> X;
    cin >> Y;

    matrix_t c, b;
    lcs(X, Y, c, b);
    printf("%d\n", c[X.length()][Y.length()]);

    getLcs(X.length(), Y.length(), b, X, Z);
    cout << Z;
}

void lcs(string X, string Y, matrix_t& c, matrix_t& b)
{
    X = X.insert(0, " ");
    Y = Y.insert(0, " ");
    int m = X.length(), n = Y.length();
    c.resize(m, vector<int>(n, 0));
    b.resize(m, vector<int>(n, 0));
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (X[i] == Y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else {
                c[i][j] = max(c[i][j - 1], c[i - 1][j]);
                if (c[i][j - 1] > c[i - 1][j])
                    b[i][j] = 2;
                else b[i][j] = 3;
            }
        }
    }
}

void getLcs(int i, int j, matrix_t& b, string X, string& Z)
{
    if (i == 0 || j == 0)   // i == X의 길이, j == Y의 길이
        return ;
    else {
        if (b[i][j] == 1) {
            Z.insert(Z.begin(), X[i - 1]);
            getLcs(i - 1, j - 1, b, X, Z);
        }
        else if (b[i][j] == 2)
            getLcs(i, j - 1, b, X, Z);
        else if (b[i][j] == 3)
            getLcs(i - 1, j, b, X, Z);
    }
}