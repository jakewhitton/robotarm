#include <SDL2/SDL.h>
#include <cmath>
#include <cstdio>

const float pi = 3.1415926;

struct Vec {
	float x;
	float y;
};

struct Line {
	Vec start;
	Vec end;
};


const int length1 = 300;
const int length2 = 400;

const int margin = 50;

const int SCREEN_WIDTH = 2 * (length1 + length2 + margin);
const int SCREEN_HEIGHT = (2 * margin) + (length1 + length2);

float a = pi / 3;
float b = -pi / 6;

float aVel = 5.0000;
float bVel = 5.0000;

Line calculateLine(float theta, float length, Vec startPoint) {
	Line returnValue = Line{startPoint, Vec{startPoint.x + (length * cos(theta)), startPoint.y + (length * sin(theta))}};
	printf("Calculating line resulted in (%f, %f) to (%f, %f)\n",returnValue.start.x, returnValue.start.y, returnValue.end.x, returnValue.end.y);
	return returnValue;
}

void drawLine(const Line& line, SDL_Renderer* render) {
	SDL_RenderDrawLine(render, rint(line.start.x), SCREEN_HEIGHT - rint(line.start.y), rint(line.end.x), SCREEN_HEIGHT - rint(line.end.y) );
}

Line line1 = calculateLine(a, length1, Vec{SCREEN_WIDTH / 2, margin});
Line line2 = calculateLine(b, length2, line1.end);


//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

bool init()
{
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

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	
	printf("The window dimensions are %dx%d\n", SCREEN_WIDTH, SCREEN_HEIGHT);

	if( !init() ) {
		printf( "Failed to initialize!\n" );
	} else {
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;
			
		int ticks = 0;

		//While application is running
		while( !quit ){
			//

			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}

			//Clear screen
			SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderClear( renderer );
			
			//User rendering
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			drawLine(line1, renderer);
			drawLine(line2, renderer);
			
			//Update screen
			SDL_RenderPresent( renderer );
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
