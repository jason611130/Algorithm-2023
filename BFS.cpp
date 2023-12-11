#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:    
        int vertex;
        vector<list<int>> adj;
    public:
        Graph(int vertex);
        void addEdge(int a,int b);
        void BFS(int start); 
};

Graph::Graph(int vertex){
    this->vertex = vertex;
    adj.resize(vertex);
}

void Graph::addEdge(int a,int b){
    adj[a].push_back(b);
}

void Graph::BFS(int start){
    vector<bool> visited;
    visited.resize(vertex);
    queue<int> q; 

    visited[start] = true;
    q.push(start);
    
    while(!q.empty()){
        int u = q.front();
        cout << u << endl;
        q.pop();
        for(auto v:adj[u]){
            if(visited[v]==false){
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main(){
    Graph g(5);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,2);
    g.addEdge(2,0);
    g.addEdge(2,3);
    g.addEdge(3,2);
    g.addEdge(3,4);
    g.addEdge(4,3);
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(3);
 
    return 0;
}