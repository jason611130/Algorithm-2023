#include <bits/stdc++.h> 
using namespace std; 
  
// User defined class, Point 
class Point 
{ 
   int x; 
   int y; 
   char name;
public: 
   Point(int x, int y,char name) 
   { 
      this->x = x; 
      this->y = y; 
      this->name = name;
   } 
   int getX() const { return x; } 
   int getY() const { return y; } 
   char getname() const { return name; }
}; 
  
// To compare two points 
class myComparator 
{ 
public: 
    int operator() (const Point& p1, const Point& p2) 
    { 
        return p1.getX() > p2.getX(); 
    } 
}; 
  
// Driver code 
int main () 
{ 
    // Creates a Min heap of points (order by x coordinate) 
    priority_queue <Point, vector<Point>, myComparator > pq; 
  
    // Insert points into the min heap 
    pq.push(Point(5, 2 , 'T')); 
    pq.push(Point(2, 1,'U')); 
    pq.push(Point(1, 5,'G')); 
  
    // One by one extract items from min heap 
    while (pq.empty() == false) 
    { 
        Point p = pq.top(); 
        cout << "(" << p.getX() << ", " << p.getY() << ","<<p.getname()<< ")"; 
        cout << endl; 
        pq.pop(); 
    } 
  
    return 0; 
} 