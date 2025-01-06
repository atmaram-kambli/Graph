//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends


class DisjointSet {
  private: 
    vector<int>rank, parent;
  public:
    DisjointSet(int n) {
        rank.resize(n+1, 0);
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
};

class Solution {
  public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> graph[]) {
        vector<pair<int, pair<int, int>>> edges;
        for(int i = 0; i < V; i++) {
            for(auto it : graph[i]) {
                edges.push_back({it[1], {i, it[0]}});
            } 
        }
        sort(edges.begin(), edges.end());
        DisjointSet ds(V);
        
        int ans = 0;
        for(auto edge : edges) {
            int wt = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            
            if(ds.findParent(u) != ds.findParent(v)) {
                ans += wt;
                ds.unionByRank(u, v);
            }
        }
        return ans;
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i = 0;
        while (i++ < E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1, t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }

        Solution obj;
        cout << obj.spanningTree(V, adj) << "\n";

        cout << "~"
             << "\n";
    }

    return 0;
}

// } Driver Code Ends