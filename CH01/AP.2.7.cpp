#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int mve = 0, call = 0, k;
void hanoi(int n, char src, char via, char dst) {
    call++;
    if (n == 1) {
        mve++;
        if (mve == k)
            printf("%c -> %c\n", src, dst);
    }
    else {
        hanoi(n-1, src, dst, via);
        hanoi(1, src, via, dst);
        hanoi(n-1, via, src, dst);
    }
}

int main() {
    int n;
    cin >> n;
    cin >> k;
    hanoi(n, 'A', 'B', 'C');
    cout << call;
}