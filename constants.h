/** --------------------------------------------------------
* @file			constants.h (all the constants fheader file spaceObject.h)
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
#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

const int SCREEN_WIDTH = 400;// has to be an even number due to screen wrap and easier to be even
const int SCREEN_HEIGHT = 400;// has to be an even number due to setRadius divides by 2
const double PI = 3.1416;
const int MAX_ASTROIDS = 20;
const int MAX_PHOTONS = 10;
const int PHOTON_LIFE_SPAN = 60;


// const int NUMBER_OF_LIVES = 3;  // works  uncomment games.cpp under backToMiddle and
// uncomment function in spaceObject.cpp under back to middle for working 3 lives

#endif // !CONSTANTS_H_INCLUDED