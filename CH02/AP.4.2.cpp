#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

typedef vector<int> LargeInteger;
int threshold;
int cnt = 0;

void remove_leading_zeros(LargeInteger &v);
void roundup_carry(LargeInteger &v);
void ladd(LargeInteger a, LargeInteger b, LargeInteger &c);
void lmult(LargeInteger a, LargeInteger b, LargeInteger &c);
void pow_by_exp(LargeInteger u, int m, LargeInteger &v);
void rem_by_exp(LargeInteger u, int m, LargeInteger &v);
void div_by_exp(LargeInteger u, int m, LargeInteger & v);
void prod(LargeInteger u, LargeInteger v, LargeInteger &r);

int main(void)
{
    string n1, n2;
    cin >> threshold;
    cin >> n1;
    cin >> n2;
    LargeInteger u, v, r;
    u.resize(n1.size());    v.resize(n2.size());

    int j = n1.size();
    for (int i = 0; i < n1.size(); i++) {   // 첫번째 정수 n1을 u벡터에 반대정렬
        j--;
        u[i] = n1[j] - '0';
    }
    j = n2.size();
    for (int i = 0; i < n2.size(); i++) {   // 두번째 저수 n2를 v벡터에 반대정렬
        j--;
        v[i] = n2[j] - '0';
    }
    
    prod(u, v, r);

    printf("%d\n", cnt);
    for (int i = r.size() - 1; i >= 0; i--) {
        printf("%d", r[i]); // 숫자는 r 벡터 안에 들어있기 때문에 r이 아닌 r[i]를 출력해야함
    }
    return 0;
}

void remove_leading_zeros(LargeInteger &v)
{
    while(v.size() != 0 && v.back() == 0)
        v.pop_back();
}

void roundup_carry(LargeInteger &v)
{
    int carry = 0;
    for (int i = 0; i < v.size(); i++) {
        v[i] += carry;  // i = 0 일 때에는 일의 자리 수이므로 carry = 0(올릴 숫자 없음)
        carry = v[i] / 10;  // 다음 자리수에 올릴 수 carry에 저장
        v[i] = v[i] % 10;   // 본래 자리수에는 그 수의 일의 자리만 저장
    }
    if (carry != 0) // 여기의 carry는 마지막 배열의 올릴 수
        v.push_back(carry); // 마지막 배열 뒤에 carry 추가(배열에는 수가 반대로 입력되어 있음)
}

void ladd(LargeInteger a, LargeInteger b, LargeInteger &c)
{
    c.resize(max(a.size(), b.size()));  // 배열c의 크기를 배열 a,b중 큰 배열의 크기로 할당
    fill(c.begin(), c.end(), 0);        // 배열c 전체를 0으로 할당
    for (int i = 0; i < c.size(); i++) {    // for문 : 덧셈은 같은 자리수끼리 더한다
        if (i < a.size()) c[i] += a[i]; 
        if (i < b.size()) c[i] += b[i]; // 배열 a, b의 각 자리수가 끝날 때까지 배열c에 숫자 합하기(10이상 ok)
    }
    roundup_carry(c);   // 10 이상 배열의 자릿수 올리기기
}

void lmult(LargeInteger a, LargeInteger b, LargeInteger &c)
{
    c.resize(a.size() + b.size() - 1);  // c의 크기를 a의 크기+b의 크기-1로
    fill(c.begin(), c.end(), 0);    // 배열c의 전체를 0으로 할당
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {    // for문 : 곱셈은 한 숫자의 자리수가 다른 숫자의 모든 자리수에 곱해진다
            c[i + j] += a[i] * b[j];    // 일단 각 자리수 곱한 값을 배열에 입력(10이상 ok)
        }
    }
    roundup_carry(c);   // 10이상 배열의 자릿수 올리기
}

void pow_by_exp(LargeInteger u, int m, LargeInteger &v)
{
    // m은 곱할 10의 차수(10^m)
    if (u.size() == 0)
        v.resize(0);    // v가 비어있다면 배열 크기를 0으로
    else {
        v.resize(u.size() + m);         // v배열의 사이즈를 원래사이즈 + m 으로
        fill(v.begin(), v.end(), 0);    // v배열 전체를 0으로 할당
        copy(u.begin(), u.end(), v.begin() + m);    // u배열을 v배열의 m번째부터 넣음(v[0]-v[m] 까지는 0이 들어가있음)
    }
}

void rem_by_exp(LargeInteger u, int m, LargeInteger &v)
{
    if (u.size() == 0)
        v.resize(0);    // u가 비어있다면 배열 크기를 0으로
    else {
        int k = m < u.size() ? m : u.size();    // m < u의 크기라면 k=m, m >= u의 크기라면 k=u.size (k에 m, u의 크기 중 작은 값을 넣어준다)
        v.resize(k);    // 배열v의 사이즈를 k로
        copy(u.begin(), u.begin() + k, v.begin());  // u배열 시작부터 k번째까지 배열v에 넣는다
        remove_leading_zeros(v);
    }
}

void div_by_exp(LargeInteger u, int m, LargeInteger & v)
{
    if (u.size() == 0)
        v.resize(0);
    else {
        int k = m < u.size() ? u.size() - m : 0;    // m과 남는 숫자 개수는 사이즈와의 차이로 계산. 또한, 나누는 숫자가 더 크면 몫은 0
        v.resize(k);
        if (k != 0) {   // k가 0이면 v의 사이즈가 0이므로 그냥 v 전달!!! copy 불가!!
            copy(u.begin() + m, u.end(), v.begin());    // 배열v가 시작되는 위치는 m만큼을 지난 후부터
            remove_leading_zeros(v);
        }
    }
}

void prod(LargeInteger u, LargeInteger v, LargeInteger &r)
{
    cnt++;
    // 두 숫자가 들어있는 u, v 배열
    LargeInteger x, y, w, z;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;
    int n = max(u.size(), v.size());    // n에 배열 u, v 크기 중 큰 값 입력
    if (u.size() == 0 || v.size() == 0)
        r.resize(0);    // 배열 u, v 중 사이즈가 0인 배열이 있다면 (최종배열)r 사이즈를 0으로
    else if (n <= threshold)
        lmult(u, v, r);
    else {
        int m = n / 2;
        div_by_exp(u, m, x);    rem_by_exp(u, m, y);
        div_by_exp(v, m, w);    rem_by_exp(v, m, z);

        prod(x, w, t1); pow_by_exp(t1, 2*m, t2);
        prod(x, z, t3); prod(w,y,t4); ladd(t3, t4, t5); pow_by_exp(t5, m, t6);
        prod(y, z, t7); ladd(t2, t6, t8); ladd(t8, t7, r);
    }
}