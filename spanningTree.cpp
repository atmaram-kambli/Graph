//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


class Solution {
  public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> graph[]) {
        priority_queue<pair<int, int>, vector< pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int>vis(V, 0);
        vector<pair<int, int>>mst;
        pq.push({0, 0});
        long long ans = 0;
        
        while(!pq.empty()) {
            auto p = pq.top();
            pq.pop();
            int wt = p.first;
            int node = p.second;
            if(vis[node] == 1) continue;
            vis[node] = 1;
            ans += wt;
            
            for(auto it :graph[node]) {
                int adjN = it[0];
                int weight = it[1]; 
                if(vis[adjN] == 0) {
                    pq.push({weight, adjN});
                }
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
