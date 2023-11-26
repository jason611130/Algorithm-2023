#include<iostream>
using namespace std;
class DisjSet{
    private:
        int *parent,n,*rank;
    public:
        DisjSet(int n){
            rank = new int[n];
            parent = new int[n];
            this->n = n;
            makeSet();
        }
        void makeSet(){
            for(int i=0;i<n;i++){
                parent[i]=i;
                rank[i]=0;
            }
        }
        int find(int a){
            if(parent[a]!=a){
                parent[a] = find(parent[a]);
            }
            return parent[a];
        }
        void Union(int a,int b){
            int xset = find(a);
            int yset = find(b);
            
            if(xset==yset){
                return;
            }
            if(rank[xset]<rank[yset]){
                parent[xset] = parent[yset];
            }
            else if(rank[xset]>rank[yset]){
                parent[yset] = parent[xset];
            }
            else{
                parent[yset] = xset;
                rank[xset] = rank[xset] + 1;
            }
        }
};

int main(){
    DisjSet obj(10);
    obj.Union(0,1);
    obj.Union(2,3);
    obj.Union(4,5);
    obj.Union(6,7);
    obj.Union(8,9);
    obj.Union(9,6);
    obj.Union(7,5);
    obj.Union(0,2);
    obj.Union(3,4);
    obj.Union(6,2);
    // obj.Union(8,9);
    for(int i=0;i<10;i++){
        cout<<obj.find(i)<<endl;
    }
    if (obj.find(4) == obj.find(0))
        cout << "Yes\n";
    else
        cout << "No\n";
    if (obj.find(1) == obj.find(0))
        cout << "Yes\n";
    else
        cout << "No\n";
}