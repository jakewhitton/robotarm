#include <cstdio>
#include <cmath>
#include "velocitymapping.h"

#define PI 3.1415926


int main() {
	Velocitymapping map;
	
	long double aDegrees = 45.0000;
	long double bDegrees = -45.0000;
	
	long double a = aDegrees * ( PI / 180 );
	long double b = bDegrees * ( PI / 180 );
	
	long double xVel = 1.0000;
	long double yVel = 1.0000;
	
	map.calculateAVel(xVel, yVel, a, b);
	map.calculateBVel(xVel, yVel, a, b);
	
	if ( map.getSuccess() == true ) {
		printf("If a is %.2Lf rad or %.2Lf degrees, b is %.2Lf rad or %.2Lf degrees, xVel is %.2Lf, and yVel is %.2Lf:\n\naVel is %.4Lf\n\nbVel is %.4Lf\n", a, aDegrees, b, bDegrees, xVel, yVel, map.getAVel(), map.getBVel() );
	} else {
		printf("Failed to calculate aVel or bVel.\n");
	}
}
