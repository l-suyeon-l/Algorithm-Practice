#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int selection(int low, int high, int k);
void print_list(vector<int> S);
void partition(int low, int high, int &pivotpoint);

vector<int> S;

int main(void)
{
    int n;
    cin >> n;
    S.resize(n);
    for (int i = 0; i < n; i++)
        cin >> S[i];
    /*for (int i = 1; i <= n; i++)
        cin >> S[i];*/
    int rst = selection(0, n - 1, 0); // k번째 슬롯 찾기(S[i]가 0부터 시작인지 1부터 시작인지에 따라 달라짐, 유동적)
    //int rst = selection(1, n, 0);
    cout << rst;
}

void partition(int low, int high, int &pivotpoint)
{
    int i, j, pivotitem;

    pivotitem = S[low];
    j = low;
    for (i = low + 1; i <= high; i++)
        if (S[i] < pivotitem) {
            j++;
            int temp = S[i];
            S[i] = S[j];
            S[j] = temp;
        }
    pivotpoint = j;
    int temp = S[low];
    S[low] = S[pivotpoint];
    S[pivotpoint] = temp;
}

void print_list(vector<int> S)
{
    int i = 0;
    while(S[i] != 0) {
        cout << S[i++] << " ";
    }
    cout << "\n";
}

int selection(int low, int high, int k)
{
    int pivotpoint;

    if (low == high)
        return S[low];
    else {
        partition(low, high, pivotpoint);
        //print_list(S);
        if (k == pivotpoint)
            return S[pivotpoint];
        else if (k < pivotpoint)
            return selection(low, pivotpoint - 1, k);
        else return selection(pivotpoint + 1, high, k);
    }
}