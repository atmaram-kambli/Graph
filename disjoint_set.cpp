#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
  private: 
    vector<int>rank, parent, siz;
  public:
    DisjointSet(int n) {
        rank.resize(n+1, 0);
        siz.resize(n+1, 1);
        parent.resize(n+1, 0);
        for(int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    int findParent(int node) {
        if(node == parent[node]) {
            return node;
        }
        return parent[node] = findParent(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findParent(u);          // ulp_u --> ultimate parent of u
        int ulp_v = findParent(v);          // ulp_v --> ultimate parent of v
        
        if(ulp_u == ulp_v) return;          // if parent of u and v are same, no need to perform unionByRank
        if(rank[ulp_u] < rank[ulp_v]) {     // if ulp_u has smaller rank than that of ulp_v
            parent[ulp_u] = ulp_v;          // make ulp_v as parent of ulp_u && no need to update rank
        }
        else if(rank[ulp_v] < rank[ulp_u]) {   // if ulp_v has smaller rank than that of ulp_u
            parent[ulp_v] = ulp_u;             // make ulp_u as parent of ulp_v && no need to update rank
        }
        else {                          // if they have same rank
            parent[ulp_u] = ulp_v;      // make anyone one of them parent of another
            rank[ulp_v]++;              // increase the rank of parent by 1
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findParent(u);          // ulp_u --> ultimate parent of u
        int ulp_v = findParent(v);          // ulp_v --> ultimate parent of v

        if(ulp_u == ulp_v) return;          // if parent of u and v are same, no need to perform unionBySize

        if(siz[ulp_u] < siz[ulp_v]) {       // if ulp_u has smaller siz than that of ulp_v
            parent[ulp_u] = ulp_v;          // make ulp_v as parent of ulp_u
            siz[ulp_v] += siz[ulp_u];       // update the siz of parent
        }
        else {                              // // if ulp_u has smaller or equal siz to that of ulp_v
            parent[ulp_v] = ulp_u;          // make ulp_v as parent of ulp_u
            siz[ulp_u] += siz[ulp_v];       // update the siz of parent
        }
    }


};

int main() {
    // Example
    DisjointSet ds(7);
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);

    if(ds.findParent(3) == ds.findParent(7)) {
        cout << "Same component!\n";
    }else {
        cout << "Not same component!\n";
    }

    ds.unionByRank(3, 7);

    if(ds.findParent(3) == ds.findParent(7)) {
        cout << "Same component!!\n";
    }else {
        cout << "Not same component!\n";
    }

    return 0;
}