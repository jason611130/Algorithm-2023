#include<iostream>
#include <bits/stdc++.h>
using namespace std;
struct Node;

struct Item
{
  Node *hd,*tl;
};

struct Node{
  int val;
  Node *next;
  Item *itemPtr;
};


class ListSet{
  public:
    void makeset(int a);
    Item* find(int key);
    void Union(Item *i1,Item *i2); 
  private:
    unordered_map<int,Node*> nodeAddress;
};

void ListSet::makeset(int a){
  //create new set;
  Item *newSet =new Item;
  //create a new linked list node
  newSet->hd = new Node;
  //Initialize head and tail
  newSet->tl = newSet->hd;
  nodeAddress[a] = newSet -> hd;
  //create a new set 
  newSet->hd->val = a;
  newSet->hd->itemPtr = newSet;
  newSet->hd->next = NULL;
}

Item *ListSet::find(int key){
  Node *ptr = nodeAddress[key];
  return (ptr->itemPtr);
}

void ListSet::Union(Item *set1,Item *set2){
  Node *cur = set2->hd;
  while(cur != 0){
    cur->itemPtr =set1;
    cur = cur->next;
  }
  (set1->tl)->next = set2->hd;
  set1->tl = set2->tl;
  delete set2;
}

int main()
{
    ListSet a;
    a.makeset(13); //a new set is made with one object only
    a.makeset(25);
    a.makeset(45);
    a.makeset(65);
 
    cout << "find(13): " << a.find(13) << endl;
    cout << "find(25): "
        << a.find(25) << endl;
    cout << "find(65): "
        << a.find(65) << endl;
    cout << "find(45): "
        << a.find(45) << endl << endl;
    cout << "Union(find(65), find(45)) \n";
 
    a.Union(a.find(65), a.find(45));
 
    cout << "find(65]): "
        << a.find(65) << endl;
    cout << "find(45]): "
        << a.find(45) << endl;
    return 0;
}