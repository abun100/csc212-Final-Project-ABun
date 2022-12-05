#include "minkowski.h"

minkowski::minkowski()
{

}

void minkowski::find_minkowski(std::vector<Point>& poly1, std::vector<Point>& poly2)
{
	Point temp;
	for (auto& vertex_A : poly1) {
		for (auto& vertex_B : poly2) {
			temp.x = vertex_A.x - vertex_B.x;
			temp.y = vertex_A.y - vertex_B.y;
			minkowski_sum.push_back(temp);
		}
	}

	GrahamScan find_minkowski;

	find_minkowski.minkowski_setup(minkowski_sum);
	minkowski_sum = find_minkowski.find_convex_hull(minkowski_sum);
}

std::vector<Point> minkowski::get_minkowski_sum()
{
	return this->minkowski_sum;
}

