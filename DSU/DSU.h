#ifndef DSU_H
#define DSU_H

#include <vector>

class DSU {
    public:
        DSU(int size);
        
        int find(int x);
        void union_by_rank(int x, int y);
        void union_by_size(int x, int y);

    private:
        std::vector<int> parent;
        std::vector<int> rank;
};

#endif 
