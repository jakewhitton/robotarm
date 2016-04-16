//Implementation for velocitymapping class

#ifndef _CMATH_H
#define _CMATH_H
#include <cmath>
#endif

#ifndef _CSTDIO_H
#define _CSTDIO_H
#include <cstdio>
#endif

Velocitymapping::Velocitymapping() {
	//Constructer: do some init stuff
	aVel = -1.0000;
	bVel = -1.0000;
	success = false;
}


void Velocitymapping::calculateAVel(long double xVel, long double yVel, long double a, long double b) {
	try {
		long double motif1 = ( ( sin(a) * yVel ) + ( cos(a) * xVel ) ) 
		     / ( ( sin(a) * cos(b) ) - ( cos(a) * sin(b) ) );
	
		aVel = ( -1 / ( length1 * sin(a) ) ) * ( ( sin(b) * motif1 ) + xVel );
		if ( std::isfinite(aVel) ) {
			success = true;
		} else {
			throw 5;
		}
	} catch (int e) {
		puts("Failed to calculate AVel");
		success = false;
	}
}

void Velocitymapping::calculateBVel(long double xVel, long double yVel, long double a, long double b) {
	try {
		long double motif1 = ( ( sin(a) * yVel ) + ( cos(a) * xVel ) ) 
		     / ( ( sin(a) * cos(b) ) - ( cos(a) * sin(b) ) );
		bVel = ( 1 / length2 ) * ( motif1 );
		if ( std::isfinite(bVel) ) {
			success = true;
		} else {
			throw 5;
		}
	} catch (int e) {
		puts("Failed to calculate BVel");
		success = false;
	}
}

long double Velocitymapping::getAVel() {
	return aVel;
}

long double Velocitymapping::getBVel() {
	return bVel;
}

bool Velocitymapping::getSuccess() {
	return success;
}
