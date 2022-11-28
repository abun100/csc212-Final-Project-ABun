#pragma once
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

struct Point
{
	int x, y;
};

class GrahamScan
{
public:

    //The reference point
    Point p0;

	//Finds the bottom most point of the given coordinates
	int findBottom(std::vector<Point> &poly);

    //Find the distance between two points
    int dist(Point p1, Point p2);

    //The comparison used within the qsort
    int compare(const void *vp1, const void *vp2);

    //Finds whether the following points is collinear, ccw or cw
    int direction(Point p1, Point p2, Point p3);

	//Prints the outer convex hull of given image
	std::stack<Point> convexHull(std::vector<Point>& points);

	//Reads from file and assigns each "Point" cordinates and pushes each "Point" into a vector
	void ReadFile(std::string file_name, std::vector<Point>& points, int numLines);
	
	friend class App;
};
