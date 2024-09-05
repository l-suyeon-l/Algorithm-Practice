#include <iostream>
#include <vector>
#include <algorithm>
#define INF 999999

using namespace std;

typedef vector<vector<int>> matrix_t;
typedef vector<pair<int, int>> set_of_edges;
typedef pair<int, int> edge_t;

void prim(int n, matrix_t& W, set_of_edges& F);

int main(void)
{
    int n, m, u, v, w;
    scanf("%d %d", &n, &m);

    matrix_t W(n + 1, vector<int>(n + 1)); // vertex adjacency matrix
    set_of_edges F; // edges

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            W[i][j] = INF;
        W[i][i] = 0;
    }
    for(int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        W[u][v] = W[v][u] = w;
    }
    
    prim(n, W, F);
    for (edge_t e: F) {
        u = e.first; v = e.second;
        cout << u << " " << v << " " << W[u][v] << endl;
    }
}

void prim(int n, matrix_t& W, set_of_edges& F)
{
    int vnear, min;
    vector<int> nearest(n + 1), distance(n + 1);

    F.clear();  // F는 공집합
    for(int i = 2; i <= n; i++) {
        nearest[i] = 1;
        distance[i] = W[1][i];
        printf("%d", nearest[i]);
        if (i != n)
            printf(" ");
        else printf("\n");
    }

    for(int k = n - 1; k > 0; k--) {
        min = INF;
        for(int i = 2; i <= n; i++)
            if (0 <= distance[i] && distance[i] < min) {
                min = distance[i];
                vnear = i;
            }
        F.push_back(make_pair(vnear, nearest[vnear]));
        // edge_t edge = {vnear, nearest[vnear]};
        // F.push_back(edge);
        distance[vnear] = -1;
        for (int i = 2; i <= n; i++)
            if (distance[i] > W[i][vnear]) {
                distance[i] = W[i][vnear];
                nearest[i] = vnear;
            }

        for (int i = 2; i <= n; i++) {
            printf("%d", nearest[i]);      
            if (i != n)
                printf(" ");
            else printf("\n");
        }
    }
}