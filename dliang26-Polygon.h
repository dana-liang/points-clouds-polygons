/* CS 211, Summer 2020
 * dliang26-Polygon.cpp for Project 6 by Dana Liang, 6/7/2020
 * netID: dliang26
 * 
 * This declares the data fields and methods to be included in Polygon objects.
 */


#ifndef _POLYGON_H
#define _POLYGON_H

#include "dliang26-PointCloud.h"


class Polygon: public PointCloud {
	
	private: 
		// Private data
	    double normal[ 3 ];	//stores normal of the polygon, calculated when a 3rd point is added
	    
	    // Private methods
		void calcNormal( );
		void calcVector( const Point3d & start, const Point3d & finish, 
			double result[ 3 ] );
		void cross( const double vec1[ 3 ], const double vec2[ 3 ], 
			double result[ 3 ] );
		double dot( const double vec1[ 3 ], const double vec2[ 3 ] );
	    
	public: 
	    
	    // Constructors and destructor
		Polygon( );
		Polygon( int initialCapacity );
		~Polygon( );
	    
		bool addPoint( const Point3d & point ); //overrides PointCloud::addPoint()
		bool isCoplanar( const Point3d & point ); //determine if a proposed point is coplanar
		void printPoly( ostream & outStream ); // means to print a Polygon
};

// TODO:  Add a means of printing Polygons, either as class methods or by operator <<

#endif //_POLYGON_H
