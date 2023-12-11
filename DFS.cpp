#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
        int vertex;
        int time = 0;
        vector<string>color;
        vector<int> start_time;
        vector<int> end_time;
        vector<list<int>> adj;
    public:
        Graph(int vertex);
        void addEdge(int a,int b);
        void DFS();
        void DFS_Visit(int v);
 
};

Graph::Graph(int vertex){
    this->vertex = vertex;
    adj.resize(vertex);
    start_time.resize(vertex,0);
    end_time.resize(vertex,0);
    color.resize(vertex,"White");
}

void Graph::addEdge(int a,int b){
    adj[a].push_back(b);
}

void Graph::DFS_Visit(int u){ 
    this->time = this->time+1;
    start_time[u] = this->time;
    color[u] = "Gray";
    cout<< "Gray = " << u << endl; 
    for(auto v:adj[u]){
        if(color[v]=="White"){
            DFS_Visit(v);
        }
    }
    color[u] = "Black";
    cout<< "Black = " << u << endl;
}
void Graph::DFS(){
    for(int u=0;u<vertex;u = u+1){
        if(color[u]=="White"){
            DFS_Visit(u);
        }
    }
}



int main(){
    Graph g(6);
    g.addEdge(0,3);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,1);
    g.addEdge(4,5);
    g.addEdge(4,2);

    g.DFS();

    
}