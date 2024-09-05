#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct item {
    int index;
    int value;
} item_type;
typedef vector<item_type> item_list;

void tournament(int n, item_list& S, item_list& L, item_type &largest);

int main(void)
{
    int n, second_largest;
    cin >> n;               // n은 2의 제곱수
    item_type largest;
    item_list S(n);
    for (int i = 0; i < n; i++) {
        cin >> S[i].value;
        S[i].index = i;
    }
    item_list L(n);
    vector<int> SL;

    tournament(n, S, L, largest);
    //cout << largest.value << " " << largest.index << endl;
    second_largest = L[largest.index].value;
    while(largest.index != 0) {
        largest.index /= 2;
        if (L[largest.index].value > second_largest)
            second_largest = L[largest.index].value;
    }
    cout << second_largest << endl;

    return 0;
}

void tournament(int n, item_list& S, item_list& L, item_type &largest)
{
    int j = 0;
    if (n == 1)
        largest = S[0];
    else {
        item_list winner;
        for (int i = 0; i < n - 1; i+=2) {
            if (S[i].value > S[i + 1].value) {
                winner.push_back(S[i]);
                L[i] = S[i + 1];
                //cout << L[i].value << "/";
            }
            else {
                winner.push_back(S[i + 1]);
                L[i + 1] = S[i];
                //cout << L[i + 1].value << "/";
            }
        }
        return tournament(n / 2, winner, L, largest);
    }
}