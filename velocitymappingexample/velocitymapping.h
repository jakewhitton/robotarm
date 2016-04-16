//Interface for velocitymapping class

class Velocitymapping {
	private:
		//Private stuff
		long double aVel;
		long double bVel;
		const long double length1 = 40.0000; //40cm
		const long double length2 = 50.0000; //50cm
		bool success;
	public:
		//Public stuff
		Velocitymapping();

		void calculateAVel(long double xVel, long double yVel, long double a, long double b);
		void calculateBVel(long double xVel, long double yVel, long double a, long double b);
		long double getAVel();
		long double getBVel();
		bool getSuccess();
};


//Include implementation
#include "velocitymapping.cpp"
