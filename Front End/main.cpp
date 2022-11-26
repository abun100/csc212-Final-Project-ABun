#include "GrahamScan.h"
#include "App.h"


// Driver program to test above functions
int main(int argc, char* argv[])
{
	std::string file_name = argv[2];

	//Application 
	App app;

	//Set the file_name and initiate graham scan
	app.setFileName(file_name);
	app.initGrahamScan();

	//window loop
	while (app.isRunning()) {
		
		//update
		app.update();
		
		//render
		app.render();
	
	}

	return 0;
}
