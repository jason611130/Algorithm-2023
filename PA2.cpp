#include <bits/stdc++.h>
#include <fstream>
using namespace std;
typedef struct Point{
    short col;
    short row;
    short val;
    Point *parent;
}Point;

class graph {
private:
    int col_size;
    int row_size;
    int nets;
    short nowcol;
    short nowrow;
    short point = 0;
    int capacity = 0;
    vector<vector<short>> Allpoint;
    vector<vector<short>> col_edge;
    vector<vector<short>> row_edge;
    vector<vector<Point>> array_2D;
    stack<Point> pointlist;

public:
    
    // graph(short col_size, short row_size, short cap);
    void routing(short col1, short row1, short col2, short row2);
    void relax(short col1,short row1,short col2,short row2);
    void readfile();
    void outputfile();
};
// graph::graph(short col_size, short row_size, short cap) : col_size(col_size), row_size(row_size), capacity(cap) {
    
//     Point init;
//     init.parent = NULL;
//     init.val = 0;
//     init.col = 0;
//     init.row = 0;

//     col_edge.resize(row_size, vector<short>(col_size-1, 1));
//     // col_edge.resize(100, vector<short>(100, 1));
//     row_edge.resize(row_size, vector<short>(col_size, 1));
//     array_2D.resize(row_size, vector<Point>(col_size , init));
//     capacity = cap;
//     cout<<"row_size = "<<row_size<<" col_size = "<<col_size<<endl;
//     cout<<"col_edge.size() = "<<col_edge.size()<<endl;
//     cout<<"col_edge[0].size() = " << col_edge[0].size()<<endl;
// }

