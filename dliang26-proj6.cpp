/* Written for CS 211, Summer 2020, 6/7/2020.	
 * dliang26-proj6.cpp
 *  
 * Use classes to manage a set of 3d points; add those points to PointCloud objects,
 * and use inheritance to develop a new Polygon class that does not allow duplicates
 * and requires all the points in the Polygon to be coplanar.
 */
 
 #include <cstdlib>
 #include <iostream>
 #include "dliang26-Point3d.h"
 #include "dliang26-PointCloud.h"
 #include "dliang26-Polygon.h"
 
 using namespace std;	// Debatable, but easier for now.
 
 int main( int argc, char ** argv ) {
 	
#ifdef DEBUG

 	// Task 1 - Create and print three Point3ds:
	// One static, one dynamic original, and one dynamic copy.
	cout << "Task 1: create and print 3 Point3ds." << endl;
 	Point3d point1( 1.1, 2.2, 3.3, 4.4 );
 	cout << "Point " << point1.getID( ) << " = " << point1 << endl;
 	
 	Point3d *point2 = new Point3d( 1.2, 3.4, 5.6, 7.8 );
 	cout << "Point " << point2->getID( ) << " = " << *point2 << endl;
 	
 	Point3d *point3 = new Point3d( point1 );
 	cout << "Point " << point3->getID( ) << " = " << *point3 << "\n" << endl;
 	 	
 	// Task2 - Create and print a PointCloud, using the 3 points 	
	cout << "Task 2: create and print a PointCloud using the 3 points." << endl;
 	PointCloud cloud1; // Ten spaces allocated initially by no-arg ctor
 	cloud1.addPoint( point1 );
 	cloud1.addPoint( *point2 );
 	cloud1.addPoint( *point3 );
 	
 	// Try to print points with IDs 0 to 5 from cloud.
 	// Note this uses the "operator <<" method at the bottom of this file.
	// UPDATE:  Only finds 0 and 1, because copy has same ID as source. :-(
 	// Note this uses the "operator <<" method at the bottom of this file.
 	for( int i = 0; i < cloud1.getNumberOfPoints( ) + 3; i++ ) {
 		Point3d *temp = NULL;
 		temp = cloud1.getPointByID( i );
 		if( temp != NULL )
 			cout << "Point " << temp->getID() << " = " << *temp << endl;
 		else
 			cout << "Point " << i << " not found.\n";
	}
	 
	 // New function prints all data, regardless of ID
	 cloud1.printAll( cout );
	 
	// Task3 - Create another PointCloud, and add points till it grows and print it out.
	// Just to be different, we'll make this one dynamically:
	cout << "\nTask 3: create another PointCloud, and add points until it grows.";
 	PointCloud *cloud2 = new PointCloud( 4 ); // Start with 4 spaces this time.
 	// Then add six points
 	cloud2->addPoint( point1 );
 	cloud2->addPoint( *point2 );
 	cloud2->addPoint( *point3 );
 	cloud2->addPoint( point1 );
 	cloud2->addPoint( *point2 );
 	cloud2->addPoint( *point3 );
 	
 	cloud2->printStats( cout );	// Prints all but points
 	// Try to print points with IDs 0 to 7 from cloud.
 	// UPDATE:  Only finds 2 points, because copies have the same ID :-(
 	for ( int i = 0; i < cloud2->getNumberOfPoints( ) + 2; i++ ) {
 		Point3d *temp = NULL;
 		temp = cloud2->getPointByID( i );
 		if( temp != NULL )
 			cout << "Point " << temp->getID() << " = " << *temp << endl;
 		else
 			cout << "Point " << i << " not found.\n";
	 }

	// Task4 - Create additional Point3ds as needed, and test
	// the intersect method.  Report results for interior, exterior,
	// and edge cases.

	cout << "\nTask 4: Testing intersection." << endl;
	Point3d point4( 1.1, 2.2, 3.3, 1.0 ); // edge case (on lower boundary)
	Point3d point5( 1.2, 3.4, 5.6, 1.0 ); // edge case (on upper boundary)
	Point3d point6( 1.15, 2.25, 3.35, 1.0 ); // interior case (inside boundaries)
	Point3d point7( 0.0, 0.0, 0.0, 1.0 ); // exterior case (outside boundaries)

	// test points on previously created PointCloud cloud2
	if ( cloud2->intersect(point4) == true )
		cout << point4 << " intersects cloud2." << endl;
	else
		cout << point4 << " doesn't intersect cloud2." << endl;

	if ( cloud2->intersect(point5) == true )
		cout << point5 << " intersects cloud2." << endl;
	else
		cout << point5 << " doesn't intersect cloud2." << endl;

	if ( cloud2->intersect(point6) == true )
		cout << point6 << " intersects cloud2." << endl;
	else
		cout << point6 << " doesn't intersect cloud2." << endl;

	if ( cloud2->intersect(point7) == true )
		cout << point7 << " intersects cloud2." << endl;
	else
		cout << point7 << " doesn't intersect cloud2." << endl;
	
	// Task5 - Using a new PointCloud, read in data using the sample
	// input files from Project 2, and verify your classes fully
	// implement the project 2 assignment.  You can read from 
	// standard input ( using "cin >> variable;" ) or read from a
	// file whose name is given as a command-line argument.
	cout << "\nTask 5: Use a new PointCloud, cloud3 to test input data from project 2." << endl;
	PointCloud *cloud3 = new PointCloud();

	// Take in input, make new Point3ds, and add them to cloud3 a until a negative luminosity is read
	double X, Y, Z, luminosity;
	cin >> X >> Y >> Z >> luminosity;

	while ( luminosity >= 0 ) {
		Point3d* point = new Point3d( X, Y, Z, luminosity);
		cloud3->addPoint( *point );
		delete point;
		cin >> X >> Y >> Z >> luminosity;
	}

	cloud3->printStats( cout );

	//Then, take in a second set of input to check if they intersect with the PointCloud
	cin >> X >> Y >> Z >> luminosity;
	while ( luminosity >= 0 ) {
		Point3d* point = new Point3d( X, Y, Z, luminosity);
		if ( cloud3->intersect(*point) == true )
			cout << *point << " intersects cloud3." << endl;
		else
			cout << *point << " doesn't intersect cloud3." << endl;
		delete( point );
		cin >> X >> Y >> Z >> luminosity;
	}

	// Task6 - Create and print Polygons.
	// Test the isCoplanar and intersection methods.
	// Sample points:  ( 0.0, 0.0, 0.0 ), ( 1.0, 1.0, 0.0 ),
	// ( 0.0, 1.0, 1.0 ), ( 1.0, 1.0, 1.0 ), ( 1.0, 2.0, 1.0 )
	cout << "\nTask 6: Create and print polygons." << endl;
	Polygon poly;
	Point3d point8( 0.0, 0.0, 0.0, 0.0 );
	Point3d point9( 1.0, 1.0, 0.0, 0.0 );
	Point3d point10( 0.0, 1.0, 1.0, 0.0 );
	Point3d point11( 1.0, 1.0, 1.0, 0.0 );	
	Point3d point12( 1.0, 2.0, 1.0, 0.0 );
	Point3d point13( point8 ); // check if same ID point will give an error

	poly.addPoint(point8);
	poly.addPoint(point9);
	poly.addPoint(point10);
	poly.addPoint(point13);
	cout << "CHECK: PRINTING POLY..." << endl; // checking addPoint
	poly.printPoly( cout );
	poly.printStats( cout );

	// Checking isCoplanar: point11 should not be coplanar, point12 is.
	if ( poly.isCoplanar(point11) )
		cout << point11 << " is coplanar with poly!" << endl;
	else
		cout << point11 << " is not coplanar with poly." << endl;

	if ( poly.isCoplanar(point12) )
		cout << point12 << " is coplanar with poly!" << endl;
	else
		cout << point12 << " is not coplanar with poly." << endl;


	// Checking intersection: points 10, 11 should intersect; 12 should not.
	if ( poly.intersect(point10) )
		cout << point10 << " intersects with poly!" << endl;
	else
		cout << point10 << " doesn't intersect poly." << endl;

	if ( poly.intersect(point11) )
		cout << point11 << " intersects with poly!" << endl;
	else
		cout << point11 << " doesn't intersect poly." << endl;

	if ( poly.intersect(point12) )
		cout << point12 << " intersects with poly!" << endl;
	else
		cout << point12 << " doesn't intersect poly." << endl;

	
#endif
	
	// Task 7 - Read and process the following input data:
	
	// 1. A series of Point3d lines to create a Polygon object,
	//    terminated by a Point3d with negative luminosity.
	//    Any point that cannot be added to the polygon should
	//    be printed out in an error message.
	cout << "\nTask 7.1: Read in Point3d's to create a Polygon, and terminate with a negative luminosity." << endl;
	Polygon polygon;
	double x, y, z, lum;
	cin >> x >> y >> z >> lum;
	cout << endl;

	while ( lum >= 0 ) {
		Point3d* point = new Point3d( x, y, z, lum );
		polygon.addPoint( *point );
		delete point; // free memory so that it's not lost after exiting the loop
		cin >> x >> y >> z >> lum;
	}

	polygon.printStats( cout );

	// 2. A second set of Point3d lines, terminated by a point
	//    with a negative luminosity.  For each of these points,
	//    determine whether the point is coplanar with the polygon
	//    and whether the point intersects with the polygon ( i.e.
	//    with the polygon's bounding box ), and report the results.
	cout << "\nTask 7.2: Read in Point3d's to check if they are coplanar and/or intersect with the polygon,"
		<< " and terminate with a negative luminosity." << endl;

	cin >> x >> y >> z >> lum;
	cout << endl;

	while ( lum >= 0 ) {
		Point3d* point = new Point3d( x, y, z, lum );
		if ( polygon.isCoplanar( *point ) )
			cout << *point << " is coplanar!" << endl;
		else
			cout << *point << " is not coplanar." << endl;
		if ( polygon.intersect( *point ) )
			cout << *point << " intersects the polygon! "<< endl;
		else
			cout << *point << " doesn't intersect the polygon." << endl;
		delete point; // free memory so that it's not lost after exiting the loop
		cin >> x >> y >> z >> lum;
	}
	 
#ifdef DEBUG
	// Release dynamic memory from the individual dynamic points
 	delete( point2 );
	point2 = NULL;
 	delete( point3 );
	point3 = NULL;
	delete ( cloud2 );
	cloud2 = NULL;
	delete ( cloud3 );
	cloud3 = NULL;
#endif

	return 0;
  	
 } // main
 

