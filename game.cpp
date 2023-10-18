/* ---------------------------------------------------------------------------
* @file			game.cpp / POLYGONS
* @author		Jason Webster
* @version		4.0
*	CS162-01 Assignement 2.1/2.2/2.3
*	version 1.0 was setting up classes and testing code
*	version 2.0 is adding graphics window and testin objects in window
*	version 3.0 is adding loops and arrays for pointers to create multiple
*		asteroids.  Random location created.  Random velocity created.
*		update location of asteroids.  Create a funciton to check for collision.
*	version 4.0 is adding torpedos and collision with asteroids breaking them apart.
*
*
* Demonstrates:
*   Working with Classes
*	Working with header files
*	v1.0 was working with test values to ensure code does not break
*	Working with graphics windows and object minupluating objects
*	v2.0 was creating 1 asteroid and giving the ability for the user to move
*		the ship.
*	v3.0 is implemeting function calls with pointers and creating mutilple
*		asteroids using arrays and loops.  2nd part of 3.0 was checking for
*		collisions between ship and all asteroids using loops and pointers.
*	v4.0 is implemting the addition of PHOTON_TORPEDOS and using dynamically
*		allocated memory for additional space objects.
*
* pseudo code
*	Create Header files for funciton prototypes and constant
*	Create Classes with constructors, mutators, accessors
*		public and private values
*		setting up function calls within the class that also
*			check for errors
*			check for errors
*	Create struct for x,y locations
*	Create enumerated types
*	Create game window using SFML
*		Create objects for use in SFML window
*		Create ability to move objects via keyboard input
*		Create torepedos moving from front of ship outward, checking
*			collision and redrawing asteroids
*
*	Create multiple asteroids using allocated memory using arrays and loops and pointers
*	Create multiple torpedos using allocated memory using arrays and loops and pointers
*
*	Update position of asteroids, ship, and photon torpedoes using loops and pointers
*
*	Check for collision between SHIP and Asteroids using points and loops
*	Check for collision between photon torpedoes and asteroids.
*	If torepedoe hits asteroid redraw 2 smaller ones (after reduction by 2 times remove)
*	Check for how long a torpedo exist and deleting pointer and giving back memory.
*	Check for size of asteroid before redraw and if it is to small delete it
*	
*	When all asteroids are destroyed create new ones
*/

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "constants.h"
#include "spaceObject.h"


/* -----------------------------------------------------------------------
*  random generates location x and y
*
*	@return Point
*/
Point getRandomLocation();

/* -----------------------------------------------------------------------
*  random generates velocity x and y
*
*	@return Point
*/
Point getRandomVelocity();

/* -----------------------------------------------------------------------
*  determines the distance between two objects
*
*	@param pointer to object
*	@param pointer to 2nd object
*
*	@return true if within bounds
*/
bool objectsIntersect(SpaceObject* ship, SpaceObject* asteroids);

