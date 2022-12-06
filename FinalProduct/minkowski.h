#pragma once
#include "App.h"
class minkowski
{
private:
	//Vector representation for each polygon and shape
	std::vector<Point> poly1;
	std::vector<Point> poly2;
	std::vector<Point> minkowski_sum;
public:
	//Find the minkowski difference
	minkowski();
	void find_minkowski(std::vector<Point>& poly1, std::vector<Point>& poly2);
	std::vector<Point> get_minkowski_sum();
};

