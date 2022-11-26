#pragma once

#include "GrahamScan.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class App
{
private:
	//Variables needed for front end application
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	//Graham Scan needed fields
	std::string file_name;
	std::vector<Point> p;
	std::stack<Point> convex_hull;


	//Initialize our window and its properties
	void initiateVariables();
	void initiateWindow();
	void initShapes();

	//Convex Objects
	sf::ConvexShape convex1;
	sf::ConvexShape convex2;
	sf::ConvexShape minkowski_diff;

public:
	//Constructor and Destructor
	App();
	~App();

	//Accessors 
	const bool isRunning();

	//Function
	void pollEvents();
	void update();
	void render();
	void setFileName(std::string file_name);
	
	//Graham Scan Functions 
	void initGrahamScan();

	//TODO
	void calc_minkowski_diff();
	void calc_gjk();

	//Utility TODO's
	bool origin_in_simplex();
	void find_support_points();
	void check_origin_position();
	void choose_direction();
	void form_simplex();
	void shape_subtract();
};

