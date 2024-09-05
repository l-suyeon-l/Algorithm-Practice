// vs code 작동안함 vs studio로 켜기 => new node_t로 해결
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>    // priority_queue
#include <map>      // map<key, value>

using namespace std;

typedef struct node* node_ptr;
typedef struct node {
    char symbol;        // character(문자)
    int frequency;      // 해당 character의 빈도수
    node_ptr left;
    node_ptr right;
} node_t;

struct compare {
    bool operator()(node_ptr p, node_ptr q) {
        return p->frequency > q->frequency;     // 각 노드의 frequency를 비교하여 오름차순으로 정렬
    }
};

typedef priority_queue<node_ptr, vector<node_ptr>, compare> PriorityQueue;  // compare 조건에 맞게 Queue 정렬

node_ptr create_node(char s, int f);
void huffman(int n, PriorityQueue& PQ);
void make_encoder(node_ptr node, string code, map<char, string>& encoder);
void encode(string t, map<char, string>& encoder);
void decode(node_ptr root, node_ptr node, string s, int i);
void preorder(node_ptr ptr);
void inorder(node_ptr ptr);

int main(void)
{
    int n, T1, T2;
    scanf("%d", &n);    // n = 문자의 개수
    vector<char> S(n + 1);  // 벡터 S = 문자
    vector<int> F(n + 1);   // 벡터 F = 문자의 빈도수 (오름차순 정렬)
    PriorityQueue PQ;

    for (int i = 1; i <= n; i++)
        cin >> S[i];
    for (int i = 1; i <= n; i++)
        cin >> F[i];

    scanf("%d", &T1);
    vector<string> t1(T1 + 1);
    for (int i = 1; i <= T1; i++)
        cin >> t1[i];
    scanf("%d", &T2);
    vector<string> t2(T2 + 1);
    for (int i = 1; i <= T2; i++)
        cin >> t2[i];

    for (int i = 1; i <= n; i++) {
        node_ptr N = create_node(S[i], F[i]);
        PQ.push(N);                             // 문자 S[i], 빈도수 F[i]가 있는 노드 N을 PQ에 push
    }
    huffman(n, PQ);                             // PQ를 tree로 변환

    preorder(PQ.top());                         // PQ.top은 트리의 root
    cout << "\n";

    inorder(PQ.top());
    cout << "\n";

    map<char, string> encoder;
    string code;
    make_encoder(PQ.top(), code, encoder);      // code 해석표 만들기

    for (int i = 1; i <= T1; i++) {
        encode(t1[i], encoder);         // 문자열 하나씩(t1[i]) encoding
        cout << "\n";
    }
    for (int i = 1; i <= T2; i++) {
        int k = 0;
        decode(PQ.top(), PQ.top(), t2[i], k);   // 허프만 코드 하나씩(t2[i]) decoding 
        if (i != T2)
            cout << "\n";
    }
}

node_ptr create_node(char s, int f)
{
    node_ptr nNode = new node_t;
    nNode->symbol = s;
    nNode->frequency = f;
    nNode->left = NULL;
    nNode->right = NULL;

    return nNode;
}

void huffman(int n, PriorityQueue& PQ)
{
    for (int i = 1; i <= n - 1; i++) {
        node_ptr p = PQ.top(); PQ.pop();                            // PQ의 첫 번째 노드(pop 해줘야함)
        node_ptr q = PQ.top(); PQ.pop();                            // PQ의 두 번째 노드(pop 해줘야함)
        node_ptr r = create_node('+', p->frequency + q->frequency); // internal 노드이므로 심볼 = '+', frequency = p + q
        r->left = p;
        r->right = q;                                               // r tree의 left, right를 각각 p, q로
        PQ.push(r);                                                 // PQ에 r tree 넣기. frequency 순서에 맞게 정렬됨
    }
}

void make_encoder(node_ptr node, string code, map<char, string>& encoder)
{
    if (node->symbol != '+') {          // leaf node이면
        encoder[node->symbol] = code;   // 해당 code를 encoder의 symbol자리에 저장
    }
    else {                                                  // internal node이면
        make_encoder(node->left, code + "0", encoder);      // 왼쪽 노드로 가면 code에 '0' 추가
        make_encoder(node->right, code + "1", encoder);     // 오른쪽 노드로 가면 code에 '1' 추가
    }
}

// afdbce -> 00100111101101111
void encode(string t, map<char, string>& encoder)
{
    int k = 0;
    while (t[k] != 0) {                                                     // 문자열 t[k]의 문자 하나씩
        for (auto iter = encoder.begin(); iter != encoder.end(); iter++)    // encoder 첫 요소부터 마지막 요소까지 순환
            if (t[k] == iter->first) {          // 문자와 encoder 문자가 같으면
                cout << iter->second;           // 해당 encoder의 code 출력
                break;
            }
        k++;    // 문자열의 다음 문자
    }
}

// 00100111101101111 -> afdbce
void decode(node_ptr root, node_ptr node, string s, int i)
{
    if (i <= s.length()) {                  // i이 문자열 s 길이보다 작을 동안 : i는 (☆)에서 증가 & 허프만 코드가 끝나기 전에 (★)에서 회귀
        if (node->symbol != '+') {                  // leaf node이면
            cout << node->symbol;                   // 해당 symbol 출력
            decode(root, root, s, i);               // 다시 root 노드로 회귀 . . . (★) (다음 코드를 decode하기 위해)
        }
        else {                                                      // internal node이면
            if (s[i] == '0') decode(root, node->left, s, i + 1);    // 허프만 코드가 '0'이면 left 노드로 이동   . . . (☆)
            else decode(root, node->right, s, i + 1);               // 허프만 코드가 '1' 이면 right 노드로 이동 . . . (☆)
        }
    }
}

void preorder(node_ptr ptr)
{
    if (ptr) {
        cout << ptr->symbol << ":" << ptr->frequency << " ";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void inorder(node_ptr ptr)
{
    if (ptr) {
        inorder(ptr->left);
        cout << ptr->symbol << ":" << ptr->frequency << " ";
        inorder(ptr->right);
    }
}

/*void postorder(node_ptr ptr)
{
    if (ptr) {
        postorder(ptr->left);
        postorder(ptr->right);
        cout << ptr->symbol << ":" << ptr->frequency << " ";
    }
}*/