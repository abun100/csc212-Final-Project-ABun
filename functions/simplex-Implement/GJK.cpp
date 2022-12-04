#include "GJK.h"

Point GJK::negative_direction(Point d)
{
	Point temp;
	temp.x = -d.x;
	temp.y = -d.y;
	return temp;

}

Point GJK::subtract(Point a, Point b)
{
	Point temp;
	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	return temp;
}

void GJK::find_centroid()
{
	this->center1.x = 0;
	this->center1.y = 0;
	this->center2.x = 4;
	this->center2.y = 4;
}


float GJK::dot(Point& p, Point& d)
{
	return ((p.x * d.x) + (p.y * d.y));
}


Point GJK::find_furthest_point(std::vector<Point>& outer_hull, Point& direction)
{
	//Sets the furthest point as the first point in the polygon
	Point furthest_point = outer_hull[0];
	float maxDistance = dot(outer_hull[0], direction);
	float distance;

	//Loops through all the vertices in polygon and finds the furthest point
	for (auto& curr_vertex : outer_hull) {
		distance = dot(curr_vertex, direction);
		if (distance > maxDistance) {
			maxDistance = distance;
			furthest_point = curr_vertex;
		}
	}

	return furthest_point;
}


bool GJK::gjk()
{
	//finds the intital direction based on the centers of the polygons 
	this->direction = subtract(center2, center1);

	//initial finding furthest point of the first polygon
	Point pf1 = find_furthest_point(this->poly1, direction);

	//sets the direction in the opposite direction

	direction = negative_direction(this->direction);

	//initial finding furthest point of the second polygon 
	Point pf2 = find_furthest_point(this->poly2, direction);

	Point A(pf2.x - pf1.x, pf2.y - pf1.y);

	simplex.push_back(A);

	//sets the direction towards the origin
	Point origin(0, 0);

	this->direction = subtract(origin, simplex[0]);

	//finds second simplex
	pf1 = find_furthest_point(this->poly1, direction);

	direction = negative_direction(this->direction);

	pf2 = find_furthest_point(this->poly2, direction);

	Point B(pf2.x - pf1.x, pf2.y - pf2.y);

	//seting the direction from the perpective of A to the origin 
	direction = subtract(origin, A);

	if (dot(B, direction) <= 0) {
		return false;
	}
	else {
		simplex.push_back(B);
	}
}
