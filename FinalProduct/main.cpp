#include "ScanImage.h"
#include "App.h"


// Driver program to test above functions
int main(int argc, char* argv[])
{
	std::string file_name = argv[2];
	std::string file_name2 = argv[3];
	std::vector<Point> convex;
	std::vector<Point> black_pixels;
	std::vector<Point> poly1;
	std::vector<Point> poly2;

	//Graham Scan our images for file1 and file2
	GrahamScan scan1;
	int numLines = scan1.getNumOfLines(file_name);
	scan1.ReadFile(file_name, convex, numLines);
	scan1.initial_image_setup(convex, black_pixels);
	poly1 = scan1.find_convex_hull(black_pixels);

	//Clear convex points
	convex.clear();
	black_pixels.clear();
	
	GrahamScan scan2;
	numLines = scan2.getNumOfLines(file_name2);
	scan2.ReadFile(file_name2, convex, numLines);
	scan2.initial_image_setup(convex, black_pixels);
	poly2 = scan2.find_convex_hull(black_pixels);
	
	//Application 
	App app(poly1,poly2);

	//window loop
	while (app.isRunning()) {
		
		//update
		app.update();
		
		//render
		app.render();
	
	}

	return 0;
}
