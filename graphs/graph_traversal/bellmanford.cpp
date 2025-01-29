#include <vector>

std::vector<int> bellmanford(const std::vector<std::vector<int>>& adj, int root) {
    int N = adj.size();
    std::vector<int> dist(N, INT_MAX);
    std::vector<int> pred(N, -1);
    dist[root] = 0;
    pred[root] = root;

    for (int i = 0; i < N; ++i) {
        bool change = false;

        for (int j = 0; j < N; ++j) {
            if (dist[i] < INT_MAX) {
                if (dist[j] > dist[i] + adj[i][j]) {
                    pred[j] = i;
                    dist[j] = dist[i] + adj[i][j];
                    change = true;
                }
            }
        }

        if (!change) break;
    }
    return dist;
}