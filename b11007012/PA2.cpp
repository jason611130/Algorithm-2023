#include <bits/stdc++.h>
#include <fstream>
using namespace std;
typedef struct Point{
    int col;
    int row;
    int val;
    Point *parent;
}Point;

struct Compare {
    bool operator()(const Point* a, const Point* b) {
        return a->val > b->val; // 使用 val 作為比較依據
    }
};

class graph {
private:
    int col_size;
    int row_size;
    int nets;
    int nowcol;
    int nowrow;
    int point = 0;
    int capacity = 0;
    int scol,srow;
    int col_dir[4] ;
    int row_dir[4] ;
    vector<vector<int>> Allpoint;
    vector<vector<int>> col_edge;
    vector<vector<int>> row_edge;
    vector<vector<Point>> array_2D;
    vector<vector<bool>> pass;
    stack<Point> pointlist;

public:
    // graph(int col_size, int row_size, int cap);
    void routing(int col1, int row1, int col2, int row2);
    void readfile(string file);
    void retrace();
    void outputfile(string file);
};


void graph::routing(int row1, int col1, int row2,int col2){
    int col_dir[4];
    int row_dir[4];

    if (col2 - col1 > 0 && row2 - row1 > 0) {
        int col_arr[] = {1, 0, 0, -1};
        int row_arr[] = {0, 1, -1, 0};

        for (int i = 0; i < 4; i++) {
            col_dir[i] = col_arr[i];
            row_dir[i] = row_arr[i];
        }
    }
    else if (col2 - col1 > 0 && row2 - row1 < -1) {
        int col_arr[] = {1, 0, 0, -1};
        int row_arr[] = {0, -1, 1, 0};
        for (int i = 0; i < 4; i++) {
            col_dir[i] = col_arr[i];
            row_dir[i] = row_arr[i];
        }
    }
    else if (col2 - col1 < -1 && row2 - row1 < -1) {
        int col_arr[] = {-1, 0, 0, 1};
        int row_arr[] = {0, -1, 1, 0};
        for (int i = 0; i < 4; i++) {
            col_dir[i] = col_arr[i];
            row_dir[i] = row_arr[i];
        }
    }
    else if (col2 - col1 < 0 && row2 - row1 > 0) {
        int col_arr[] = {-1, 0, 0, 1};
        int row_arr[] = {0, 1, -1, 0};
        for (int i = 0; i < 4; i++) {
            col_dir[i] = col_arr[i];
            row_dir[i] = row_arr[i];
        }
    }
    else if (col2 - col1 == 0 && row2 - row1 > 0) {
        int col_arr[] = {0, -1, 1, 0};
        int row_arr[] = {-1, 0, 0, 1};
        for (int i = 0; i < 4; i++) {
            col_dir[i] = col_arr[i];
            row_dir[i] = row_arr[i];
        }
    }
    else if (col2 - col1 == 0 && row2 - row1 < 0) {
        int col_arr[] = {0, -1, 1, 0};
        int row_arr[] = {1, 0, 0, -1};
        for (int i = 0; i < 4; i++) {
            col_dir[i] = col_arr[i];
            row_dir[i] = row_arr[i];
        }
    }
    else if (col2 - col1 > 0 && row2 - row1 == 0) {
        int col_arr[] = {1, 0, 0, -1};
        int row_arr[] = {0, -1, 1, 0};
        for (int i = 0; i < 4; i++) {
            col_dir[i] = col_arr[i];
            row_dir[i] = row_arr[i];
        }
    }
    else {
        int col_arr[] = {-1, 0, 0, 1};
        int row_arr[] = {0, -1, 1, 0};
        for (int i = 0; i < 4; i++) {
            col_dir[i] = col_arr[i];
            row_dir[i] = row_arr[i];
        }
    }
    
    int min_row = 0;
    int min_col = 0;
    bool jump_out = false;
    priority_queue<Point*, vector<Point*>, Compare> pq;

    for(int i=0;i<row_size;i++){
        for(int j=0;j<col_size;j++){
            array_2D[i][j].val = i==row1&&j==col1?0:INT_MAX;
            array_2D[i][j].col = j;
            array_2D[i][j].row = i;
            array_2D[i][j].parent = NULL;
        }
    }
    Point* temp;

    pq.push(&array_2D[row1][col1]);    
    while(!(min_col==col2&&min_row==row2&&jump_out)){
        temp = pq.top();
        // cout << temp->val<<endl;
        min_col = temp->col;
        min_row = temp->row;
        jump_out = true;
        
        // cout << "min_row,min_col = (" << min_row << ","<<min_col<<")"<<endl;
        for(int i=0;i<4;i++){       
            int new_col = min_col+col_dir[i];
            int new_row = min_row+row_dir[i];
            
            if(new_col<col_size&&new_row<row_size&&new_col>=0&&new_row>=0){
                // relax(min_col,min_row,new_col,new_row);
                int w;
                Point *P1;
                Point *P2;
                
                if(new_col-min_col==1){
                    w = col_edge[min_row][min_col];   
                }
                else if(new_row-min_row==1){
                    w = row_edge[min_row][min_col];  
                }
                else if(new_row-min_row==-1){
                    w = row_edge[min_row-1][min_col]; 
                }
                else{
                    w = col_edge[min_row][min_col-1]; 
                }
                P1 = &array_2D[min_row][min_col];
                P2 = &array_2D[new_row][new_col];
            	//cout << w<< endl;
            
                if(P2->val>P1->val+w){
                    P2->parent = P1;
                    P2->val = P1->val+w;
                    if(pass[new_row][new_col]==false){
                        pq.push(P2);
                        pass[new_row][new_col]==true;
                    }
                    
                }
            }
        }
        pq.pop();
    }
    scol = col2;
    srow = row2;
}

