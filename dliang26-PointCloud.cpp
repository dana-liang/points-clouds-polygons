/* CS 211, Summer 2020
 * dliang26-PointCloud.cpp for Project 6 by Dana Liang, 6/7/2020
 * netID: dliang26
 * 
 * Actual code for PointCloud objects:
 * Include class methods for initializing the PointCloud,
 * Adding points to the PointCloud,
 * Checking if points intersect with the PointCloud,
 * Printing information about the PointCloud.
 */

#include "dliang26-PointCloud.h"

using namespace std; // Debatable, but easier for now.

/*  Constructors initialize class variables, many to zero.
	PointCloud constructors need to set allocated according
	to the initial size of the dynamic array of Point3d pointers,
	and then use new to dynamically allocate an array of that
	size for points.  Note that points is of type Point3d **,
	i.e. an array of ( pointers to Point3d objects. )  The actual
	points will be dynamically allocated later by addPoint.
	( It wouldn't hurt to set all the pointers to NULL initially. )
*/

// No-argument constructor.  Set allocated to 10 by default
// Initialize all variables and dynamically allocate memory
PointCloud::PointCloud( ) {
	
	this->allocated = 10;
	this->points = NULL;
	this->nPoints = 0;
	this->points = new Point3d*[this->allocated];	// allocate array of this->allocated
	for ( int i = 0; i < this->allocated; i++ ) {	// set all pointers to NULL
		this->points[i] = NULL;
	}
	this->luminosity = 0;

} // Constructor ( )

// Constructor with an argument. 
// Set allocated to the value of the passed-in argument
PointCloud::PointCloud( int initialCapacity) {

	this->allocated = initialCapacity;
	this->points = NULL;
	this->nPoints = 0;
	this->points = new Point3d*[this->allocated];	// allocate array of this->allocated
	for ( int i = 0; i < this->allocated; i++ ) {	// set all pointers to NULL
		this->points[i] = NULL;
	}
	this->luminosity = 0;

} // Constructor( int )

// Destructor needs to free all associated dynamic memory
// This includes all the dynamically allocated Point3ds
// AND the dynamically allocated array holding them.
PointCloud::~PointCloud( ) {

	for ( int i = 0; i < this->allocated; i++ ) {
		delete ( this->points[i] );
		this->points[i] = NULL;
	}
	delete [] this->points;

} // Destructor

// This looks like a getter, but it could also count points instead
int PointCloud::getNumberOfPoints( ) {
	return this->nPoints;
} // getNumberOfPoints

// Add a point to the cloud.  Allocate new memory as needed.
// Returns true if successful, false otherwise
bool PointCloud::addPoint( Point3d point ) {

	// Dynamically allocate a new Point3d, using the copy constructor
	Point3d* pPtr = new Point3d(point);

	if ( pPtr == NULL ) //if new returns NULL, return and don't continue
		return false;

	/* Double the array space if more points are entered than initially allocated */
	if ( (this->nPoints) == this->allocated ) {
		Point3d** temp = this->points;
	    this->points = new Point3d*[this->nPoints * 2];
	    for ( int j = 0; j < this->nPoints; j++ ) {
			this->points[j] = temp[j];
		}
	    delete [] temp;
		this->allocated *= 2;
	}

	this->points[this->nPoints] = pPtr; // add to the array
	this->nPoints++; 	// count points

	// find upper and lower bounds and average luminosity of the PointCloud
	this->lowerBounds[0] = this->points[0]->getX();
	this->upperBounds[0] = this->points[0]->getX();
	this->lowerBounds[1] = this->points[0]->getY();
	this->upperBounds[1] = this->points[0]->getY();
	this->lowerBounds[2] = this->points[0]->getZ();
	this->upperBounds[2] = this->points[0]->getZ();
	this->luminosity = 0;
	
	for ( int i = 0; i < this->nPoints; i++ ) {

		if ( this->points[i]->getX() < this->lowerBounds[0] )
			this->lowerBounds[0] = this->points[i]->getX();
		
		if ( this->points[i]->getX() > this->upperBounds[0] )
			this->upperBounds[0] = this->points[i]->getX();

		if ( this->points[i]->getY() < this->lowerBounds[1] )
			this->lowerBounds[1] = this->points[i]->getY();
		
		if ( this->points[i]->getY() > this->upperBounds[1] )
			this->upperBounds[1] = this->points[i]->getY();

		if ( this->points[i]->getZ() < this->lowerBounds[2] )
			this->lowerBounds[2] = this->points[i]->getZ();
		
		if ( this->points[i]->getZ() > this->upperBounds[2] )
			this->upperBounds[2] = this->points[i]->getZ();

		this->luminosity = this->luminosity + this->points[i]->getLuminosity();
	}

	this->luminosity = this->luminosity / (double)this->nPoints;
	
	return true;

} // addPoint

// Return true if there is an intersection, false otherwise
bool PointCloud::intersect( Point3d point ) {
	
	if (point.getX() >= this->lowerBounds[0] && point.getX() <= this->upperBounds[0] &&
		point.getY() >= this->lowerBounds[1] && point.getY() <= this->upperBounds[1] &&
		point.getZ() >= this->lowerBounds[2] && point.getZ() <= this->upperBounds[2] )
			return true;

	else
		return false;
} // intersect

// The following function "prints" to outStream all the information about
// a PointCloud, except the actual points themselves.
void PointCloud::printStats( ostream & outStream ) {
	
	outStream << "\nPointCloud has " << nPoints << " stored out of " << allocated << " available.\n";
	
	cout << "Lower Bounds (X Y Z): ";
	for ( int i = 0; i < 3; i++ ) {
		cout << this->lowerBounds[i] << " ";
	}
	cout << "\nUpper Bounds (X Y Z): ";
	for ( int i = 0; i < 3; i++ ) {
		cout << this->upperBounds[i] << " ";
	}

	cout << "\nAverage Luminosity: " << this->luminosity << endl;
	return;

} // printStats

// The following function "prints" to outStream all the information about
// a PointCloud, INCLUDING ALL POINTS, regardless of their ID
void PointCloud::printAll( ostream & outStream ) {
	
	printStats( outStream ); // First call the other function for basics
	
	//Loop through points and print using: outStream << *points[ ] 
	for ( int i = 0; i < this->nPoints; i++ ) {
		cout << "Point " << points[i]->getID( ) << ": ";
		outStream << *points[i] << endl;
	}
	
	return;
} // printStats

// Return the address of the point with the given ID, or NULL otherwise
Point3d * PointCloud::getPointByID( int id ) {
	
	Point3d* temp = NULL;
	if ( ( this->points[id] != NULL ) && // if the pointer we are accessing is not NULL
		 ( this->points[id]->getID() == id ) ) { // and the ids match
		temp = this->points[id];
	}

	return temp;
} // getPointByID



