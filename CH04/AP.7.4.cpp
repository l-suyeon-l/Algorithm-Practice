#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> selection(int n, vector<int>& s, vector<int>& f);

int main(void)
{
    int n;
    scanf("%d", &n);
    vector<int> s(n + 1), f(n + 1);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &s[i], &f[i]);

    vector<int> solution;
    solution = selection(n, s, f);
    printf("%d\n", solution.size());
    for (int i = 0; i < solution.size(); i++) {
        printf("%d %d", s[solution[i]], f[solution[i]]);
        if (i != solution.size() - 1)
            printf("\n");
    }
}

vector<int> selection(int n, vector<int>& s, vector<int>& f)
{
    vector<int> S;
    S.clear();
    int F = 0;
    for (int k = 1; k <= n; k++) {
        if (F <= s[k]) {
            S.push_back(k);
            F = f[k];
        }
    }
    return S;
}