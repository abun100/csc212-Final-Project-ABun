#pragma once
#include "App.h"
class minkowski
{
private:
	std::vector<Point> poly1;
	std::vector<Point> poly2;
	std::vector<Point> minkowski_sum;
public:
	minkowski();
	void find_minkowski(std::vector<Point>& poly1, std::vector<Point>& poly2);
	std::vector<Point> get_minkowski_sum();
};

