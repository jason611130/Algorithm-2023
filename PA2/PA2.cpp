#include <bits/stdc++.h>

using namespace std;

class graph {
private:
    short x;
    short y;
    short point=0;
    vector<vector<short>> x_edge;
    vector<vector<short>> y_edge;
    vector<vector<short>> array_2D;

public:
    graph(short x, short y);
    void showgraph();
    void setpoint(short start1,short end1,short start2,short end2);
};

graph::graph(short x, short y) : x(x), y(y) {
    // 創建 x_edge 的行數為 x，列數為 y-1 的二維向量，並初始化所有元素為1
    x_edge.resize(y-1, vector<short>(x, 0));
    // 創建 y_edge 的行數為 y-1，列數為 x 的二維向量，並初始化所有元素為1
    y_edge.resize(y, vector<short>(x-1, 0));
    array_2D.resize(x,vector<short>(y, 0));
}


void graph::showgraph() {
    for (int i = 0; i < y-1; i++) {
        for (int j = 0; j < x; j++) {
            cout << x_edge[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x-1; j++) {
            cout << y_edge[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << array_2D[i][j] << " ";
        }
        cout << endl;
    }
}

void graph::setpoint(short x1,short y1,short x2,short y2){
    point = point+1;
    array_2D[x1][y1] = point;
    array_2D[x2][y2] = point;
    
}

int main() {
    graph myGraph(10, 10);
    
    myGraph.setpoint(1,1,2,2);
    myGraph.setpoint(3,3,4,4);
    myGraph.showgraph();
    return 0;
}