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

class routing{
    private:
        int nets,row,column,capacity;
        vector<vector<char>> maze;
        vector<vector<Node>> nodeInfo;
        vector<vector<Point>> Allpoint;
        vector<vector<short>> horizontal_edge;
        vector<vector<short>> vertical_edge;
    public:
        void readfile();
        int bfs(vector<vector<char>>& maze, Point start, Point end, vector<vector<Node>>& nodeInfo,vector<Point>& pointlist,int capacity);
        void outputfile();
        void test();
};
void routing::test(){
    cout<<"start"<< vertical_edge[59][45]<<endl;
}
int routing::bfs(vector<vector<char>>& maze, Point start, Point end, vector<vector<Node>>& nodeInfo,vector<Point>& pointlist,int capacity) {
    
    vector<vector<bool>> visited(row, vector<bool>(column, false));
    queue<Node> q;

    Node startNode = {start, 0, {-1, -1}};
    q.push(startNode);
    visited[start.row][start.col] = true;
    nodeInfo[start.row][start.col] = startNode;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    bool pass;
            
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
            // cout << "i = "<<i<<endl;
            
            pass = true;
            // cout<<"start"<< vertical_edge[59][22]<<endl;
            
            // && maze[newRow][newCol] != '#' 
            if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < column && !visited[newRow][newCol]) {
//                cout << "i = "<< i <<endl;
//                cout <<"current.point.row = " <<current.point.row << endl;
//                cout <<"current.point.col = " <<current.point.col << endl;
//                
//                switch(i){
//                case 0:
//                    // cout <<"current.point.row = " <<current.point.row-1 << endl;
//                    // cout <<"current.point.col = " <<current.point.col << endl;
//                    cout << "capacity = " << horizontal_edge[current.point.row-1][current.point.col]<<endl;
//                    cout << endl;
//                    if(horizontal_edge[current.point.row-1][current.point.col]<capacity){
//                        horizontal_edge[current.point.row-1][current.point.col] += 1;
//                        pass = true;
//                    }    
//                break;
//                case 1:
//                    cout << "capacity = " << vertical_edge[current.point.row][current.point.col]<<endl;
//                    cout << endl;
//                    if(vertical_edge[current.point.row][current.point.col]<capacity){
//                        vertical_edge[current.point.row][current.point.col] += 1;
//                        pass = true;
//                    }  
//                break;
//                case 2:
//                    cout << "capacity = " << horizontal_edge[current.point.row][current.point.col]<<endl;
//                    cout << endl;
//                    // cout <<"current.point.row = " <<current.point.row << endl;
//                    // cout <<"current.point.col = " <<current.point.col << endl;
//                    if(horizontal_edge[current.point.row][current.point.col]<capacity){
//                        horizontal_edge[current.point.row][current.point.col] += 1;
//                        pass = true;
//                    }  
//                break;
//                case 3:
//                    cout << "capacity = " << vertical_edge[current.point.row][current.point.col-1]<<endl;
//                    cout << endl;
//                    // cout <<"current.point.row = " <<current.point.row << endl;
//                    // cout <<"current.point.col = " <<current.point.col-1 << endl;
//                    if(vertical_edge[current.point.row][current.point.col-1]<capacity){
//                        vertical_edge[current.point.row][current.point.col-1] += 1;
//                        pass = true;
//                    }
//                break;
//                }
                if(pass){
                    Node newNode = {{newRow, newCol}, current.distance + 1, current.point};
                    q.push(newNode);
                    visited[newRow][newCol] = true;
                    nodeInfo[newRow][newCol] = newNode;
                }
            }
        }
    }

    return -1; // No path found
}

void routing::readfile(){
    ifstream fin("60x60.in",ios::in);
    
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
    Allpoint.resize(nets, vector<Point>(2, {0,0}));
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
    maze.resize(row, vector<char>(column,'.'));
    nodeInfo.resize(row, vector<Node>(column));
    horizontal_edge.resize(row - 1, vector<short>(column, 0));
    vertical_edge.resize(row, vector<short>(column - 1, 0));
}

void routing::outputfile(){
    const char* file_path = "60x60.out";
    ofstream outputFile(file_path);
     
    for(int i=0;i<nets;i++){
        vector<Point> pointlist;
//        cout<< "number_of_nets_is  "<< i <<endl;
        int result = bfs(maze, Allpoint[i][0], Allpoint[i][1], nodeInfo,pointlist,capacity);
        outputFile << i << " " << result<<endl;
        for(int i=0;i<pointlist.size()-1;i++){
            outputFile << pointlist[i].row<<" "<<pointlist[i].col <<" "<<pointlist[i+1].row<<" "<<pointlist[i+1].col << endl;
        }
    }
    outputFile.close();
}
int main() {
    routing PA2;
    PA2.readfile();
    PA2.test();
    PA2.outputfile();
    return 0;
}