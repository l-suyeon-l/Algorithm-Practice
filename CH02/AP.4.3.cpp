#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> pBoard;
int pn = 0;

int whereis(int n, int srow, int scol, int row, int col);
void fill(int n, pBoard& board, int srow, int scol, int where);
void hole(int part, int where, int n, int srow, int scol, int row, int col, int &hrow, int &hcol);
void tromino(int n, pBoard& board, int srow, int scol, int row, int col);

int main(void)
{
    int n, row, col, srow = 0, scol = 0;
    scanf("%d %d %d", &n, &row, &col);
    pBoard board(n, vector<int>(n));

    tromino(n, board, srow, scol, row, col);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", board[i][j]);
            if (j != n-1)
                printf(" ");
        }
        if (i != n-1)
            printf("\n");
    }
}

int whereis(int n, int srow, int scol, int row, int col)    // 구멍의 사분면 위치 찾기
{
    int m = n / 2;
    if (row - srow < m) {
        if (col - scol < m)
            return 1;   // 1사분면
        else return 2;  // 2사분면
    }
    else {
        if (col - scol < m)
            return 3;   // 3사분면
        else return 4;  // 4사분면
    }
}

void fill(int n, pBoard& board, int srow, int scol, int where)   // 구멍이 없는 사분면의 board에 n 입력
{
    if (where != 1 /*1사분면*/)
        board[srow][scol] = n;
    if (where != 2 /*2사분면*/)
        board[srow][scol + 1] = n;
    if (where != 3 /*3사분면*/)
        board[srow + 1][scol] = n;
    if (where != 4 /*4사분면*/)
        board[srow + 1][scol + 1] = n;
}

void hole(int part, int where, int n, int srow, int scol, int row, int col, int &hrow, int &hcol)
{
    // where은 사분면을 가리키는 변수
    int m = n / 2;
    if (part != where) {
        row = srow + m - 1; col = scol + m - 1; // 구멍이 없는 사분면 가장자리에 채우기
        if (part == 2 || part == 4) col += 1;
        if (part == 3 || part == 4) row += 1;
    }
    hrow = row; hcol = col;
}

void tromino(int n, pBoard& board, int srow, int scol, int row, int col)
{
    int where = whereis(n, srow, scol, row, col);

    if (n == 2) {
        pn++;
        fill(pn, board, srow, scol, where);
    }
    else {
        int hrow, hcol;
        int m = n / 2;
        pn++;
        fill(pn, board, srow + m - 1, scol + m - 1, where);  // 구멍 없는 사분면에 채우기
        hole(1, where, n, srow, scol, row, col, hrow, hcol);
        tromino(m, board, srow, scol, hrow, hcol);
        hole(2, where, n, srow, scol, row, col, hrow, hcol);
        tromino(m, board, srow, scol + m, hrow, hcol);
        hole(3, where, n, srow, scol, row, col, hrow, hcol);
        tromino(m, board, srow + m, scol, hrow, hcol);
        hole(4, where, n, srow, scol, row, col, hrow, hcol);
        tromino(m, board, srow + m, scol + m, hrow, hcol);
    }
}