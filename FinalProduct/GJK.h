#pragma once
#include "ScanImage.h"

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

	//Simplex Valid 
	bool check = true;

public:

	//Contructor
	GJK() {}
	
	//Util functions to help find simplex points on minkowski sum
	void find_centroid(float& height, float& width, float& height2, float& width2);
	Point find_furthest_point(std::vector<Point>& outer_hull, Point& direction);
	Point find_simplex_point(std::vector<Point>& outer_hull, std::vector<Point>& poly2, Point& direction);
	float dot(Point& p, Point& d);
	Point cross(Point a, Point b);
	Point negative_direction(Point& d);
	Point subtract(Point& a, Point& b);

	//Main Function of GJK
	bool gjk(std::vector<Point>& poly1, std::vector<Point>& poly2);
	bool check_simplex(std::vector<Point>& simplex, Point& direction);
	bool line_case(std::vector<Point>& simplex, Point& direction);
	bool triangle_case(std::vector<Point>& simplex, Point& direction);

};

