#include "App.h"

/*
	Class to launch and render the application
*/

//Updates the window
void App::update()
{
	this->pollEvents();

}

//Renders the convex shapes the front end app
void App::render()
{
	//Reders the Applications 
	this->window->clear();

	//Draw Shapes
	this->window->draw(this->convex1);

	this->window->display();
}

//Accessors : Returns true if the window is currently open
const bool App::isRunning()
{
	return this->window->isOpen();
}

//Keeps the window open
void App::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

//Defualt Constructor : Initiates front end app
App::App()
{
	this->initiateVariables();
	this->initiateWindow();
}

//Destructor : delets the window from memory 
App::~App()
{
	delete this->window;
}

//Initiates Windows as nullptr
void App::initiateVariables()
{
	this->window = nullptr;
}

//Initiates the size of the window and renders the window
void App::initiateWindow()
{
	//size of the window application
	this->videomode.height = 800;
	this->videomode.width = 1000;
	this->window = new sf::RenderWindow (this->videomode, "Collision Detection", sf::Style::Titlebar | sf::Style::Close); //initialize window
	

	this->window->setFramerateLimit(165);

}

//Initiates Convex Shapes 
void App::initShapes()
{
	
	float height = videomode.height;
	float width = videomode.width;

	this->convex1.setPosition(height / 2, width / 2);
	this->convex1.setFillColor(sf::Color::Black);
	this->convex1.setOutlineColor(sf::Color::Cyan);
	this->convex1.setOutlineThickness(1.f);
	
	//set the amount of points in respects to the convex hull
	this->convex1.setPointCount(this->convex_hull.size());

	int num_points = 0;
	
	//Adds the cordinates to our convex shape
	while (!convex_hull.empty()) 
	{
		this->convex1.setPoint(num_points, sf::Vector2f(convex_hull.top().y, convex_hull.top().x));
		convex_hull.pop();
		num_points++;
	}

}

void App::initGrahamScan()
{
	//Reads from file and initiates the graham scan to find convex hull
	GrahamScan scan;
	int numberOfLines = scan.getNumOfLines(this->file_name);
	scan.ReadFile(this->file_name, this->p, numberOfLines);
	this->convex_hull = scan.convexHull(this->p);

	//Creates the convex hull shape
	this->initShapes();
}

void App::setFileName(std::string file_name)
{
	this->file_name = file_name;
}

//GJK Algorithm and Minkowski Difference
//**************************************

void App::calc_minkowski_diff()
{
	/*
		TODO :
		find the vectors from each vertex in A to each vertex in B
		Use Graham Scan to find the convex hull
		See if orgin is in minkowski difference
		condition (TRUE) : shapes intersect
		condition (FALSE) : shapes do not intersect
	*/
}

void App::calc_gjk()
{
	/*
		TODO : 
		find support points
		find the direction of the orgin
		choose next support points
		find next direction

		form simplex (Triangle) inside of the minkowski difference
		check to see if orgin is inside simplex
			- condition (TRUE) : shapes intersect
			- condition (FALSE) : shapes do not intersect

		draw the Minkowski difference and the simplex as well in the center of the front end app
	*/
}


//Utility Functions for GJK and Minkowski Difference
//**************************************************

bool App::origin_in_simplex()
{
	/* Check to see if origin is inside mikowski difference or simplex */

	return false;
}

void App::find_support_points()
{
	/*Find 3 supporting points to form the simplex */
}
void App::choose_direction()
{
	/* AFter picking the first supporting point, choose a direction relative to the origin position
	*/
}

void App::form_simplex()
{
	//Create the triangle object inside the minkowski difference
	//draw the triangle to the front end
}

void App::shape_subtract()
{
	//Subtract vertices from each shape and use vectors to form the convex hull of minkowski difference
}

void App::check_origin_position() 
{
	/* When choosing the 2nd or 3rd support point for our simplex, 
	we need to check the relative direction of the orgin 
	to choose next supporting point*/
}
