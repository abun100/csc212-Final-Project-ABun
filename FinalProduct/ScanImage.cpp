#include "ScanImage.h"

/*
     Gram Scan: takes in image values or cordinate values to find the convex hull
*/


//Contructor
GrahamScan::GrahamScan()
{
    
}

//UTIL FUNCTIONS for Graham Scan

// Checks the turn that would be made from the current point to the next point
// Takes the x and y positions from point a,b, and c to find the area's value
int GrahamScan::Turn(Point a, Point b, Point c) 
{
    float area = ((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x));
    if (area > 0) {
        return 1; // counter clockwise
    }
    else if (area < 0) {
        return -1; // clock wise
    }
    else {
        return 0; // collinear
    }
}

//simply swaps Points values within the vector
void GrahamScan::swap(Point& a, Point& b)
{
    Point temp = a;
    a = b;
    b = temp;
}

//Returns the polar anlge with respects to the bottom most y point (anchor point)
double GrahamScan::polar_angle(Point i)
{
    return atan((double)(anchor_point.y - i.y) / (double)(anchor_point.x - i.x));
}

int GrahamScan::distance(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

//Implement of Quick Sort
//Uses polar angle to determine sorting
int GrahamScan::partition(std::vector<Point>& poly, int& begin, int& end)
{
    Point pivot = poly[end];
    int i = begin - 1;

    for (int j = begin; j <= end - 1; j++) {
        if (polar_angle(poly[j]) < polar_angle(pivot)) {
            i++;
            swap(poly[i], poly[j]);
        }

    }
    swap(poly[i + 1], poly[end]);
    return i + 1;
}

//Implement of Quick Sort
void GrahamScan::quick_sort(std::vector<Point>& poly, int begin, int end)
{
    if (begin < end) {
        int pivot = partition(poly, begin, end);
        quick_sort(poly, begin, pivot - 1);
        quick_sort(poly, pivot + 1, end);
    }
}

//Finds the bottom most point in an ***IMAGE***
//The extra condition in the if statement checks to see if the pixel is black
//We also check to see if y positions are the same, choose the left most pixel
void GrahamScan::find_bottom_point(std::vector<Point>& poly)
{
    anchor_point = poly[0];
    int max_index = 0;

    for (int i = 1; i < poly.size(); i++) {
        if (poly[i].x > anchor_point.x && (poly[i].color == 0)) {
            anchor_point = poly[i];
            max_index = i;
        }
        else if (poly[i].x == anchor_point.x && poly[i].color == 0) {
            if (poly[i].y < anchor_point.y) {
                anchor_point = poly[i];
                max_index = i;
            }
        }

    }
    //set the anchor points as the first position in the vector
    swap(poly[0], poly[max_index]);
}

//finds the bottom most point in the ***minkowski difference***
//Used to find the outer hull of minkowski differecne given the vector of vectors from each polygon
void GrahamScan::minkowski_bottom_point(std::vector<Point>& poly)
{
    anchor_point = poly[0];
    int max_index = 0;

    for (int i = 1; i < poly.size(); i++) {
        if (poly[i].x > anchor_point.x) {
            anchor_point = poly[i];
            max_index = i;
        }
        else if (poly[i].x == anchor_point.x) {
            if (poly[i].y < anchor_point.y) {
                anchor_point = poly[i];
                max_index = i;
            }
        }

    }
    swap(poly[0], poly[max_index]);
}

//In order to find the convex hull of the IMAGE we need to find the bottom most point
//use quick sort to sort by polar angle
//We only care about black pixels in an image
void GrahamScan::initial_image_setup(std::vector<Point>& poly, std::vector<Point>& black_pixels)
{
    //finds the bottom most point in the polygon
    find_bottom_point(poly);

    //quick sort based on polar angle between anchor points and points in poly
    quick_sort(poly, 1, poly.size() - 1);
    
    //Loops through entire image and pushes the black pixels into a vector
    for (auto& pixel_color : poly) {
        if (pixel_color.color == 1) {
            continue;
        }
        black_pixels.push_back(pixel_color);
    }
}
//Find the convex hull of the colliding shapes
//Only uses quick sort by angle and finding the bottom point 
//given a set of points
void GrahamScan::minkowski_setup(std::vector<Point>& poly)
{
    //finds the bottom most point in the polygon
    minkowski_bottom_point(poly);

    //quick sort based on polar angle between anchor points and points in poly
    quick_sort(poly, 1, poly.size() - 1);
}

//Finds the convex hull
std::vector<Point> GrahamScan::find_convex_hull(std::vector<Point>& black_pixels)
{
    //The first three points always belong on the convex hull
    convex.push_back(black_pixels[0]);
    convex.push_back(black_pixels[1]);
    convex.push_back(black_pixels[2]);

    //Loop through each black pixel, determine if the position of the pixel
    //relative to the anchor point is counter clockwise, clockwise, or colinear
    for (int i = 3; i < black_pixels.size(); i++) {
        Point next = black_pixels[i];
        Point curr = convex.back();
        convex.pop_back();
        while (convex.size() > 1 && (Turn(convex.back(), curr, next) <= 0)) {
            curr = convex.back();
            convex.pop_back();
        }
        convex.push_back(curr);
        convex.push_back(black_pixels[i]);
    }

    return convex;

}

//Gets the total number of lines from the txt file
int GrahamScan::getNumOfLines(std::string file_name) {
	std::ifstream file(file_name);
	std::string str;
	int number_of_lines = 0;

	while (std::getline(file, str)) {
		number_of_lines++;
	}
	file.close();

	return number_of_lines;
}

//Reads the file and assigns cordinate values to each pixel
void GrahamScan::ReadFile(std::string file_name, std::vector<Point>& points, int numLines) {
	int x = 0;

	// Opens the file for reading
	std::ifstream file(file_name);

	// Creates a string to hold each line in temporarily
	std::string str;

	// Iterates over the file, storing one line at a time into `str`
	while (std::getline(file, str)) {
		//start is the top left most value (0,0)
		//end is the last value in bottom right
		
        for (int y = 0; y < str.length(); y++) {
			Point temp(x, y, (str[y] - '0'));
			points.push_back(temp);
		}

		x++;
	}
}