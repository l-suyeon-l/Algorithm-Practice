#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* k번째로 작은 값 찾기 */
int main(void)
{
    int n, k;
    cin >> n >> k;
    vector<int> S(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> S[i];
    sort(S.begin(), S.end());
    cout << S[k] << endl;

    return 0;
}