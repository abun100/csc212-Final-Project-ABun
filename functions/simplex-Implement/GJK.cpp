#include "GJK.h"

//Finds the extreme points for both polygons 
Point support(direction) {

	//find the furthest point for each polygon
	Point max1 = findFurthest1();
	Point max2 = findFurthest2();

	//return the vertex on minkoswki difference 
	return max1 - max2;
}

//Chooses the next direction for the last point
//Can choose line case
//Can choose triangle case
void handleSimplex(Simplex simplex, std::pair<int, int> direction) {
	if (simplex.size() == 2) {
		return lineCase(simplex, direction);
	}
	return triangleCase(simplex, direction);
}


//Line case, chooses directions based on orgin
void lineCase(Simplex simplex, std::pair<int, int> direction) {
	Point A = simplex[0];
	Point B = simplex[1];

	Point AB = B - A;
	Point A0 = -A;

	//AB and A0 is in the same direction 
	if () {
		//take the cross product of the two points and change the direction value 
	}

	else {
		simplex.clear();
		simplex.push_back(A);
		direction = A0;
	}

	return false; 
}

void triangleCase(Simplex simplex, std::pair<int, int> direction) {
	//Idk how this one works tbh
}

bool gjk(poly1, poly2) {
	bool pass;
	//Picks our first simplex point
	//We will call this A
	simplex.push_back(support(direction));

	//Pick the direction towards the origin by subtracting the orgin - first point
	direction.first = origin.first - simplex[0].first;
	direction.second = origin.second - simplex[0].second;

	//This while loop will help us choose the following supporting points in the simplex
	while (pass) {
		nextSimplexPoint = support(direction);
		
		//if the dot prodcut between first point and second point  is < 0, this point will not be choosen
		if (Dot(nextSimplexPoint, direction) < 0) {
			pass = false;
		}
		//If > 0, then use it as the next point
		else {
			simplex.push_back(nextSimplexPoint);
		}
		//Inorder to handle the last simplex point in our triangle call this function
		if (handleSimplex(simplex, direction)) {
			true; pass = true;
		}
		return pass;
	}
	return pass;
}