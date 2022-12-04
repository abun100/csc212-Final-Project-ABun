#pragma once
#include "grahamScan.h"


class GJK
{
private:
	//set of polygon points 
	std::vector<Point> poly1;
	std::vector<Point> poly2;
	std::vector<Point> simplex;

	//The clotest center to our convex shapes
	Point center1;
	Point center2;

	//Direction vector
	Point direction;

	

public:

	//Util functions to help find simplex points on minkowski sum
	void find_centroid();
	Point find_furthest_point(std::vector<Point>& outer_hull, Point& direction);
	float dot(Point& p, Point& d);
	float cross();
	Point negative_direction(Point d);
	Point subtract(Point a, Point b);


	//Main Function of GJK
	void gjk();
	void check_simplex();
	void line_case();
	void triangel_case();

};
