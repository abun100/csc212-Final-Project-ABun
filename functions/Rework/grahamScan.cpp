#include "grahamScan.h"
/*

    This is the "Final", hopefully, iteration of the graham scan
        - it uses Eddy's convex hull finder, turn function, distance function, and find bottom function (with some tweaks throughout)
        - Bun implemented a quick sort function that sorts all points based on polar angles 
    
    Missing : just comments of what the graham scan does and what each part does

*/


//Contructor
grahamScan::grahamScan(std::vector<Point> &inserted_poly)
{
    anchor_point = inserted_poly[0];
}

//Util Functions for Graham Scan
int grahamScan::Turn(Point a, Point b, Point c) // Checks the turn that would be made from the current point to the next point
{
    float area = ((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x));
    if (area > 0) {
        return 1; // ccw 
    }
    else if (area < 0) {
        return -1; // cw
    }
    else {
        return 0; // collinear
    }
}

void grahamScan::swap(Point& a, Point& b)
{
    Point temp = a;
    a = b;
    b = temp;
}

double grahamScan::polar_angle(Point i)
{
    return atan((double)(i.y - anchor_point.y) / (double)(i.x - anchor_point.x));
}

int grahamScan::distance(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

//Implement of Quick Sort
int grahamScan::partition(std::vector<Point>& poly, int& begin, int& end)
{
    Point pivot = poly[end];
    int i = begin - 1;

    for (int j = begin; j <= end - 1; j++) {
        if (polar_angle(poly[j]) < polar_angle(pivot)) {
            i++;
            swap(poly[i], poly[j]);
        }
        else if (polar_angle(poly[j]) == polar_angle(pivot)) {
            if (distance(anchor_point, pivot) >= distance(anchor_point, poly[j])) {
                i++;
                swap(poly[j], poly[i]);
            }
        }
    }
    swap(poly[i + 1], poly[end]);
    return i + 1;
}

void grahamScan::quick_sort(std::vector<Point>& poly, int begin, int end)
{
    if (begin < end) {
        int pivot = partition(poly, begin, end);
        quick_sort(poly, begin, pivot - 1);
        quick_sort(poly, pivot + 1, end);
    }
}

//Graham Scan Functions 
void grahamScan::find_bottom_point(std::vector<Point>& poly)
{
    anchor_point = poly[0];
    int min_index = 0;

    for (int i = 1; i < poly.size(); i++) {
        if (poly[i].y < anchor_point.y) {
            anchor_point = poly[i];
            min_index = i;
        }
    }
    swap(poly[0], poly[min_index]);
}

void grahamScan::initial_setup(std::vector<Point>& poly)
{
    //finds the bottom most point in the polygon
    find_bottom_point(poly);
   
    //quick sort based on polar angle between anchor points and points in poly
    quick_sort(poly, 1, poly.size() - 1);
}

void grahamScan::find_convex_hull(std::vector<Point>& poly)
{
    //Eddy's Part of the convex hull finder
    convex.push(poly[0]);
    convex.push(poly[1]);

    for (int i = 2; i < poly.size(); i++) {
        Point next = poly[i];
        Point curr = convex.top();
        convex.pop();
        while (Turn(convex.top(), curr, next) <= 0) {
            curr = convex.top();
            convex.pop();
        }
        convex.push(curr);
        convex.push(poly[i]);
    }

   /* while (!convex.empty()) {
        std::cout << convex.top().x << convex.top().y << " ";
        convex.pop();
    }*/
}



