//Work in progress
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

//Creates a struct that holds each x and y coordinate, alongside the polygon number
struct Point{
    int x;
    int y;
    int p;
};

//Calculates the dot product between two points
float Dot(Point p, std::pair<int,int> d)
{
    return ((p.x * d.first) + (p.y * d.second));
}

//This will find the furthest point in a polygon given a direction
Point findFurthest1(std::vector<Point> &poly, std::pair<int,int> direction)
{
    Point far = poly[0];
    float mdis = Dot(poly[0], direction);
    float dis;
    for(int i = 0; i < poly.size(); i++){
        dis = Dot(poly[i], direction);
        if(dis > mdis){
            mdis = dis;
            far = poly[i];
        }
    }
    //std::cout << far.x << far.y << " d:" << direction.first << direction.second << std::endl;
    return far;
}

//Just a sample for inverting the direction for the second polygon. Can be cleaned up
Point findFurthest2(std::vector<Point> &poly, std::pair<int,int> direction)
{
    direction.first *= -1;
    direction.second *= -1;
    Point far = poly[0];
    float mdis = Dot(poly[0], direction);
    float dis;
    for(int i = 0; i < poly.size(); i++){
        dis = Dot(poly[i], direction);
        if(dis > mdis){
            mdis = dis;
            far = poly[i];
        }
    }
    //std::cout << far.x << far.y << " d:" << direction.first << direction.second << std::endl;
    return far;
}

//Calculates the Minkowski sum of the found furthest points and places them into a vector
void Minkowski(Point tmp1, Point tmp2, std::vector<Point> &mhull)
{
    Point tmp3;
    tmp3.x = tmp2.x - tmp1.x;
    tmp3.y = tmp2.y - tmp1.y;
    mhull.push_back(tmp3);
}

//Reads the inputted text file and stores all values into a polygon vector
void readFile(std::vector<Point> &poly, std::string fname)
{
    std::ifstream inFile(fname);
    int a, b, c;
    while(inFile >> a >> b >> c){
        Point p;
        p.x = a;
        p.y = b;
        p.p = c;
        poly.push_back(p);
    }
}

int main(int argc, char** argv)
{
    std::string fname = argv[1];
    std::vector<Point> poly;
    std::vector<Point> poly1;
    std::vector<Point> poly2;
    std::vector<std::pair<int,int>> direction = {{1,0},{-1,0},{0,1},{0,-1}}; // Creates a sample direction vector used for finding the furthest points along a direction
    std::vector<Point> mhull;
    Point tmp1, tmp2, tmp3;
    readFile(poly, fname);
    for(int i = 0; i < poly.size(); i++){
        if(poly[i].p == 1){
            poly1.push_back(poly[i]); //places correspoding polygon points into the corresponding polygon vector
        }
        else{
            poly2.push_back(poly[i]);
        }
    } 
    //This will be responsible for finding the points that comprise the Minkowksi outer hull
    for(int i = 0; i < direction.size(); i++){
        tmp1 = findFurthest1(poly1, direction[i]);
        tmp2 = findFurthest2(poly2, direction[i]);
        Minkowski(tmp1, tmp2, mhull);
    }
    //This is an output to check the contents of the minkowski hull
    for(int i = 0; i < mhull.size(); i++){
        std::cout << mhull[i].x << mhull[i].y << std::endl;
    }
}