//============================================================================
int main() {

	srand(time(NULL));
	
	//create graphics window
	sf::RenderWindow window(
		sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
		"Polygons!",
		sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);

	SpaceObject* asteroids[MAX_ASTROIDS] = { nullptr };
	SpaceObject* photons[MAX_PHOTONS] = { nullptr };

	// set number of asteroids  == 5
	for (int i = 0; i < 5; i++) {
		asteroids[i] = new SpaceObject{ ASTEROID, 20, getRandomLocation(), getRandomVelocity(), 180 };
	}
	//create ship
	SpaceObject* ship = nullptr;
	ship = new SpaceObject{ SHIP , 3, {SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2}, {0,0}, 0 };


	//game loop
	while (window.isOpen()) {
		//handle user input (events and keyboard keys being pressed)
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// creating torpedos using ships position and angle
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				int x = 0;
				while (x < MAX_PHOTONS && photons[x] != nullptr)
					x++;
				if (x < MAX_PHOTONS) {
					photons[x] = new SpaceObject{ PHOTON_TORPEDO, 2, ship->getLocation(), ship->getVelocity(), ship->getAngle() };
					photons[x]->applyThrust(5);
				}
			}
		}
		// ship movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ship->changeAngle(-5.0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ship->changeAngle(+5.0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ship->applyThrust(0.5);
		// update game objects ------------------------------------------
		for (int i = 0; i < MAX_ASTROIDS; i++) {
			if (asteroids[i] != nullptr) {
				asteroids[i]->updatePostion();
				asteroids[i]->changeAngle(5);
			}
		}
		for (int i = 0; i < MAX_PHOTONS; i++) {
			if (photons[i] != nullptr) {
				photons[i]->updatePostion();
			}
		}
		// checking to see if photons hit asteroids --- if true break them into 2
		// and draws them in the exact location of original
		// not sure if i can split this into small functions 
		// using the just deleted pointer as one smaller rock - becasuse i know it is nullptr
		// using a while loop to find the next open slot and draws the 2nd rock
		for (int i = 0; i < MAX_PHOTONS; i++) {
			for (int j = 0; j < MAX_ASTROIDS; j++) {
				if (photons[i] != nullptr && asteroids[j] != nullptr) {
					if (objectsIntersect(photons[i], asteroids[j]) == true) {
						Point holdLocation = asteroids[j]->getLocation();
						double holdRadius = asteroids[j]->getRadius();
						delete asteroids[j];
						asteroids[j] = nullptr;
						delete photons[i];
						photons[i] = nullptr;
						// checking on size of asteroid if it is below a 1/4 original size do not draw
						if (holdRadius > 20.0 / 4) {
							asteroids[j] = new SpaceObject{ ASTEROID, holdRadius / 2, holdLocation, getRandomVelocity(), 180 };
							int x = 0;
							while (x < MAX_ASTROIDS && asteroids[x] != nullptr)
								x++;
							if (x < MAX_ASTROIDS) {
								asteroids[x] = new SpaceObject{ ASTEROID, holdRadius / 2, holdLocation, getRandomVelocity(), 180 };

							}
						}
					}
				}
			}
		}
		ship->updatePostion();

		// Ship CRASH!!!!
		for (int i = 0; i < MAX_ASTROIDS; i++) {
			if (asteroids[i] != nullptr) {
				if (objectsIntersect(ship, asteroids[i]) == true) {
					ship->explode();
				}
			}
		}

		// draw new frame -----------------------------------------------
		window.clear();
		for (int i = 0; i < MAX_ASTROIDS; i++) {
			if (asteroids[i] != nullptr)
				asteroids[i]->drawObject(window);
		}
		for (int i = 0; i < MAX_PHOTONS; i++) {
			if (photons[i] != nullptr)
				photons[i]->drawObject(window);
		}
		for (int i = 0; i < MAX_PHOTONS; i++) {
			if (photons[i] != nullptr) {
				int timesDrawn = photons[i]->getTimesDrawn();
				if (timesDrawn >= PHOTON_LIFE_SPAN) {
					delete photons[i];
					photons[i] = nullptr;
				}
			}

		}
		ship->drawObject(window);

		// checks to see if SHIP_GONE then redraws ship in the middle of the screen
		if (ship->backToMiddle() == true) {
			//int lives = ship->getTimesDrawn();  //  add lives to end of new spaceObject when ready
			delete ship;
			ship = nullptr;
			ship = new SpaceObject{ SHIP , 3, {SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2}, {0,0}, 0, };
		}

		//checks to see if all asteroids are gone, if so draw 5 new ones
		int count = 0;
		for (int i = 0; i < MAX_ASTROIDS; i++) {
			if (asteroids[i] == nullptr) {
				count++;
			}
		}
		if (count == 20) {
			for (int i = 0; i < 5; i++) {
				asteroids[i] = new SpaceObject{ ASTEROID, 20, getRandomLocation(), getRandomVelocity(), 180 };
			}
		}


		window.display();
	}
	return 0;
}

/*____________________________________________________________________________
* NOTES FOR FUTHER WORK TO BE DONE // CURRENT ISSUES WITH RUNNING OR CODE
*
*	 working on asteroid near the edge of the screen redraw - have it create the first 1/2
*		but it jumps when it hits the center of the asteroid
*
**		WORKING ON LIVEs COUNT = 3 THEN 2 THEN 1 THEN GAME OVER
			it works // but i have commneted it out just to submit working version 4
*
*
*	WORKS 2/19/2023 10:07 am  SAVED
*
*	torpedos fire from front of ship and move correctly across screen
*		delete after 60 redraws - works
*
*	explosion works ship disappears and reappears in the middle
*
*	torpedo hits asteroid and disappear, asteroid is split into 2 and reduced by 1/2 radius
*
*	starts with 5 Astroid moves across screen and reappears on other side / top / bottom
*
*	Ship moves with UP button pressed and turns LEFT and RIGHT when button is
*		pressed and reappears on other side / top / bottom
*
*/