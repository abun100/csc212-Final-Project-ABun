#include <iostream>
#include <stack>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Point
{
	int x, y, color;
	Point();
	Point(int pos1, int pos2, int col);
};

Point::Point() {
	x = 0;
	y = 0;
	color = 0;
}
Point::Point(int pos1, int pos2, int col) {
	this->x = pos1;
	this->y = pos2;
	this->color = col;
}

// A global point needed for sorting points with reference
// to the first point Used in compare function of qsort()
Point p0;

// A utility function to find next to top in a stack
Point nextToTop(stack<Point>& S)
{
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

// A utility function to swap two points
void swap(Point& p1, Point& p2)
{
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) +
		(p1.y - p2.y) * (p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
	int val = (q.x - p.x) * (r.y - q.y) -
		(q.y - p.y) * (r.x - q.x);

	if (val == 0) return 0; // collinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void* vp1, const void* vp2)
{
	Point* p1 = (Point*)vp1;
	Point* p2 = (Point*)vp2;

	// Find orientation
	int o = orientation(p0, *p1, *p2);
	if (o == 0)
		return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

	return (o == 2) ? -1 : 1;
}

// Prints convex hull of a set of n points.
void convexHull(std::vector<Point> &points)
{
	std::vector<Point> temp;
	// Find the bottommost point
	int xmax = points[0].x, min = 0;
	for (int i = 1; i < points.size(); i++)
	{
		int x = points[i].x;

		// Pick the bottom-most or choose the left
		// most point in case of tie
		if (((x > xmax) || (xmax == x &&
			points[i].y < points[min].y)) &&
			points[i].color == 0)
			xmax = points[i].x, min = i;
	}

	// Place the bottom-most point at first position
	swap(points[0], points[min]);

	// Sort n-1 points with respect to the first point.
	// A point p1 comes before p2 in sorted output if p2
	// has larger polar angle (in counterclockwise
	// direction) than p1
	p0 = points[0];
	temp.push_back(points[0]);
	qsort(&points[1], points.size() - 1, sizeof(Point), compare);

	// If two or more points make same angle with p0,
	// Remove all but the one that is farthest from p0
	// Remember that, in above sorting, our criteria was
	// to keep the farthest point at the end when more than
	// one points have same angle.
	
	for (int i = 1; i < points.size(); i++)
	{
		// Keep removing i while angle of i and i+1 is same
		// with respect to p0
		while ((i < points.size() - 1 && orientation(p0, points[i],
			points[i + 1]) == 0))
			i++;

		if (points[0].color == 1) {
			continue;
		}

		temp.push_back(points[i]);
		
	}

	for (auto& elem : temp) {
		std::cout << elem.x << ":" << elem.y << ":" << elem.color << std::endl;
	}

	// If modified array of points has less than 3 points,
	// convex hull is not possible
	if (temp.size() < 3) return;

	// Create an empty stack and push first three points
	// to it.
	stack<Point> S;
	S.push(points[0]);
	S.push(points[1]);
	S.push(points[2]);

	// Process remaining n-3 points
	for (int i = 3; i < temp.size(); i++)
	{
		// Keep removing top while the angle formed by
		// points next-to-top, top, and points[i] makes
		// a non-left turn
		while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
			S.pop();
		S.push(points[i]);
	}

	// Now stack has the output points, print contents of stack
	while (!S.empty())
	{
		Point p = S.top();
		cout << p.x << ";" << p.y << endl;
		S.pop();
	}
}

void ReadFile(std::string file_name, std::vector<Point> &points) {
	int row = 0;

	// Opens the file for reading
	std::ifstream file(file_name);

	// Creates a string to hold each line in temporarily
	std::string str;

	// Iterates over the file, storing one line at a time into `str`
	while (std::getline(file, str)) {
		
		//pushes each binary value into points
		for (int i = 0; i < str.length(); i++) {
			
			Point temp(row, i, (str[i] - '0'));
			points.push_back(temp);
		}

		row++;
	}
}



// Driver program to test above functions
int main(int argc, char* argv[])
{
	std::vector<Point> p;
	std::string file_name = argv[2];

	ReadFile(file_name, p);
	
	convexHull(p);

	return 0;
}
