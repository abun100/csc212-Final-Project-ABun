#pragma once
#include <iostream>

#include "ScanImage.h"
#include "minkowski.h"
#include "GJK.h"

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


	//Initialize our window and its properties
	void initiateVariables();
	void initiateWindow();
	void initGrid();
	void initShape();
	void initMinkowski();

	//Convex Objects
	
	sf::ConvexShape polygon1;
	sf::ConvexShape polygon2;
	sf::ConvexShape minkowski_diff;
	float movement_speed;

	//Graham Scan needed fields
	std::vector<Point> convex_hull;
	std::vector<Point> convex_hull2;
	std::vector<Point> minkowski_sum;

	//Variables for app
	sf::Texture grid;
	sf::Sprite background;

public:
	//Constructor and Destructor
	App(std::vector<Point> poly1, std::vector<Point> poly2);
	App();
	~App();

	//Accessors 
	const bool isRunning();

	//Function
	void pollEvents();
	void update();
	void render();
	
	//Shape update
	void keyboard_input();
	void add_points_to_shape(std::vector<Point>& outer_hull, sf::ConvexShape& polygon);
	void update_minkowski_position();

};

