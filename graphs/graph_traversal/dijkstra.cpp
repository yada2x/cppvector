#include <queue>
#include <vector>
#include <utility>

std::vector<int> dijkstra(const std::vector<std::vector<int>>& adj, int root) {
    // Assuming adjacency matrix, where adj[i][j] represents an edge if it is >= 0. If it is -1, there is no edge.
    int N = adj.size();
    std::vector<int> dist(N, INT_MAX);
    std::vector<int> pred(N, -1);

    dist[root] = 0;
    pred[root] = root;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.push({0, root}); // dist, start node

    while (!pq.empty()) {
        auto [currDist, currNode] = pq.top();
        pq.pop();

        if (currDist > dist[currNode]) {
            continue; // skip stale data
        }

        for (int nei = 0; nei < N; ++nei) {
            if (adj[currNode][nei] == -1 ) continue;
            if (currDist + adj[currNode][nei] < dist[nei]) {
                dist[nei] = currDist + adj[currNode][nei];
                pred[nei] = currNode;
                pq.push({dist[nei], nei});
            }
        }
    }
    return dist;
}