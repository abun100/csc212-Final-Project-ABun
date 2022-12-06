#include "GJK.h"

/*
	GJK class : test for collisions or intersections 
*/

//Given a vector, return the opposite direction 
//sets the x and y of the vector in the negative direction
Point GJK::negative_direction(Point& d)
{
	Point temp;
	temp.x = -(d.x); 
	temp.y = -(d.y);
	return temp;

}

//Given two vectors a and b
//subtrack their x and y values and
//return the new vector 
Point GJK::subtract(Point& a, Point& b)
{
	Point temp;
	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	return temp;
}

//Given two vectors, find the cross product
//Return a vector in the form of the cross product
Point GJK::cross(Point a, Point b) {
	Point temp;

	temp.x = a.x * b.y;
	temp.y = b.x * a.y;

	return temp;
}

//Given the center cordinates of the polygon from its position on the window
//set the each polygon's center
void GJK::find_centroid(float& width, float& height, float& width2, float& height2)
{
	this->center1.x = width; 
	this->center1.y = height;
	this->center2.x = width2;
	this->center2.y = height2;
}

//Given two vectors
//return the float value of the dot product 
float GJK::dot(Point& p, Point& d)
{
	return ((p.x * d.x) + (p.y * d.y));
}

//Finds the furthest points given a direction vector
//it takes in the polygon's verticies and the given search direction
//returns the furthest point found in the polygon
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

//In order to find a simplex point
//Search for the furthest point in a given direction for polygon 1
//Search for the furthest point in the opposite direction for polygon 2
//Return the point that belongs on the minkowski difference (ALSO our simplex point)
Point GJK::find_simplex_point(std::vector<Point>& poly1, std::vector<Point>& poly2, Point& direction) {
	Point pf1 = find_furthest_point(poly1, direction);

	Point opposite_direction = negative_direction(direction);

	Point pf2 = find_furthest_point(poly2, opposite_direction);

	Point temp;
	temp = subtract(pf1, pf2);
	return temp;
}


//Main Collision Dectection Algorithm
//Takes in the vectors of verticies from each polygon
//Returns true if the two polygons are intersecting 
//Returns false if not intersecting 
bool GJK::gjk(std::vector<Point>& poly1, std::vector<Point>& poly2)
{
	Point perpendicular_direction; //establish perpendicular direction and origin
	Point origin(0, 0);

	//Loop continues until a return statement is hit in this loop ONLY 
	while (true) {

		//If no points exist in our simplex, choose a direction,
		//and add Point A to our simplex
		if (simplex.size() == 0) {
			Point direction = subtract(center2, center1);
			Point A = find_simplex_point(poly1, poly2, direction);
			simplex.push_back(A);
		}

		//If a point is added to our simplex
		//Find the oppoiste direction of that point
		//Find the furthest point along that direction (Point B)
		//Add B to our simplex
		else if (simplex.size() == 1) {
			Point new_direction = subtract(origin, simplex[0]);
			Point B = find_simplex_point(poly1, poly2, new_direction);
			
			if ((dot(B, new_direction) < 0)) {
				return false;
			}

			simplex.push_back(B);
		}

		//If simplex contains two points, initiate the line case
		//Find the edge between A and B, then find the vector between Point B and the origin
		//Finds the perpendicular direction from edge AB and finds the furthest point in that direction (Point C)
		//Adds Point C to the simplex
		else if (simplex.size() == 2) {

			//Line case 
			Point A = simplex[0];
			Point B = simplex[1];

			Point BA = subtract(A, B);
			Point BO = subtract(origin, B);
			perpendicular_direction = cross(cross(BA, BO), BA);
			Point C = find_simplex_point(poly1, poly2, perpendicular_direction);
			simplex.push_back(C);
		}

		//When the simplex contains three points, it forms a triangle
		//If the triange does not contain the simplex, we iterate our loop
		//Returns true if and only if origin is inside the triange case
		else if (simplex.size() == 3) {
			if (!(triangle_case(simplex, perpendicular_direction))) { continue; }
			else { return true;  }
		}
	}
}

//Triangle case - Three points must exist in our simplex
//Checks for the regions perpendiuclar to edges CB and CA
//Returns true only when both if statements are false
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
		
		//return case where it tosses the simplex back to the line case to find the next point on the Minkowski by Removing point A
		return false;
	}
	else if (dot(CAperp, CO) > 0) {
		simplex.erase(simplex.begin() + 1); // Removes B from the simplex vector
	
		// return case where it tosses the simplex back to the line case to find the next point on the Minkowski by removing point B
		return false;
	}
	//If it fails the prior two edge cases, the origins lies within the polygon, therefore there is collision
	else {
		return true;
	}
}
