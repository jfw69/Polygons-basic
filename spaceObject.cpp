/** ----------------------------------------------------------------------------
* @file			spaceObject.cpp (header file spaceObject.h) / POLYGONS
* @author		Jason Webster
* @version		4.0
*	CS162-01 Assignement 2.1/2.2
*	version 1.0 was setting up classes and testing code
* 	version 2.0 is adding graphics window and testing objects in window
*	version 3.0 is adding loops and arrays for pointers to create multiple
*		asteroids.  Random location created.  Random velocity created.
*		update location of asteroids.  Create a funciton to check for collision.
*	version 4.0 is adding torpedos and collision with asteroids breaking them apart.
*/

#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>
#include "spaceObject.h"
#include "constants.h"

// Default Constructor
SpaceObject::SpaceObject() {
	type = ASTEROID;
	radius = 20;
	location = { 0,0 };
	velocity = { 0,0 };
	angleDeg = 0.0;
	timesDrawn = 0;
}
// Constructor with imputs
SpaceObject::SpaceObject(SpaceObjType type, double radius, Point location,
	Point velocity, double angle, int timesDrawn) {
	if (!setType(type))
		this->type = ASTEROID;
	if (!setRadius(radius))
		this->radius = 20;
	setLocation(location.x, location.y);
	if (!setVelocity(velocity.x, velocity.y)) {
		this->velocity.x = 5;
		this->velocity.y = 5;
	}
	setAngle(angle);
	setTimesDrawn(timesDrawn);

	assert(location.x <= SCREEN_WIDTH && location.y <= SCREEN_HEIGHT);
	assert(angle >= 0 && angle < 360);
}

//  mutators // setters
bool SpaceObject::setType(SpaceObjType type) {
	switch (type) {
	case SHIP:
		this->type = type;
		return true;
	case ASTEROID:
		this->type = type;
		return true;
	case PHOTON_TORPEDO:
		this->type = type;
		return true;
	case SHIP_EXPLODING:
		this->type = type;
		return true;
	case SHIP_GONE:
		this->type = type;
		return true;
	default:
		return false;
	}
}

bool SpaceObject::setRadius(double radius) {
	if (radius < 0 || radius >= static_cast<double>(SCREEN_HEIGHT) / 2) {
		return false;
	}
	this->radius = radius;
	return true;
}

void SpaceObject::setLocation(double x, double y) {
	if (x >= SCREEN_WIDTH)
		this->location.x = (x - SCREEN_WIDTH);
	if (x < 0.0)
		this->location.x = x + SCREEN_WIDTH;
	if (y >= SCREEN_HEIGHT)
		this->location.y = y - SCREEN_HEIGHT;
	if (y < 0.0)
		this->location.y = y + SCREEN_HEIGHT;
	if (x > 0.0 && x < SCREEN_WIDTH)
		this->location.x = x;
	if (y > 0.0 && y < SCREEN_HEIGHT)
		this->location.y = y;
}

bool SpaceObject::setVelocity(double velocityX, double velocityY) {
	if (velocityX > 10 && velocityX < -1.0 || velocityY > 10 && velocityY < -1.0) {
		return false;
	}
	this->velocity.x = velocityX;
	this->velocity.y = velocityY;
	return true;
}

void SpaceObject::setAngle(double angleDeg) {

	if (angleDeg >= 360.0)
		this->angleDeg = angleDeg - 360.0;
	if (angleDeg < 0.0)
		this->angleDeg = angleDeg + 360.0;
	else if (angleDeg >= 0.0 && angleDeg < 360.0)
		this->angleDeg = angleDeg;
}

void SpaceObject::setTimesDrawn(int timesDrawn)
{
	this->timesDrawn = timesDrawn + 1;
}

void SpaceObject::changeAngle(double deltaDeg) {
	if (type != SHIP_EXPLODING) {
		double updatedAngle = angleDeg + deltaDeg;
		setAngle(updatedAngle);
	}
	else
		return;
}

// accessors // getters
double SpaceObject::getRadius() const { return radius; }
Point SpaceObject::getLocation() const { return location; }
Point SpaceObject::getVelocity() const { return velocity; }
double SpaceObject::getAngle() const { return angleDeg; }
int SpaceObject::getTimesDrawn() const { return timesDrawn; }

// other functions for processing code
void SpaceObject::updatePostion() {
	double updatedX = location.x + velocity.x;
	double updatedY = location.y + velocity.y;

	setLocation(updatedX, updatedY);
}

