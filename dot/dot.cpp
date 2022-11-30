//I built this using the Graham Scan algorithm I worked on earlier (it's incomplete but I used it as a base)
//I wasn't sure how to approach a dot viz using Graphviz for a Convex Hull so I just had it output a connected graph of the points on the hull itself and print
//points that are inside of the hull off to the side, with no connections
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

void ConvexHull(std::vector<Point> &poly, std::stack<Point> &convex, std::stack<Point> &skip) //Checks all possible points for the convex hull
{
    for(int i = 2; i < poly.size(); i++){
        Point next = poly[i];
        Point curr = convex.top();
        convex.pop();
        while(Turn(convex.top(), curr, next) <= 0){
            skip.push(curr); // points that are dropped off the hull are placed into here to be printed later
            curr = convex.top();
            convex.pop();
        }
        convex.push(curr);
        convex.push(poly[i]);
    }
}

void PrintHull(std::stack<Point> &convex, std::stack<Point> skip, std::string ofname)
{
    Point temp = convex.top();
    std::ofstream output(ofname);
    output << "graph g{" << std::endl;
    while(!convex.empty()){ // this prints all the outer points of the convex hull that lie on the hull itself. all connected
        output << "\t" << '"' << convex.top().x << ',' << convex.top().y << '"' << " -- ";
        convex.pop();
    }
    output << '"' << temp.x << ',' << temp.y << '"' << ';' << std::endl;
    while(!skip.empty()){ // this just prints the remaining points onto the visualization just to show the points that aren't connected to the hull
        output << "\t" << '"' << skip.top().x << ',' << skip.top().y << '"';
        skip.pop();
    }
    output << ';' << std::endl << "}";
}

int main(int argc, char** argv)
{
    std::vector<Point> input;
    std::stack<Point> skip;
    std::string fname = argv[1];
    std::string ofname = argv[2];
    readFile(input, fname);
    //for(int i = 0; i < input.size(); i++){
    //    std::cout << input[i].x << input[i].y << " ";
    //}
    //std::cout << std::endl;
    std::stack<Point> convex;
    convex.push(input[0]);
    convex.push(input[1]);
    ConvexHull(input, convex, skip);
    //while(!convex.empty()){
    //   std::cout << convex.top().x << convex.top().y << " ";
    //    convex.pop();
    //}
    //std::cout << std::endl;
    PrintHull(convex, skip, ofname);
}
