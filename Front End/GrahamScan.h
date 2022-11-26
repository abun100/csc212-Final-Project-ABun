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
	int x, y, color;
	Point();
	Point(int pos1, int pos2, int col);
};

class GrahamScan
{
public:
	//Returns the Number of Rows in the file
	int getNumOfLines(std::string file_name);

	//Prints the outer convex hull of given image
	std::stack<Point> convexHull(std::vector<Point>& points);

	//Reads from file and assigns each "Point" cordinates and pushes each "Point" into a vector
	void ReadFile(std::string file_name, std::vector<Point>& points, int numLines);
	
	friend class App;
};