void SpaceObject::drawObject(sf::RenderWindow& win) {
	if (type == SHIP) {
		drawShip(win);
	}
	if (type == SHIP_EXPLODING) {
		if (radius < 30) {
			drawExplodingShip(win);
			radius = radius + 1;
		}
		if (radius == 30) {
			setType(SHIP_GONE);
			setTimesDrawn(timesDrawn);
		}
	}
	if (type == SHIP_GONE) {

	}
	if (type == ASTEROID) {
		drawAsteroid(win);

	}
	if (type == PHOTON_TORPEDO) {
		drawAsteroid(win);
		setTimesDrawn(timesDrawn);
	}

}
void SpaceObject::drawAsteroid(sf::RenderWindow& win) {
	int points = 8;
	sf::CircleShape shape(radius, points);

	sf::Vector2f midpoint(radius, radius);
	shape.setOrigin(midpoint);

	shape.setFillColor(sf::Color(0, 0, 0));
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(255, 255, 255));

	shape.setPosition(location.x, location.y);
	shape.setRotation(angleDeg);
	win.draw(shape);


	//Note: if asteroid is near the edge (within a radius) then we should 
	//draw it again on the other side of the screen so the part off the edge 
	//shows up immediately on the other edge. Code to do that should be added
	//here.
//	double tempRadius = radius;
//	while (location.x + tempRadius >= SCREEN_WIDTH) {
//		shape.setPosition(0 - tempRadius,location.y);
//		win.draw(shape);
//		tempRadius--;
//	}



}

void SpaceObject::drawExplodingShip(sf::RenderWindow& win) {
	int points = 100;
	sf::CircleShape explosionShape(radius, points);

	sf::Vector2f midpoint(radius, radius);
	explosionShape.setOrigin(midpoint);

	explosionShape.setFillColor(sf::Color(255, 255, 255));
	explosionShape.setOutlineThickness(1);
	explosionShape.setOutlineColor(sf::Color(255, 255, 255));

	explosionShape.setPosition(location.x, location.y);
	explosionShape.setRotation(angleDeg);
	win.draw(explosionShape);
}

void SpaceObject::drawShip(sf::RenderWindow& win) {
	sf::ConvexShape shipShape;
	shipShape.setPointCount(3);
	shipShape.setPoint(0, sf::Vector2f(10, 0));
	shipShape.setPoint(1, sf::Vector2f(0, 25));
	shipShape.setPoint(2, sf::Vector2f(20, 25));

	sf::Vector2f midpoint(10, 15);
	shipShape.setOrigin(midpoint);

	shipShape.setFillColor(sf::Color(0, 0, 0));
	shipShape.setOutlineThickness(1);
	shipShape.setOutlineColor(sf::Color(255, 255, 255));

	shipShape.setPosition(location.x, location.y);
	shipShape.setRotation(angleDeg);
	win.draw(shipShape);
}

void SpaceObject::applyThrust(double thrust) {
	if (type != SHIP_EXPLODING) {
		double forcex = cos((angleDeg - 90) * PI / 180.0) * thrust;
		double forcey = sin((angleDeg - 90) * PI / 180.0) * thrust;
		velocity.x = velocity.x + forcex;
		velocity.y = velocity.y + forcey;
	}
	else
		return;
}

void SpaceObject::explode() {
	setType(SHIP_EXPLODING);
	setVelocity(0.0, 0.0);
	changeAngle(0.0);
}

bool SpaceObject::backToMiddle() {
	if (type == SHIP_GONE){// && getTimesDrawn()<= NUMBER_OF_LIVES+1) {		
		return true;
	}
	else
		return false;
}



Point getRandomLocation() {
	Point randomLocation;
	randomLocation.x = rand() % SCREEN_WIDTH;
	randomLocation.y = rand() % SCREEN_HEIGHT;
	// making sure that the asteroids are not in the middle and ship can live
	while (randomLocation.x <= (SCREEN_WIDTH / 2 + SCREEN_WIDTH / 8)
		&& randomLocation.x >= (SCREEN_WIDTH / 2 - SCREEN_WIDTH / 8)
		|| randomLocation.y <= (SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 8)
		&& randomLocation.y >= (SCREEN_HEIGHT / 2 - SCREEN_WIDTH / 8)
		== true) {
		randomLocation.x = rand() % SCREEN_WIDTH;
		randomLocation.y = rand() % SCREEN_HEIGHT;
	}
	return (randomLocation);
}

Point getRandomVelocity() {
	double rangeHigh = 1.0;
	double rangeLow = -1.0;
	Point randomVelocity = { 0,0 };

	int range = (rangeHigh - rangeLow + .001) * 1000;

	randomVelocity.x = double(rand() % range) / 1000 + rangeLow;
	randomVelocity.y = double(rand() % range) / 1000 + rangeLow;
	return (randomVelocity);
}

bool objectsIntersect(SpaceObject* spaceObject1, SpaceObject* spaceObject2) {

	Point objectOne = spaceObject1->getLocation();
	Point objectTwo = spaceObject2->getLocation();

	double object1Radius = spaceObject1->getRadius();
	double object2Radius = spaceObject2->getRadius();
	// sqrt (x2 - x1)^2 + (y2 - y1)^2
	double distanceBetweenTwoObjects =
		sqrt((pow(objectTwo.x - objectOne.x, 2)) + (pow(objectTwo.y - objectOne.y, 2)));
	if (distanceBetweenTwoObjects <= object1Radius + object2Radius)
		return true;
	else
		return false;
}