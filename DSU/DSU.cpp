#include <vector>
#include "DSU.h"

DSU::DSU(int N) {
    parent.resize(N);
    rank.resize(N, 1); // init rank to 1
    size.resize(N, 1);
    
    for (int i = 0; i < N; ++i) {
        parent[i] = i;
    }
}


int DSU::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // with path compression
    }
    return parent[x];

    // if (parent[x] == x) {
    //     return x;
    // }
    // return find(parent[x]);
}

void DSU::union_by_rank(int x, int y) {
    int parentX = find(x);
    int parentY = find(y);

    if (parentX != parentY) {
        if (rank[parentX] < rank[parentY]) {
            std::swap(parentX, parentY); // swap the two, ensuring parentX has the bigger rank.
        } 
        parent[parentY] = parentX;
        if (rank[parentY] == rank[parentX]) {
            ++rank[parentX];
        }
    }
}

void DSU::union_by_size(int x, int y) {
    int parentX = find(x);
    int parentY = find(y);

    if (parentX != parentY) {
        if (size[parentX] < size[parentY]) {
            parent[parentX] = parentY;
            size[parentY] += size[parentX];
        } else {
            parent[parentY] = parentX;
            size[parentX] += size[parentY];
        }
    }
}
