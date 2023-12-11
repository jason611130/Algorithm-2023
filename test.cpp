#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cstdlib>
#include <fstream>
using namespace std;

struct Point {
    int row, col;
};

struct Node {
    Point point;
    int distance;
    Point parent;
};

int bfs(vector<vector<char>>& maze, Point start, Point end, vector<vector<Node>>& nodeInfo,vector<Point>& pointlist,int capacity) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<short>> x_edge;
    vector<vector<short>> y_edge;
    x_edge.resize(rows - 1, vector<short>(cols, 0));
    y_edge.resize(rows, vector<short>(cols - 1, 0));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<Node> q;

    Node startNode = {start, 0, {-1, -1}};
    q.push(startNode);
    visited[start.row][start.col] = true;
    nodeInfo[start.row][start.col] = startNode;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.point.row == end.row && current.point.col == end.col) {
            stack<Point> pathStack;
            Point trace = end;
//            cout<<index<<" "<<current.distance<<endl;
            while (trace.row != -1 && trace.col != -1) {
                pathStack.push(trace);
                trace = nodeInfo[trace.row][trace.col].parent;
            }
            while (!pathStack.empty()) {
                Point p = pathStack.top();
                pointlist.push_back(p);
                pathStack.pop();
            }
            return current.distance;
        }

        for (int i = 0; i < 4; ++i) {
            int newRow = current.point.row + dr[i];
            int newCol = current.point.col + dc[i];

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                maze[newRow][newCol] != '#' && !visited[newRow][newCol]) {
                Node newNode = {{newRow, newCol}, current.distance + 1, current.point};
                q.push(newNode);
                visited[newRow][newCol] = true;
                nodeInfo[newRow][newCol] = newNode;
            }
        }
    }

    return -1; // No path found
}

int main() {
    int nets,row,column,capacity;
    ifstream fin("20x20.in",ios::in);
    
    char buffer[100];
    fin >> buffer;
    string s = buffer;

	if (s == "grid") {
		fin >> buffer;
		row = atoi(buffer);

		fin >> buffer;
		column = atoi(buffer);
    }

	fin >> buffer;
	s = buffer;

	if (s == "capacity") {
		fin >> buffer;
		capacity = atoi(buffer);
	}

	fin >> buffer;
	s = buffer;
	fin >> buffer;
	s = buffer;

	if (s == "net") {
		fin >> buffer;
		nets = atoi(buffer);
	}
    vector<vector<Point>> Allpoint(nets, vector<Point>(2, {0,0}));
	for (int i = 0; i < nets; ++i) {
		fin >> buffer;
		int netID = atoi(buffer);
		fin >> buffer;
		int sx = atoi(buffer);
		fin >> buffer;
		int sy = atoi(buffer);
		fin >> buffer;
		int tx = atoi(buffer);
		fin >> buffer;
		int ty = atoi(buffer);
        Allpoint[i][0] = {sx,sy};
        Allpoint[i][1] = {tx,ty};
	}
    
    const char* file_path = "output.txt";
    ofstream outputFile(file_path);

    vector<vector<char>> maze(row, vector<char>(column,'.'));
    vector<vector<Node>> nodeInfo(row, vector<Node>(column)); // 用於保存每個節點的信息
    for(int i=0;i<nets;i++){
        vector<Point> pointlist;
        int result = bfs(maze, Allpoint[i][0], Allpoint[i][1], nodeInfo,pointlist,capacity);
        outputFile << i << " " << result<<endl;
        for(int i=0;i<pointlist.size()-1;i++){
            outputFile << pointlist[i].col<<" "<<pointlist[i].row <<" "<<pointlist[i+1].col<<" "<<pointlist[i+1].row << endl;

        }
    }
    outputFile.close();
    
    return 0;
}