//This code works off an inputted data set that is already sorted by angle
//Note: Properly does the graham scan on the sorted vector of elements
//Parts that are missing: 1. Method to sort initial inputted elements -- 2. How to handle cases of collinearity 
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>

struct Point{
    int x, y;
};

void readFile(std::vector<Point> &poly, std::string fname) // Just to input for the sake of testing/debugging
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

int dist(Point p1, Point p2) // This will be used to find the furthest point away if two points make the same angle to the base point
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}

Point findBottom(std::vector<Point> &poly) // Finds the lowest point along the y-axis (checks lowest x if two y values are the same)
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

int Turn(Point a, Point b, Point c) // Checks the turn that would be made from the current point to the next point
{
    float area = ((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x));
    if(area > 0){
       return 1; // ccw 
    }
    else if(area < 0){
        return -1; // cw
    }
    else{
        return 0; // collinear
    }
}

void ConvexHull(std::vector<Point> &poly, std::stack<Point> &convex) //Checks all possible points for the convex hull
{
    for(int i = 2; i < poly.size(); i++){
        Point next = poly[i];
        Point curr = convex.top();
        convex.pop();
        while(Turn(convex.top(), curr, next) <= 0){
            curr = convex.top();
            convex.pop();
        }
        convex.push(curr);
        convex.push(poly[i]);
    }
}

int main(int argc, char** argv)
{
    std::vector<Point> input;
    std::string fname = argv[1];
    readFile(input, fname);
    //for(int i = 0; i < input.size(); i++){
    //    std::cout << input[i].x << input[i].y << " ";
    //}
    std::cout << std::endl;
    std::stack<Point> convex;
    convex.push(input[0]);
    convex.push(input[1]);
    ConvexHull(input, convex);
    while(!convex.empty()){
        std::cout << convex.top().x << convex.top().y << " ";
        convex.pop();
    }
    std::cout << std::endl;
}
