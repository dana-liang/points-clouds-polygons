/* CS 211, Summer 2020
 * dliang26-Polygon.cpp for Project 6 by Dana Liang, 6/7/2020
 * netID: dliang26
 * 
 * This declares the data fields and methods to be included in PointCloud objects.
 */


#ifndef _POINTCLOUD_H
#define _POINTCLOUD_H

#include <cstdlib>
#include <iostream>
#include "dliang26-Point3d.h"

using namespace std;  // Debatable.  Easier for now.

class PointCloud {
	
	// Protected data memebers are accessible to descendants
	
	protected: 
	    Point3d ** points; // Dynamic array of POINTERS TO Point3d objects
	    int nPoints;
	    
	// Private data memebers - Descendants don't need access to these?
	
	private: 
	    int allocated;
	    double luminosity;
	    double lowerBounds[ 3 ];
	    double upperBounds[ 3 ];
	    
	// Public methods
	
	public: 
	    
	    // Two constructors and one destructor
		PointCloud( );
		PointCloud( int initialCapacity );
		virtual ~PointCloud( );
		
		int getNumberOfPoints( );
		virtual bool addPoint( Point3d point ); // Child can override this
		Point3d * getPointByID( int id );
		bool intersect( Point3d point );
		void printStats( ostream & out );
		void printAll( ostream & out );
};

#endif //_POINTCLOUD_H
