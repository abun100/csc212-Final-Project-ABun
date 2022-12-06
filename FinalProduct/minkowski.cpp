#include "minkowski.h"

//Constructor
minkowski::minkowski()
{

}

//Find the minkowski difference given two polygons or convex shapes
void minkowski::find_minkowski(std::vector<Point>& poly1, std::vector<Point>& poly2)
{
	Point temp;
	for (auto& vertex_A : poly1) {		//Loops through the vertexes in each polygon and finds there vectors
		for (auto& vertex_B : poly2) {
			temp.x = vertex_A.x - vertex_B.x;
			temp.y = vertex_A.y - vertex_B.y;
			minkowski_sum.push_back(temp);
		}
	}

	GrahamScan find_minkowski;			//uses a graham scan to find the outer hull of those vectors 
	find_minkowski.minkowski_setup(minkowski_sum);
	minkowski_sum = find_minkowski.find_convex_hull(minkowski_sum);
}

//returns the minkowski difference back to the application class 
std::vector<Point> minkowski::get_minkowski_sum()
{
	return this->minkowski_sum;
}

