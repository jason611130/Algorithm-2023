#include <bits/stdc++.h>
using namespace std;
typedef struct Point{
    short x;
    short y;
}Point;

class graph {
private:
    short x_size;
    short y_size;
    short nowx;
    short nowy;
    short point = 0;
    short capacity = 2;
    vector<vector<short>> x_edge;
    vector<vector<short>> y_edge;
    vector<vector<short>> array_2D;
    const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    graph(short x_size, short y_size, short cap);
    void showgraph();
    void setpoint(short x1, short y1, short x2, short y2);
    bool isVaild(short nowx, short nowy,short afterx, short aftery);
    void routing(short x1, short y1,short targetx,short targety);
    void bfs(short x1, short y1,short targetx,short targety);
};

graph::graph(short x_size, short y_size, short cap) : x_size(x_size), y_size(y_size), capacity(cap) {
    x_edge.resize(y_size - 1, vector<short>(x_size, 0));
    y_edge.resize(y_size, vector<short>(x_size - 1, 0));
    array_2D.resize(y_size, vector<short>(x_size, 0));
    capacity = cap;
}

void graph::showgraph() {
    for (int i = 0; i < y_size - 1; i++) {
        for (int j = 0; j < x_size; j++) {
            cout << x_edge[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < y_size; i++) {
        for (int j = 0; j < x_size - 1; j++) {
            cout << y_edge[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < y_size; i++) {
        for (int j = 0; j < x_size; j++) {
            cout << array_2D[i][j] << " ";
        }
        cout << endl;
    }
}

void graph::setpoint(short x1, short y1, short x2, short y2) {
    point = point + 1;
    array_2D[y1][x1] = point;
    array_2D[y2][x2] = point;
}


void graph::bfs(short x1,short y1, short x2,short y2){
    vector<vector<bool>> visited;
    visited.resize(y_size,vector<bool>(x_size,false));
    queue<Point> q;
    queue<int> y_arr;

    visited[y1][x1] = true;
    Point p;
    p.x = x1;
    p.y = y1;
    q.push(p);
    
    while(!q.empty()){
        Point u = q.front();
        cout << "x = "<< u.x << endl;
        cout << "y = "<< u.y << endl;
        q.pop();
        
        for(){
            if(visited[v.y][v.x]==false){
                visited[v.y][v.x] = true;
                q.push(v);
            }
        }
    }
}


int main() {
    graph myGraph(4, 4, 2);

    myGraph.setpoint(1, 1, 2, 2);
    myGraph.setpoint(3, 3, 3, 1);
    myGraph.showgraph();
    

    return 0;
}