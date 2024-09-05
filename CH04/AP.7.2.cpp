#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct edge {
    int u, v, w;
} edge_t;
struct edge_compare {
    bool operator()(edge_t e1, edge_t e2) {
        if (e1.w > e2.w) 
            return true;
        else return false;
    }
};
typedef vector<edge_t> set_of_edges;
typedef priority_queue<edge_t, vector<edge_t>, edge_compare> PriorityQueue;
vector<int> dset;

void dset_init(int n);
int dset_find(int i);
void dset_merge(int p, int q);
void kruskal(int n, int m, set_of_edges& E, set_of_edges& F);

int main(void)
{
    int n, m, u, v, w;

    scanf("%d %d", &n, &m);
    set_of_edges E, F;
    edge_t temp;

    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &temp.u, &temp.v, &temp.w);
        E.push_back(temp);
    } 
    kruskal(n, m, E, F);

    for(int i = 0; i < F.size(); i++) {
        printf("%d %d %d", F[i].u, F[i].v, F[i].w);
        if (i != F.size() - 1)
            printf("\n");
    }
}

void dset_init(int n)
{
    dset.resize(n + 1);
    for(int i = 1; i <= n; i++)
        dset[i] = i;
}

int dset_find(int i)
{
    while(dset[i] != i)
        i = dset[i];
    return i;
}

void dset_merge(int p, int q)
{
    dset[p] = q;
}

void kruskal(int n, int m, set_of_edges& E, set_of_edges& F)
{
    int p, q;
    edge_t e, temp;
    PriorityQueue PQ;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (E[j].w > E[j + 1].w) {
                temp = E[j];
                E[j] = E[j + 1];
                E[j + 1] = temp;
            }
        }
    }

    for (edge_t e: E)
        PQ.push(e);
    
    F.clear();  // F는 공집합
    dset_init(n);
    while(F.size() < n - 1) {
        e = PQ.top(); PQ.pop();
        p = dset_find(e.u);
        q = dset_find(e.v);
        if (p != q) {
            dset_merge(p, q);
            F.push_back(e);
        }
    }
}