void graph::relax(short col1,short row1,short col2,short row2){
    short w;
    
    // cout << "row1 = ("<< row1 <<") = col1 = ("<<col1<<")"<<endl;
    // cout << "row2 = ("<< row2 <<") = col2 = ("<<col2<<")"<<endl;
    // cout << "array_2D["<<row1<<"]["<<col1<<"].val = "<<array_2D[row1][col1].val <<endl;
    // cout << "array_2D["<<row1<<"]["<<col1<<"].val = "<<array_2D[row2][col2].val <<endl;
    if(col2-col1==1){
        // cout<<"right"<<endl;
        w = this->col_edge[row1][col1];
        // w = col_edge[1][0];
        
    }
    else if(row2-row1==1){
        // cout<<"down"<<endl;
        w = this->row_edge[row1][col1];  
    }
    else if(row2-row1==-1){
        // cout<<"up"<<endl;
        w = this->row_edge[row1-1][col1]; 
    }
    else{
        // cout<<"left"<<endl;
        w = this->col_edge[row1][col1-1]; 
    }
    if(this->array_2D[row2][col2].val>this->array_2D[row1][col1].val+w){
        this->array_2D[row2][col2].parent = &this->array_2D[row1][col1];
        this->array_2D[row2][col2].val = this->array_2D[row1][col1].val+w;
        // cout << "w = " << w <<endl;
        // cout << "                                       change   array_2D["<<row2<<"]["<<col2<<"].val = "<<this->array_2D[row2][col2].val <<endl;
    }
}
void graph::routing(short row1, short col1, short row2,short col2){
    bool swapflag = false;
    bool target_is_right_up = true;
    short col_dir[4] = {0,1,0,-1};
    short row_dir[4] = {-1,0,1,0};
    short minimun = SHRT_MAX;
    short min_row = 0;
    short min_col = 0;
    int cnt=0;
    // if(col1>col2){
    //     swap(col1,col2);
    //     swap(row1,row2);
    //     swapflag = true;
    // }
    // if(row2>row1){//目標在右下
    //     target_is_right_up = false;
    //     row_dir[0] = 1 ;
    //     cout<<"target is right down"<<endl;
    // }
    // else{
    //     cout<<"target is right up"<<endl;
    // }
    
    vector<Point*> q;
    vector<Point*> p;    
    Point *link_list;
    for(int i=0;i<row_size;i++){
        for(int j=0;j<col_size;j++){
            this->array_2D[i][j].val = i==row1&&j==col1?0:SHRT_MAX;
            this->array_2D[i][j].col = j;
            this->array_2D[i][j].row = i;
            this->array_2D[i][j].parent = NULL;
            q.push_back(&array_2D[i][j]);
        }
    }

    while(!q.empty()){
        // cout << endl;
        minimun = q[0]->val;
        // cout << "("<<q[0]->row<<","<<q[0]->col<<")";
        // cout << q[0]->val<<endl;
        for(int i=0;i<q.size()-1;i++){
            minimun = minimun<q[i+1]->val?minimun:q[i+1]->val;
            // cout << "("<<q[i+1]->row<<","<<q[i+1]->col<<")";
            // cout << q[i+1]->val<<endl;
        }
        cnt = 0;
        // cout << "minimun = " << minimun <<endl;
        for(int i=0;i<q.size();i++){

            if(minimun==q[i]->val&&cnt==0){
                minimun = q[i]->val;
                min_col = q[i]->col;
                min_row = q[i]->row;
                
                cnt=1;
            }
            else{
                p.push_back(q[i]);
            }
        }
        
        // cout << "min_row,min_col = (" << min_row << ","<<min_col<<")"<<endl;
        

        if(p.empty()){
            short bfr_col,bfr_row,now_col,now_row;
            link_list = &array_2D[row2][col2];
            // for(int i=0;i<array_2D.size();i++){
            //     for(int j=0;j<array_2D[0].size();j++){
            //         if(array_2D[i][j].parent==NULL){
            //             cout << "array_2D["<<i<<"]["<<j<<"].parent = "<<"NULL"<<endl;
            //         }
            //         else{
            //             cout<< "array_2D["<<i<<"]["<<j<<"].parent = "<< array_2D[i][j].parent<<endl;
            //         }
            //     }
            // }
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
                    col_edge[bfr_row][bfr_col] = col_edge[bfr_row][bfr_col]+1;//right
                    }
                    else if(now_row-bfr_row==1){
                        row_edge[bfr_row][bfr_col] = row_edge[bfr_row][bfr_col]+1;//down
                    }
                    else if(now_row-bfr_row==-1){
                        row_edge[bfr_row-1][bfr_col] = row_edge[bfr_row-1][bfr_col]+1;//up
                    }
                    else{
                        col_edge[bfr_row][bfr_col-1] = col_edge[bfr_row][bfr_col-1]+1;//left
                    }
                }
            }
            break;
        }
        
        for(int i=0;i<4;i++){       
            short new_col = min_col+col_dir[i];
            short new_row = min_row+row_dir[i];
            
            if(new_col<col_size&&new_row<row_size&&new_col>=0&&new_row>=0){
                relax(min_col,min_row,new_col,new_row);
            }
        }
        q = p;
        p.clear();
    }   
}

void graph::readfile(){
    ifstream fin("60x60.in",ios::in);
    
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
    Allpoint.resize(nets, vector<short>(4, 0));
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

    col_edge.resize(row_size, vector<short>(col_size-1, 1));
    // col_edge.resize(100, vector<short>(100, 1));
    row_edge.resize(row_size, vector<short>(col_size, 1));
    array_2D.resize(row_size, vector<Point>(col_size , init));

}

void graph::outputfile(){
    const char* file_path = "60x60.out";
    ofstream outputFile(file_path);
    
    vector<Point> P;
    
    short tmpcol,tmprow;
    for(int i=0;i<nets;i++){
        
        routing(Allpoint[i][0],Allpoint[i][1],Allpoint[i][2],Allpoint[i][3]);
        cout<<i<<endl;
        outputFile << i << " "<<pointlist.size()-1<<endl;
        while(!pointlist.empty()){
            P.push_back(pointlist.top());
            pointlist.pop();
        }
        for(int i=0;i<P.size()-1;i++){
            outputFile<< P[i].col  << " "<<P[i].row << " "<<P[i+1].col  << " "<<P[i+1].row<<endl;
        }
        P.clear();
    }
    outputFile.close();
}

int main() {
    graph PA2;
    PA2.readfile();
    PA2.outputfile();
    
    return 0;
}