#include "grahamScan.h"

int main()
{
	//Using rectangles beacuase it is easy to test and find centers
	std::vector<Point> points = { {-3,-3}, {3,3}, {-3,3}, {3,-3} };
	std::vector<Point> points2 = { {2,2}, {2,6}, {6,2}, {6,6} };

	/*grahamScan scan;
	scan.initial_setup(points);
	scan.find_convex_hull(points);*/

	return 0;
}
