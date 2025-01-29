#include <vector>
#include "DSU.h"

DSU::DSU(int size) {
    parent.resize(size);
    rank.resize(size, 1); // init rank to 1

    for (int i = 0; i < size; ++i) {
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

}

void DSU::union_by_size(int x, int y) {

}
