#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> col;
vector<string> str;     // str을 동적으로 할당: vector 이용
int n, cnt = 0;

bool promising(int i);
void queens(int i);
bool compareStrings(const string& str1, const string& str2);    // 이해하기!!! 매우중요

int main(void)
{
    cin >> n;
    col.resize(n + 1);

    queens(0);

    cout << cnt << "\n";
    string max = str[0];
    for (int i = 1; i < str.size(); i++) {  // str.size() = vector<string> str의 크기
        if (compareStrings(str[i], max))    // 벡터 안의 str[i]가 max 값보다 크면
            max = str[i];                   // max에 입력
    }
    cout << max;                            // 최대값 출력
}

void queens(int i)
{
    int j;
    if (promising(i)) {
        if (i == n) {                       // leaf node에 도달하면(가능한 보드 배치를 찾으면)
            string s = "";
            for (int k = 1; k <= n; k++)
                s += to_string(col[k]);     // 가능한 보드 배치 col순서를 문자열로 저장 : s
            str.push_back(s);               // 벡터에 문자열 s push
            cnt++;                          // 가능한 보드 배치 개수 cnt(전역변수)
            /* for (int k = 1; k <= n; k++)
                cout << col[k];
            cout << "\n";*/
        }
        else {                              // internal node
            for (j = 1; j <= n; j++) {
                col[i + 1] = j;             // 다음 row의 column을 하나씩 증가시키면서
                queens(i + 1);              // queens 재귀호출
            }                               // 모든 j(column)이 nonpromising하면 parent node로 올라감
        }
    }
}

bool promising(int i)   // i는 현재 row
{
    int k = 1;
    bool flag = true;

    while (k < i && flag) {                                         // k는 row i 이전의 row && flag가 true인 동안
        if ((col[i] == col[k]) || abs(col[i] - col[k]) == i - k)    // row i의 column이 이전 row들의 colum과 같거나 || 대각선에 있으면
            flag = false;                                           // nonpromising
        k++;                                                        // i보다 작은 row 하나씩 증가시키면서 비교
    }
    return flag;
}

bool compareStrings(const string& str1, const string& str2) {
    if (str1.length() != str2.length()) {       // str1와 str2가 길이가 다르면
        return str1.length() > str2.length();   // 길이가 더 긴 문자열이 크다는 뜻. 그를 return
    }
    return str1 > str2;                         // str1와 str2의 길이가 같으면 사전식 순서로 비교하여 더 큰 값 return
}