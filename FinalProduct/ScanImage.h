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
	float x, y, color;
	Point() {}
	Point(float pos1, float pos2) :
		x(pos1), y(pos2) {}
	Point(int pos1, int pos2, int col)
		: y(pos1) , x(pos2), color(col) {}
};

class GrahamScan
{
private:
	Point anchor_point;
	std::vector<Point> poly;
	std::vector<Point> convex;
	void quick_sort(std::vector<Point>& poly, int begin, int end);

public:
	GrahamScan();
	int Turn(Point a, Point b, Point c);
	void swap(Point& a, Point& b);
	double polar_angle(Point i);
	int distance(Point p1, Point p2);
	int partition(std::vector<Point>& poly, int& begin, int& end);
	void find_bottom_point(std::vector<Point>& poly);
	void minkowski_bottom_point(std::vector<Point>& poly);
	void initial_image_setup(std::vector<Point>& poly, std::vector<Point>& black_pixels);
	void minkowski_setup(std::vector<Point>& poly);
	std::vector<Point> find_convex_hull(std::vector<Point>& poly);

	//Returns the Number of Rows in the file
	int getNumOfLines(std::string file_name);

	//Reads from file and assigns each "Point" cordinates and pushes each "Point" into a vector
	void ReadFile(std::string file_name, std::vector<Point>& points, int numLines);
	
	friend class App;
};