void graph::retrace(){
    Point *link_list;
    int bfr_col,bfr_row,now_col,now_row;
    link_list = &array_2D[srow][scol];
    while(link_list!= NULL){
        
        // cout << "( " << link_list->row << "," << link_list->col <<" )"<<endl;
        bfr_col = link_list->col;
        bfr_row = link_list->row;
        Point P;
        P.col = bfr_col;
        P.row = bfr_row;
        pointlist.push(P);
        link_list = link_list->parent;
        
        if(link_list != NULL){
            now_col = link_list->col;
            now_row = link_list->row;
            if(now_col-bfr_col==1){
            col_edge[bfr_row][bfr_col] = col_edge[bfr_row][bfr_col]>=capacity+1?capacity+10:col_edge[bfr_row][bfr_col]+1 ;//right
            }
            else if(now_row-bfr_row==1){
                row_edge[bfr_row][bfr_col] = row_edge[bfr_row][bfr_col]>=capacity+1?capacity+10:row_edge[bfr_row][bfr_col]+1;//down
            }
            else if(now_row-bfr_row==-1){
                row_edge[bfr_row-1][bfr_col] = row_edge[bfr_row-1][bfr_col]>=capacity+1?capacity+10:row_edge[bfr_row-1][bfr_col]+1;//up
            }
            else{
                col_edge[bfr_row][bfr_col-1] = col_edge[bfr_row][bfr_col-1]>=capacity+1?capacity+10:col_edge[bfr_row][bfr_col-1]+1;//left
            }
        }
    }
        
}
void graph::readfile(string file){
    ifstream fin(file,ios::in);
    
    char buffer[100];
    fin >> buffer;
    string s = buffer;

	if (s == "grid") {
		fin >> buffer;
		row_size = atoi(buffer);

		fin >> buffer;
		col_size = atoi(buffer);
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
	cout << nets <<endl;
    Allpoint.resize(nets, vector<int>(4, 0));
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
        Allpoint[i][0] = sx;
        Allpoint[i][1] = sy;
        Allpoint[i][2] = tx;
        Allpoint[i][3] = ty;
	}

    Point init;
    init.parent = NULL;
    init.val = 0;
    init.col = 0;
    init.row = 0;

    col_edge.resize(row_size, vector<int>(col_size-1, 1));
    row_edge.resize(col_size-1, vector<int>(row_size, 1));
    array_2D.resize(row_size, vector<Point>(col_size , init));
    pass.resize(row_size, vector<bool>(col_size , false));

}

void graph::outputfile(string output_file){
    
    ofstream outputFile(output_file);
    vector<Point> P;
    
    int tmpcol,tmprow;
    for(int i=0;i<nets;i++){
        
        routing(Allpoint[i][0],Allpoint[i][1],Allpoint[i][2],Allpoint[i][3]);
        retrace();
        //cout<<i<<endl;
        outputFile << i << " "<<pointlist.size()-1<<endl;
        while(!pointlist.empty()){
            P.push_back(pointlist.top());
            pointlist.pop();
        }
        for(int i=0;i<P.size()-1;i++){
            outputFile<< P[i].row  << " "<<P[i].col<< " "<<P[i+1].row  << " "<<P[i+1].col<<endl;
        }
        P.clear();
    }
    outputFile.close();
}

int main(int argc, char **argv){
    if(argc != 3)
    {
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
        exit(1);
    }

    // open the input file
    fstream fin;
    fin.open(argv[1], fstream::in);
    if(!fin.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }
    
    
    graph PA2;
    PA2.readfile(argv[1]);
    PA2.outputfile(argv[2]);

    return 0;
}