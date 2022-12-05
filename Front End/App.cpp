#include "App.h"


/*
	Class to launch and render the application
*/

//shape.getTransform().transformPoint(shape.getPoint(0)); (Helpful)

//Updates the window
void App::update()
{
	this->pollEvents();

	//Window Bounds Collision

	//Keyboard movement
	keyboard_input();

	//update cordinates for each polygon
	
	//test transform points
	update_minkowski_position();
}

void App::update_minkowski_position() {
	
	sf::Vector2f cordinates1;
	sf::Vector2f cordinates2;
	std::vector<Point> temp_poly;
	std::vector<Point> temp_poly2;
	Point temp;
	Point temp2;

	//Loops through the polygon's verticies and updates the position of each vertex
	//based on where it's location is on screen
	for (int i = 0; i < polygon1.getPointCount(); ++i) {
		cordinates1 = polygon1.getTransform().transformPoint(polygon1.getPoint(i));
		temp.x = cordinates1.x;
		temp.y = cordinates1.y;
		temp_poly.push_back(temp);
	}	

	//Loops through the polygon's verticies and updates the position of each vertex
	//based on where it's location is on screen
	for (int i = 0; i < polygon2.getPointCount(); ++i) {
		cordinates2 = polygon2.getTransform().transformPoint(polygon2.getPoint(i));
		temp2.x = cordinates2.x;
		temp2.y = cordinates2.y;
		temp_poly2.push_back(temp2);
	}

	//Finds our minkowski sum relative to the positions of each polygon
	minkowski sum;
	sum.find_minkowski(temp_poly, temp_poly2);
	minkowski_sum = sum.get_minkowski_sum();
	initMinkowski();

	//GJK collision detector
	GJK collide;
	
	float width1 = polygon1.getTransform().transformPoint(polygon1.getOrigin()).x;
	float height1 = polygon1.getTransform().transformPoint(polygon1.getOrigin()).y;
	float width2= polygon2.getTransform().transformPoint(polygon2.getOrigin()).x;
	float height2 = polygon2.getTransform().transformPoint(polygon2.getOrigin()).y;
	
	collide.find_centroid(height1, width1, height2, width2);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		if (collide.gjk(temp_poly, temp_poly2)) {
			std::cout << "true" << std::endl;
		}
		else {
			std::cout << "false";
		}
	}

	//std::cout << width1 << " " << height1 << std::endl;
}

void App::keyboard_input() {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->polygon1.move(-this->movement_speed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->polygon1.move(this->movement_speed, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->polygon1.move(0.f, -this->movement_speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->polygon1.move(0.f, this->movement_speed);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->polygon1.rotate(0.5);
	}
}


//Renders the convex shapes the front end app
void App::render()
{
	//Reders the Applications 
	this->window->clear();


	//render grid background 
	this->window->draw(this->background);

	//Draw Shapes
	this->window->draw(polygon1);
	this->window->draw(polygon2);
	this->window->draw(minkowski_diff);

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
App::App(std::vector<Point> poly1, std::vector<Point> poly2)
{
	this->convex_hull = poly1;
	this->convex_hull2 = poly2;
	
	this->initiateVariables();
	this->initiateWindow();
	this->initGrid();
	this->initShape();
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
	this->movement_speed = 2.f;
}

//Initiates the size of the window and renders the window
void App::initiateWindow()
{
	//size of the window application
	this->videomode.height = 1000;
	this->videomode.width = 1000;
	this->window = new sf::RenderWindow (this->videomode, "Collision Detection", sf::Style::Titlebar | sf::Style::Close); //initialize window
	

	this->window->setFramerateLimit(60);

}

void App::initGrid()
{
	this->grid.loadFromFile("grid.png");
	this->background.setTexture(this->grid);
}

void App::initShape() {
	
	this->polygon1.setFillColor(sf::Color(255, 255, 255, 0));
	this->polygon1.setOutlineColor(sf::Color::Cyan);
	this->polygon1.setOutlineThickness(1.f);

	this->polygon2.setFillColor(sf::Color(255, 255, 255, 0));
	this->polygon2.setOutlineColor(sf::Color::Green);
	this->polygon2.setOutlineThickness(1.f);
	
	this->minkowski_diff.setFillColor(sf::Color(255, 255, 255, 0));
	this->minkowski_diff.setOutlineColor(sf::Color::Red);
	this->minkowski_diff.setOutlineThickness(1.f);

	this->polygon1.setPointCount(convex_hull.size());
	this->polygon2.setPointCount(convex_hull2.size());
	
	this->polygon1.setPosition(650,250);
	this->polygon2.setPosition(750,250);
	this->minkowski_diff.setPosition(500,500);


	add_points_to_shape(convex_hull, polygon1);
	add_points_to_shape(convex_hull2, polygon2);
	
	polygon1.setOrigin(sf::Vector2f(polygon1.getGlobalBounds().width / 2, polygon1.getGlobalBounds().height / 2));
	polygon2.setOrigin(sf::Vector2f(polygon2.getGlobalBounds().width / 2, polygon1.getGlobalBounds().height / 2));
}

void App::initMinkowski()
{
	this->minkowski_diff.setPointCount(minkowski_sum.size());
	add_points_to_shape(minkowski_sum, minkowski_diff);
}

void App::add_points_to_shape(std::vector<Point>& outer_hull, sf::ConvexShape& polygon)
{
	 
	int numPoints = 0;
	while (!outer_hull.empty()) {
		polygon.setPoint(numPoints, sf::Vector2f(outer_hull.back().x, outer_hull.back().y));
		numPoints++;
		outer_hull.pop_back();
	}
}