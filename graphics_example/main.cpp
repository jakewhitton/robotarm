#include <SDL2/SDL.h>
#include <cmath>
#include <cstdio>

const float pi = 3.1415926;

//Useful structs
struct Vec {
	float x;
	float y;
};
struct Line {
	Vec start;
	Vec end;
};

//Function prototypes
Line calculateLine(float theta, float length, Vec startPoint);
Vec calculateAngularVelocity(float alpha, float beta, Vec velocity);
void drawLine(const Line& line, SDL_Renderer* render);
bool init();
void close();

//USER TWEAKABLE VARIABLES
const int length1 = 300;
const int length2 = 400;
const int margin = 50;
float a = pi / 3;
float b = -pi / 6;
float aVel = 0;
float bVel = 0;
float aVelMax = 2 * pi;
float bVelMax = 2 * pi;


//Init variables
const int SCREEN_WIDTH = 2 * (length1 + length2 + margin);
const int SCREEN_HEIGHT = (2 * margin) + (length1 + length2);
Line line1 = calculateLine(a, length1, Vec{SCREEN_WIDTH / 2, margin});
Line line2 = calculateLine(b, length2, line1.end);
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* args[]) {
	if( !init() ) {
		printf( "Failed to initialize!\n" );
	} else {
		bool quit = false;
		SDL_Event event;

		int ticks = 0;
		int iterationTime = 0;
		bool buttonDown = false;
		Vec origin;
		Vec currentPosition;
		Vec cartesianVelocity;
		Vec angularVelocity;

		while(!quit) {
			ticks = SDL_GetTicks();
			while(SDL_PollEvent( &event ) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
					buttonDown = true;
					origin = Vec{(float)event.button.x, (float)event.button.y};
				}
				
				if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
					buttonDown = false;;
				}
				if (event.type == SDL_MOUSEMOTION) {
					currentPosition = Vec{(float)event.motion.x, (float)event.motion.y};
				}
			}
			
			//Clear screen
			SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderClear( renderer );
			
			//User rendering
		
			//Update cartesian velocity if left mouse button is pressed down
			if (buttonDown) {
				cartesianVelocity = Vec{currentPosition.x - origin.x, (float)-1.0000 * (currentPosition.y - origin.y)};
				angularVelocity = calculateAngularVelocity(a, b, cartesianVelocity);
			} else {
				cartesianVelocity = Vec{0.0000f, 0.0000f};
				angularVelocity = Vec{0.0000f, 0.0000f};
			}
			
			aVel = angularVelocity.x;
			bVel = angularVelocity.y;

			//printf("The angular velocity is <%f, %f>\n", angularVelocity.x, angularVelocity.y);


			//printf("The cartesian velocity is <%f, %f>\n", cartesianVelocity.x, cartesianVelocity.y);

			

			//Update a and b
			a = a + ((float)iterationTime / 1000.0000 * aVel);
			b = b + ((float)iterationTime / 1000.0000 * bVel);

			//Update lines
			line1 = calculateLine(a, length1, line1.start);
			line2 = calculateLine(b, length2, line1.end);
			

			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			drawLine(line1, renderer);
			drawLine(line2, renderer);
			
			//Update screen
			SDL_RenderPresent( renderer );

			//Update iteration time(in ms)
			iterationTime = SDL_GetTicks() - ticks;
		}
	}
	close();
	return 0;
}

Line calculateLine(float theta, float length, Vec startPoint) {
	return Line{startPoint, Vec{startPoint.x + (length * (float)cos(theta)), startPoint.y + (length * (float)sin(theta))}};
}

void drawLine(const Line& line, SDL_Renderer* render) {
	SDL_RenderDrawLine(render, rint(line.start.x), SCREEN_HEIGHT - rint(line.start.y), rint(line.end.x), SCREEN_HEIGHT - rint(line.end.y) );
}

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else {
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL ) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return success;
}

void close() {
	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


Vec calculateAngularVelocity(float alpha, float beta, Vec velocity) {
	float motif1 = (velocity.y * sin(alpha) ) + ( velocity.x * cos(alpha) );
	float motif2 = ( sin(alpha)*cos(beta) ) - ( cos(alpha) * sin(beta) );
	if (motif2 != 0 && alpha != 0) {
		float motif = motif1 / motif2;
		Vec angularVelocityVector = Vec{ -1.0000f / length1 / (float)sin(alpha) * (velocity.x + ( (float)sin(beta) * motif ) ), (float)1 / (float)length2 * motif};
		float scalingFactor = 1;
		if (angularVelocityVector.x > aVelMax) {
			scalingFactor = aVelMax / angularVelocityVector.x;
		} else if (angularVelocityVector.y > bVelMax) {
			scalingFactor = bVelMax / angularVelocityVector.y;
		}
		angularVelocityVector = Vec{angularVelocityVector.x * scalingFactor, angularVelocityVector.y * scalingFactor};
		return angularVelocityVector;
	} else {
		return calculateAngularVelocity(alpha + 0.0001f, beta - 0.0001f, velocity);
	}
}


