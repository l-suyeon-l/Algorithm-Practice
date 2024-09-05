#include <iostream>
#include <vector>
#include <stdlib.h>
#define INF 999999

using namespace std;

int cnt, num;
typedef vector<vector<int>> matrix_t;
typedef struct node* node_ptr;
typedef struct node {
    int key;
    node_ptr left, right;
} node_t;

int minimum(int i, int j, int& mink, vector<int>& d, matrix_t& M);
void optsearchtree(int n, vector<int>& p, matrix_t& A, matrix_t& R);
node_ptr create_node(int k);
node_ptr tree(int i, int j, vector<int>& keys, matrix_t& R);
void preorder(node_ptr ptr);
void inorder(node_ptr ptr);

int main(void)
{
    int n;
    scanf("%d", &n);
    vector<int> K(n + 1), p(n + 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &K[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);

    matrix_t A(n + 2, vector<int>(n + 1)), R(n + 2, vector<int>(n + 1));
    optsearchtree(n, p, A, R);
    for (int i = 1; i <= n + 1; i++) {
        for (int j = i - 1; j <= n; j++) {
            printf("%d", A[i][j]);
            if (j != n)
                printf(" ");
        }
        if (i != n + 1)
            printf("\n");
    }
    printf("\n");
    for (int i = 1; i <= n + 1; i++) {
        for (int j = i - 1; j <= n; j++) {
            printf("%d", R[i][j]);
            if (j != n)
                printf(" ");
        }
        if (i != n + 1)
            printf("\n");
    }
    printf("\n");
    printf("%d", A[1][n]);
    printf("\n");

    node_ptr bTree = tree(1, n, K, R);
    num = n; cnt = 1;
    preorder(bTree);
    printf("\n");
    cnt = 1;
    inorder(bTree);
}

int minimum(int i, int j, int& mink, vector<int>& d, matrix_t& M)
{
    int minValue = INF, value, psum = 0;
    for (int k = i; k <= j; k++) {
        value = M[i][k - 1] + M[k + 1][j];
        if (minValue > value) {
            minValue = value;
            mink = k;
        }
    }
    for (int m = i; m <= j; m++) {
        psum += d[m];
    }
    return minValue + psum;
}

void optsearchtree(int n, vector<int>& p, matrix_t& A, matrix_t& R)
{
    int i, j, k, diagonal;
    for (i = 1; i <= n; i++) {
        A[i][i - 1] = 0; A[i][i] = p[i];
        R[i][i - 1] = 0; R[i][i] = i;
    }
    A[n + 1][n] = 0; R[n + 1][n] = 0;

    for (diagonal = 1; diagonal <= n - 1; diagonal++)
        for (i = 1; i <= n - diagonal; i++) {
            j = i + diagonal;
            A[i][j] = minimum(i, j, k, p, A);
            R[i][j] = k;
        }
}

node_ptr create_node(int k)
{
    node_ptr nNode = (node_ptr)malloc(sizeof(node_ptr));
    nNode->key = k;

    return nNode;
}

node_ptr tree(int i, int j, vector<int>& keys, matrix_t& R)
{
    int k = R[i][j];
    if (k == 0)
        return NULL;
    else {
        node_ptr node = create_node(keys[k]);
        node->left = tree(i, k - 1, keys, R);
        node->right = tree(k + 1, j, keys, R);
        return node;
    }
}

void preorder(node_ptr ptr)
{
    if (ptr) {
        printf("%d", ptr->key);
        if (cnt++ != num)
            printf(" ");
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void inorder(node_ptr ptr)
{
    if (ptr) {
        inorder(ptr->left);
        printf("%d", ptr->key);
        if (cnt++ != num)
            printf(" ");
        inorder(ptr->right);
    }
}