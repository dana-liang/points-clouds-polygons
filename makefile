dliang26-proj6 : dliang26-proj6.o dliang26-Point3d.o dliang26-PointCloud.o dliang26-Polygon.o
	g++ -o dliang26-proj6 dliang26-proj6.o dliang26-Point3d.o dliang26-PointCloud.o dliang26-Polygon.o

dliang26-proj6.o : dliang26-proj6.cpp dliang26-Point3d.h dliang26-PointCloud.h
	g++ -g -c dliang26-proj6.cpp

dliang26-Point3d.o : dliang26-Point3d.cpp dliang26-Point3d.h
	g++ -g -c dliang26-Point3d.cpp

dliang26-PointCloud.o : dliang26-PointCloud.cpp dliang26-PointCloud.h
	g++ -g -c dliang26-PointCloud.cpp

.cpp.o :
	g++ -g -c $<

Debug : dliang26-proj6.cpp
	g++ -o dliang26-proj6 -g -DDEBUG dliang26-proj6.cpp dliang26-Point3d.cpp dliang26-PointCloud.cpp dliang26-Polygon.cpp

clean :
	rm *.o core

