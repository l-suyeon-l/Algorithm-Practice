#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void find_largest(int n, vector<int> S, int& large);
void find_both(int n, vector<int> S, int& small, int& large);
void find_both2(int n, vector<int> S, int& small, int& large);

int main(void)
{
    int n, small, large;
    vector<int> S;
    cin >> n;
    S.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> S[i];
    //find_largest(n, S, large);        // 가장 큰 값 찾기 
    //find_both(n, S, small, large);    // 가장 큰 값과 작은 값 찾기
    //find_both2(n, S, small, large);   // 가장 큰 값과 작은 값 찾기2
    cout << small << " " << large;

    return 0;
}

void find_largest(int n, vector<int> S, int& large)
{
    int i;
    large = S[1];
    for (i = 2; i <= n; i++)
        if (S[i] > large)
            large = S[i];
}

void find_both(int n, vector<int> S, int& small, int& large)
{
    small = large = S[1];
    for (int i = 2; i <= n; i++)
        if (S[i] < small)
            small = S[i];
        else if (S[i] > large)
            large = S[i];
}

void find_both2(int n, vector<int> S, int& small, int& large)
{
    int i;

    if (S[1] < S[2]) {
        small = S[1];
        large = S[2];
    }
    else {
        small = S[2];
        large = S[1];
    }
    for (i = 3; i <= n - 1; i+=2) {
        if (S[i] < S[i + 1]) {
            if (S[i] < small) small = S[i];
            if (S[i + 1] > large) large = S[i + 1];
        }
        else {
            if (S[i + 1] < small) small = S[i + 1];
            if (S[i] > large) large = S[i];
        }
    }
}