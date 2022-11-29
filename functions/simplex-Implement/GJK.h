#pragma once
#include <pair>
struct Simplex {
private :
	std::vector<Points> simplex;

class GJK
{
private:
	std::pair<int, int> origin;

public:
	bool gjk(Point poly1, Point poly2);
	Point support(std::vector<std::pair<int, int>> direction);
	Point handleSimplex(Simplex simeplex, std::vector<std::pair<int, int>> direction);
	Point lineCase(Simplex simeplex, std::vector<std::pair<int, int>> direction);
	Point triangleCase(Simplex simeplex, std::vector<std::pair<int, int>> direction);
};

