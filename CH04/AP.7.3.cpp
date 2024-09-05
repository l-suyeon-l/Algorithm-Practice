#include <iostream>
#include <vector>
#include <algorithm>
#define INF 999999

using namespace std;

typedef vector<vector<int>> matrix_t;
typedef vector<pair<int, int>> set_of_edges;
typedef pair<int, int> edge_t;

void dijkstra(int n, matrix_t& W, set_of_edges& F);
void path(int vtx, set_of_edges& F);

int main(void)
{
    int n, m, u, v, w, T;
    scanf("%d %d", &n, &m);
    matrix_t W;
    set_of_edges F;

    W.resize(n + 2, vector<int>(n + 2, INF));
    for (int i = 1; i <= n; i++)
        W[i][i] = 0;
    for(int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        W[u][v] = w;
    }
    scanf("%d", &T);
    vector<int> vtx(T);
    for (int i = 0; i < T; i++)
        scanf("%d", &vtx[i]);

    dijkstra(n, W, F);
    for (edge_t e: F) {
        u = e.first; v = e.second;
        cout << u << " " << v << " " << W[u][v] << endl;
    }
    for (int i = 0; i < T; i++) {
        path(vtx[i], F);
        if (i != T - 1)
            printf("\n");
    }

}

void dijkstra(int n, matrix_t& W, set_of_edges& F)
{
    int vnear, min;
    vector<int> touch(n + 1), length(n + 1);

    F.clear();
    for (int i = 2; i <= n; i++) {
        touch[i] = 1;
        length[i] = W[1][i];
        printf("%d", touch[i]);
        if (i != n)
            printf(" ");
        else printf("\n");
    }

    for (int k = n - 1; k > 0; k--) {
        min = INF;
        for (int i = 2; i <= n; i++)
            if (0 <= length[i] && length[i] < min) {
                min = length[i];
                vnear = i;
            }
        F.push_back(make_pair(touch[vnear], vnear));
        for (int i = 2; i <= n; i++)
            if (length[i] > length[vnear] + W[vnear][i]) {
                length[i] = length[vnear] + W[vnear][i];
                touch[i] = vnear;
            }
        length[vnear] = -1;

        for (int i = 2; i <= n; i++) {
            printf("%d", touch[i]);
            if (i != n)
                printf(" ");
            else printf("\n");
        }
    }
}

void path(int vtx, set_of_edges& F)
{
    vector<int> p;
    p.push_back(vtx);
    while(p[0] != 1) {
        for (int i = 0; i < F.size(); i++) {
            if (F[i].second == p[0]){
                p.insert(p.begin(), F[i].first);
            }
        }
    }
    for (int i = 0; i < p.size(); i++) {
        printf("%d", p[i]);
        if (i != p.size() - 1)
            printf(" ");
    }
}