//This function was utilized for reading individual data points off a file as a simpler way to input data while testing functions
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

//Creates a struct that holds each x and y coordinate, alongside the polygon number
struct Point{
    int x;
    int y;
    int p;
};

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
    readFile(poly, fname);
    std::cout << "it works" << std::endl;
    for(int i = 0; i < poly.size(); i++){
        if(poly[i].p == 1){
            poly1.push_back(poly[i]); //places correspoding polygon points into the corresponding polygon vector
        }
        else{
            poly2.push_back(poly[i]);
        }
    }
    for(int i = 0; i < poly1.size(); i++){
        std::cout << poly1[i].x << poly1[i].y << poly1[i].p << std::endl;
    }
}
