/* CS 211, Summer 2020
 * dliang26-Point3d.h for Project 6 by Dana Liang, 6/7/2020
 * netID: dliang26
 * 
 * This declares the data fields and methods to be included in Point3d objects.
 */


#ifndef _POINT3D_H
#define _POINT3D_H

#include <cstdlib>
#include <iostream>
using namespace std;

class Point3d {
	
	/* Private data members */
		
	private: 
	    int ID;
	    static int nextID;
	    double X;
	    double Y;
	    double Z;
	    double luminosity;
	    
	/* Public methods */
	
	public: 
	    
		// Two constructors and one destructor
		Point3d( double X, double Y, double Z, double luminosity );
		Point3d( const Point3d & point ); // Copy constructor
		~Point3d( );
		
		// Getters
		int getID( ) const;    
		double getX( ) const;    
		double getY( ) const;    
		double getZ( ) const;    
		double getLuminosity( ) const;

};

 
// Function prototype.  The following is not a class method
ostream & operator << ( ostream & out, Point3d point );


#endif //_POINT3D_H
