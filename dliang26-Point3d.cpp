/* CS 211, Summer 2020
 * dliang26-Point3d.cpp for Project 6 by Dana Liang, 6/7/2020
 * netID: dliang26
 * 
 * Actual code for Point3d objects:
 * Initialize the static int class variable, and use classes and class methods
 * to build Point3ds.
 */

#include "dliang26-Point3d.h"

/* Point3d implementation */
 
// Initialize the static int class variable.
int Point3d::nextID = 0;
 
// Two constructors
// Note that the first one  must assign a new unique value to ID, 
// making use of static int nextID

/* set all class variables to the arguments provided */
Point3d::Point3d( double X,  double Y,  double Z,  double luminosity ) {
	
	this->X = X;
	this->Y = Y;
	this->Z = Z;
	this->luminosity = luminosity;
	this->ID = this->nextID;
	this->nextID++;
}

/*  The copy constructor should copy all the data of the input point,
	including the ID.  That has potential problems, but is better than
	the alternative ( creating a new unique ID for the copy ) for our
	purposes at the moment.
	
	Note:  This is an important function, because the system uses it 
	every time a Point3d is passed by value, by copying the Point3d
	onto the call stack.  Strange things break until you write this.	
*/

Point3d::Point3d( const Point3d & point ) {
	
	this->X = point.X;
	this->Y = point.Y;
	this->Z = point.Z;
	this->luminosity = point.luminosity;
	this->ID = point.ID;
}

// Destructor.  ( This method has nothing to do right now. )

Point3d::~Point3d( ) {
	
}

// Getters return class values

int Point3d::getID( ) const {
	return this->ID;
}

double Point3d::getX( ) const {
	return this->X;
}

double Point3d::getY( ) const {
	return this->Y;
}

double Point3d::getZ( ) const {
	return this->Z;
}

double Point3d::getLuminosity( ) const {
	return this->luminosity;
}
 
 // The following method allows code like this, where p is a Point3d:
 //			cout << "Point p = " << p << endl;
 // Note the code sends output to the variable "out", not cout
 
 ostream & operator << ( ostream & out, Point3d point ) {

 	out << "( X: " << point.getX( );
	out << ", Y: " << point.getY( );
	out << ", Z: " << point.getZ( );
	out << "	Lum: " << point.getLuminosity( );
 	out << " )";
 	
 	return out; 	
 	
 } // operator << ( ostream &, Point3d )
