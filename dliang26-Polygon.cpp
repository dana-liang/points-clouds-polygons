/* CS 211, Summer 2020
 * dliang26-Polygon.cpp for Project 6 by Dana Liang, 6/7/2020
 * netID: dliang26
 * 
 * Actual code for Polygon objects: include class methods for:
 * 		- initializing the Polygon
 * 		- adding points to the Polygon
 * 		- calculating and storing the normal of the Polygon
 */


#include "dliang26-Polygon.h"

/* No-arg constructor calls the parent no-arg constructor */
Polygon::Polygon() : PointCloud() {
}

/* Constructor calls the parent constructor */
Polygon::Polygon( int initialCapacity ) : PointCloud( initialCapacity ) {
}

/* Destructor */
Polygon::~Polygon( ) {
}

/*  The Polygon::addPoint method first ascertains whether it is acceptable
	to add the given point to the polygon.  Reasons for rejecting the point
	would be if the ID of the point already exists in the Polygon, or if the 
	point is not coplanar with the points already in the Polygon.  ( Use the 
	getPointByID( ) and isCoplanar( ) methods to check these two conditions. )
	
	If Polygon::addPoint finds the point unacceptable, it should return false;
	
	If Polygon::addPoint finds the point acceptable, then it should pass the 
	point to PointCloud::addPoint( Point3d ) to do the actual adding of the 
	point.
	
	If nPoints becomes 3 as a result of adding this point, then calcNormal( ) 
	should be called to calculate the normal to the polygon.
*/

bool Polygon::addPoint( const Point3d & point ) {
	/* check if ID is already in the polygon; if it is, return false */
	for ( int i = 0; i < this->nPoints; i++ ) {
		if ( point.getID() == this->points[i]->getID() ) {
			cout << point << " is already in the Polygon!" << endl;
			return false;
		}
	}

	/* check if the point is coplanar, if it isn't, return false */
	if ( !isCoplanar( point ) ) {
		cout << point << " is not coplanar!" << endl;
		return false;
	} 

	PointCloud::addPoint( point );
	if ( this->nPoints == 3 ) {
		calcNormal();
	}
	return true;
}

/*  The isCoplanar method determines if the passed Point3d is coplanar with the 
	existing points of the polygon, ( or at least not out of the plane of the 
	existing points ), as follows:
	
	1. If nPoints is less than 3, return true.  The point is not out of the 
	   plane.
	2. Otherwise create a vector from the first point in the Polygon 
	   ( points[0] ) to the passed point.
	3. Then calculate the dot product between the vector created in step 2 and 
	   the normal.
	4. If the absolute value of the dot product is less than some small 
	   tolerance, say 1.0E-6, then return true;  Otherwise return false.
*/
bool Polygon::isCoplanar( const Point3d & point ) {
	double result[3];
	// (1) point is always coplanar if there are <3 points
	if ( this->nPoints < 3 ) 
		return true;

	else {
		// (2) create vector from first point to the passed point
		calcVector( *this->points[0], point, result ); 
		// (3) find dot product of created vector and the normal (3)
		double dotProd = abs( dot( result, this->normal ) );
		// (4) if absolute value of the dot product is < a small tolerance
		if ( dotProd < 1.0E-6 ) 
			return true;
		else
			return false;
	}
}

/*  The normal to the polygon is calculated as the cross product between two 
	vectors, both of which lie in the plane of the Polygon, as follows:
	
	1. Create a vector from points[ 0 ] to points[ 1 ]
	2. Create a second vector from points[ 0 ] to points[ 2 ]
	3. Calculate the cross product of the first vector and the second,
	   and save the result in normal[ ].

*/
void Polygon::calcNormal() {

	double vec1[3], vec2[3];
	calcVector( *this->points[0], *this->points[1], vec1 ); // (1)
	calcVector( *this->points[1], *this->points[2], vec2 ); // (2)
	cross( vec1, vec2, this->normal); // (3)
	
}

/*  calcVector calculates a vector from point 1 to point 2, by simply 
	subtracting their components in the X, Y, and Z directions respectively. 
	X = X2 - X1, Y = Y2 - Y1, Z = Z2 - Z1.

*/
void Polygon::calcVector( const Point3d & start, const Point3d & finish, 
	double result[ 3 ] ) {
	
	result[0] = finish.getX() - start.getX();
	result[1] = finish.getY() - start.getY();
	result[2] = finish.getZ() - start.getZ();
}

/*  The cross product between two vectors is a third vector, which is 
	perpendicular to the first two and which obeys the "right hand rule".
	The formula for calculating the cross of 
	vec1 = ( X1, Y1, Z1 ) x vec2 = ( X2, Y2, Z2 ) is:
	
	X = Y1 * Z2 - Y2 * Z1
	Y = Z1 * X2 - Z2 * X1
	Z = X1 * Y2 - X2 * Y1
*/

void Polygon::cross( const double vec1[ 3 ], const double vec2[ 3 ], 
	double result[ 3 ]) {

	result[0] = ( vec1[1] * vec2[2] ) - ( vec2[1] * vec1[2] );
	result[1] = ( vec1[2] * vec2[0] ) - ( vec2[2] * vec1[0] );
	result[2] = ( vec1[0] * vec2[1] ) - ( vec2[0] * vec1[1] );
}

/*  The dot product of two vectors is simply the sum of the products of their
	components, i.e. X1 * X2 + Y1 * Y2 + Z1 * Z2.  The result will be zero if
	the two vectors are perpindicular to each other.
*/
double Polygon::dot( const double vec1[ 3 ], const double vec2[ 3 ] ) {

	double dot;
	dot = ( vec1[0] * vec2[0] ) + ( vec1[1] * vec2[1] ) + ( vec1[2] * vec2[2] );

	return dot;
}

/* Allow printing all the points in the polygon */ 
void Polygon::printPoly( ostream & outStream ) {
	for ( int i = 0; i < this->getNumberOfPoints(); i++ ) {
		cout << "Point " << i << ": ";
		outStream << *this->points[i] << endl;
	}
}


