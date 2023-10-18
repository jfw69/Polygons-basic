/** ------------------------------------------------------------------------
* @file			spaceObject.h (header file spaceObject.h) / POLYGONS
* @author		Jason Webster
* @version		4.0
*	CS162-01 Assignement 2.1/2.2
*	version 1.0 was setting up classes and testing code
*	version 2.0 is adding graphics window and testing objects in window
*	version 3.0 is adding loops and arrays for pointers to create multiple
*		asteroids.  Random location created.  Random velocity created.
*		update location of asteroids.  Create a funciton to check for collision.
*	version 4.0 is adding torpedos and collision with asteroids breaking them apart
*/
#ifndef SPACEOBJECT_H_INCLUDED
#define SPACEOBJECT_H_INCLUDED

struct Point {
	double x = 0.0;
	double y = 0.0;
};

enum SpaceObjType { SHIP, ASTEROID, PHOTON_TORPEDO, SHIP_EXPLODING, SHIP_GONE};

class SpaceObject {
public:
	//========================================================================
	//default constructor:
	SpaceObject();

	/* -----------------------------------------------------------------------
	*Constructor with parameters
	*
	*	@param	SpaceObjectType (enum types - ship, astroid, or photon torpedo)
	*	@param	radius			raidus of the object
	*	@param	location		starting point for created object
	*	@param	velocity		starting velocity for created object
	*	@param	angle			starting angle of obect for inital travel
	*	@param	timesDrawn		setting timesDrawn of an object
	*/

	SpaceObject(SpaceObjType type, double radius,
		Point location, Point velocity, double angle, int timesDrawn = 0);

	//========================================================================
	//mutators  // setters

	/*------------------------------------------------------------------------
	* sets type for objects created
	*
	*   @param type - ship, astroid, or photon torpedo
	*
	*	@return true if successful, false otherwise
	*/

	bool setType(SpaceObjType type);

	/* -----------------------------------------------------------------------
	* sets radius for objects created
	*
	*   @param radius - radius of an object
	*
	*	@return true if successful, false otherwise
	*/
	bool setRadius(double radius);

	/* -----------------------------------------------------------------------
	* sets location X,Y for objects created and updated through updatePostition funciton
	*
	*   @param location X - setting X the objects location on the screen
	*	@param location Y - setting Y the objects location on the screen
	*/
	void setLocation(double x, double y);

	/* -----------------------------------------------------------------------
	* sets velocity for objects created and updated through applyThrust function
	*
	*   @param velocity	X - setting the objects velocity for movement across screen
	*	@param velocity Y - setting the objects velocity for movement across screen
	*
	*	@return true if successful, false otherwise
	*/
	bool setVelocity(double velocityX, double velocityY);

	/* -----------------------------------------------------------------------
	* sets angle of movement for objects created and updated through changeAngle function
	*
	*   @param angleDet - setting the angle an object will travel across screen
	*
	*/
	void setAngle(double angleDeg);

	/* -----------------------------------------------------------------------
	* sets number of how many times an object has been drawn
	*
	*   @param timesDrawn - default is 0 set when constructor is called
	*
	*/
	void setTimesDrawn(int timesDrawn);

	//========================================================================
	//accessors  // getters

	/* -----------------------------------------------------------------------
	* gets radius from private member
	*
	*   @return radius
	*/
	double getRadius() const;

	/* -----------------------------------------------------------------------
	* gets location from private member
	*
	*   @return location (x,y)
	*/
	Point getLocation() const;

	/* -----------------------------------------------------------------------
	* gets velocity from private member
	*
	*   @return velocity change in (x,y) values
	*/
	Point getVelocity() const;

	/* -----------------------------------------------------------------------
	* gets angleDeg from private member
	*
	*   @return angleDeg
	*/
	double getAngle() const;

	/* -----------------------------------------------------------------------
	* gets timesDrawn from private member
	*
	*   @return timesDrawn
	*/
	int getTimesDrawn() const;
	
	//========================================================================
	// other functions / methods

	/* -----------------------------------------------------------------------
	* updates position for objects on the screen
	*/
	void updatePostion();

	/* -----------------------------------------------------------------------
	* update angle for objects on the screen
	*
	*	@param angleDeg	- getting the current angle of movement in Degrees
	*/
	void changeAngle(double deltaDeg);

	/* -----------------------------------------------------------------------
	* Draws the spaceobject on the given window
	*
	* 	@param win - the window on to draw the space object
	*/
	void drawObject(sf::RenderWindow& win);

	/* -----------------------------------------------------------------------
	* creates an astroid using provided information
	*
	* 	@param win - the window on to draw the space object
	*/
	void drawAsteroid(sf::RenderWindow& win);

	/* -----------------------------------------------------------------------
	*  creates a spaceship using provided information
	*
	* 	@param win - the window on which we’ll draw the ship
	*/
	void drawShip(sf::RenderWindow& win);

	/* -----------------------------------------------------------------------
	*  creates an explosion using provided information
	*
	* 	@param win - the window on which we’ll draw the ship exploding
	*/
	void drawExplodingShip(sf::RenderWindow& win);

	/* -----------------------------------------------------------------------
	*  moves the spaceship using provided information
	*/
	void applyThrust(double thrust);

	/* -----------------------------------------------------------------------
	*  ship exploding
	* 
	*/
	void explode();

	/* -----------------------------------------------------------------------
	*  redraws ship in middle of screen when clear
	*
	*/
	bool backToMiddle();


private:
	SpaceObjType type;		//type of object
	Point location;			//current location (x,y)
	Point velocity;			//current velocity (in pixels/frame)
	double angleDeg;		//angle object is facing (in degrees)
	double radius;			//gross radius of object (for collision detection)
	int timesDrawn;			// times something is drawn to the screen
};

#endif // !SPACEOBJECT_H_INCLUDED

