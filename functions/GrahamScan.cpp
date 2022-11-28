#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "GrahamScan.h"

struct Point{
    int x;
    int y;
};

Point p0;

void readFile(std::vector<Point> &poly, std::string fname)
{
    std::ifstream inFile(fname);
    int a, b;
    while(inFile >> a >> b){
        Point p;
        p.x = a;
        p.y = b;
        poly.push_back(p);
    }
}

int dist(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}

int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
  
   int o = direction(p0, *p1, *p2);
   if (o == 0)
     return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1;
  
   return (o == 2)? -1: 1;
}

int direction(Point p1, Point p2, Point p3)
{
    int val = (p2.y - p1.y) * (p3.x - p2.x) -
              (p2.x - p1.x) * (p3.y - p2.y);
  
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

Point findBottom(std::vector<Point> &poly)
{
    Point p0 = poly[0];
    for(int i = 0; i < poly.size(); i++){
        if(poly[i].y < p0.y){
            p0 = poly[i];
        }
        else if(poly[i].y == p0.y){
            if(poly[i].x < p0.x){
                p0 = poly[i];
            }
        }
    }
    return p0;
}
