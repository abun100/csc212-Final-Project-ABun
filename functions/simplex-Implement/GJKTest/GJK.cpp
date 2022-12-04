#include "GJK.h"

Point GJK::negative_direction(Point& d)
{
	Point temp;
	temp.x = -(d.x);
	temp.y = -(d.y);
	return temp;

}

Point GJK::subtract(Point& a, Point& b)
{
	Point temp;
	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	return temp;
}

Point GJK::cross(Point a, Point b) {
	Point temp;

	temp.x = a.x * b.y;
	temp.y = b.x * a.y;

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

Point GJK::find_simplex_point(std::vector<Point>& poly1, std::vector<Point>& poly2,  Point& direction) {
	//finds the furthest point for polygon 1
	Point pf1 = find_furthest_point(poly1, direction);

	Point opposite_direction = negative_direction(direction);

	Point pf2 = find_furthest_point(poly2, opposite_direction);

	Point temp;
	temp = subtract(pf1, pf2);
	return temp;
}

bool GJK::gjk()
{
	//get the center of each polygon
	find_centroid();

	//finds the intital direction based on the centers of the polygons 
	Point direction = subtract(center2, center1);

	//finds first simplex point
	Point A = find_simplex_point(poly1, poly2, direction);
	simplex.push_back(A);

	//sets the direction towards the origin
	Point origin(0, 0);
	direction = subtract(origin, simplex[0]);

	while (true) {
		//Finds next simplex point
		Point next_point = find_simplex_point(poly1, poly2, direction);

		//if the next simplex points does not pass the orgin
		//then there is no collision
		if (dot(next_point, direction) <= 0) { 
			return false;
		}
		else { simplex.push_back(next_point); }

		if (check_simplex(simplex, direction)) {
			return true;
		}
	}
}

bool GJK::check_simplex(std::vector<Point>& simplex, Point& direction) {
	if (simplex.size() == 2) {
		return line_case(simplex, direction);
	}

	return triangle_case(simplex, direction);
}

//The purpose is to find the next direction for the third point in the simplex
bool GJK::line_case(std::vector<Point>& simplex, Point& direction) {
	Point A = simplex[0];
	Point B = simplex[1];
	Point origin(0, 0);

	Point BA = subtract(A, B);
	Point BO = subtract(origin, B);
	direction = cross(cross(BA,BO),BA);
	
	return false;
}

bool GJK::triangle_case(std::vector<Point>& simplex, Point& direction)
{
	Point A = simplex[0]; // Declaring all points for usage in the triangle case (for the sake of simplification)
	Point B = simplex[1];
	Point C = simplex[2];
	Point origin(0, 0);

	//Initializes each edge of the simplex triangle
	Point CB = subtract(B, C);
	Point CA = subtract(A, C);
	Point CO = subtract(origin, C);

	//Finds the CB and AB perpendiculars utilizing triple cross product
	Point CBperp = cross(cross(CA, CB), CB);
	Point CAperp = cross(cross(CB, CA), CA);

	//Each edge case that needs to be tested
	if (dot(CBperp, CO) > 0) {
		simplex.erase(simplex.begin()); // removes A from the simplex vector
		direction = CBperp;
		//some return case where it tosses the simplex back to the line case to find the next point on the Minkowski or
		return false;
	}
	else if (dot(CAperp, CO) > 0) {
		simplex.erase(simplex.begin() + 1); // Removes B from the simplex vector
		direction = CAperp;
		//some return case where it tosses the simplex back to the line case to find the next point on the Minkowski or
		return false;
	}
	//If it fails the prior two edge cases, the origins lies within the polygon, therefore there is collision
	else {
		//Some return case that defines the collision as true
		return true;
	}
}
