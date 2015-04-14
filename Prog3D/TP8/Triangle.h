#ifndef Triangle_h
#define Triangle_h

#include "../TP1/Point.h"
#include <vector>

class Triangle{

	private:
		Point sommetA;
		Point sommetB;
		Point sommetC;
		
	public:
		Triangle(Point premierSommet, Point secondSommet, Point troisiemeSommet);
		Point getSommetA();
		Point getSommetB();
		Point getSommetC();
		bool compareTriangle(Triangle t);
		std::vector<Point> getSommets(); 

};

#endif 
