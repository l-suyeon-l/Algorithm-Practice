#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> sequence_of_integer;

bool is_feasible(sequence_of_integer& K, sequence_of_integer& deadline);
void schedule(int n, sequence_of_integer& deadline, sequence_of_integer& J);

int main(void)
{
    int n;
    scanf("%d", &n);    // job의 개수
    sequence_of_integer J(n + 1), deadline(n + 1), profit(n + 1);   // job, deadline, profit 정보를 담을 int형 벡터
    for (int i = 1; i <= n; i++)    // deadline 입력받기
        scanf("%d", &deadline[i]); 
    for (int i = 1; i <= n; i++)    // profit 입력받기 (내림차순 정렬)
        scanf("%d", &profit[i]);

    schedule(n, deadline, J);       // 배열 J에는 feasible sequence가 저장됨
                                    // profit 내림차순되어 있으므로 자동으로 최대 profit

    int sum = 0, i = 1;
    while(J[i] != 0)
        sum += profit[J[i++]];      // 최대이익(feasible sequence의 profit의 합)
    printf("%d\n", sum);

    i = 1;                          // J의 처음부터 다시
    while(J[i] != 0) {              // feasible sequence의 profit 순서대로 출력
        printf("%d", profit[J[i++]]);
        if (J[i] != 0)
            printf(" ");
    }        
}

bool is_feasible(sequence_of_integer& K, sequence_of_integer& deadline)
{
    for (int i = 1; i < K.size(); i++)
        if (i > deadline[K[i]])         // ppt p.61 참고 : 정해진 자리(i) 보다 deadline이 작으면 안됨
            return false;               // 작으면 기각, J에 저장안됨
        return true;                    // deadline이 타당하면 J에 저장
}

void schedule(int n, sequence_of_integer& deadline, sequence_of_integer& J)
{
    sequence_of_integer K;
    J.clear();          // 벡터 J 초기화
    J.push_back(0);     // J[0] = 0
    J.push_back(1);     // J[1] = 1
    for (int i = 2; i <= n; i++) {                              // i는 새로 추가된 Job의 위치(Job을 추가하면서 feasibility 확인함)
        K.resize(J.size());
        copy(J.begin(), J.end(), K.begin());                    // 벡터 K <== 벡터 J 저장

        int j = 1;
        // j < K.size()는 K[j]가 유효하기 위한 조건
        while(j < K.size() && deadline[K[j]] <= deadline[i])    // deadline이 작은 것부터 벡터 K에 정렬
            j++;                                                // deadline[i](새로 추가할 Job의 deadline) 보다 기존의 deadline이 작으면 j++
        K.insert(K.begin() + j, i);                             // 그 K벡터의 j 위치에 추가 : deadline 오름차순 정렬
        if (is_feasible(K, deadline)) {
            J.resize(K.size());                             
            copy(K.begin(), K.end(), J.begin());                // feasible하면 벡터 J <== 벡터 K 저장
        }
    }
}