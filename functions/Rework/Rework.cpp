#include "grahamScan.h"

int main()
{
	
	std::vector<Point> points = { {0, 3}, {1, 1}, {4, 4},
					{0, 0}, {2, 2}, {1, 2}, {3, 1}, {3, 3} };
	

	grahamScan scan(points);
	scan.initial_setup(points);
	scan.find_convex_hull(points);

	return 0;
}