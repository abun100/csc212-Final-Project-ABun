#pragma once
#include <iostream>
#include <stack>
#include <vector>

struct Point {
	int x, y;
};

class grahamScan
{
private:
	Point anchor_point;
	std::vector<Point> poly;
	std::stack<Point> convex;
	void quick_sort(std::vector<Point>& poly,int begin, int end);

public:
	grahamScan(std::vector<Point>& poly);
	int Turn(Point a, Point b, Point c);
	void swap(Point& a, Point& b);
	double polar_angle(Point i);
	int distance(Point p1, Point p2);
	int partition(std::vector<Point>& poly, int& begin, int& end);
	void find_bottom_point(std::vector<Point>& poly);
	void initial_setup(std::vector<Point>& poly);
	void find_convex_hull(std::vector<Point>& poly);




};

