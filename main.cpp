#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<bits/stdc++.h>
#include "defs.hpp"
#include "structure.hpp"
#include "init.hpp"
#include "Input.hpp"
#include "draw.hpp"
#include "movement.hpp"
#include "stage.hpp"
#include "Util.hpp"
#include"Intro.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	long then;
	float remainder;

    memset(&app, 0, sizeof(App));

	initSDL();

	initstage();
	
	then = SDL_GetTicks();

	remainder = 0;
	intro();
	
	while (1)
	{
		prepareScene();

		doInput();
		drawintro(load0);
		drawintro(load1);
		drawintro(load2);
		drawintro(title0);
		drawintro(title1);
		drawintro(title2);

		app.delegate.logic();

		app.delegate.draw();
        
		presentScene();

		capFrameRate(&then, &remainder);
	}
    return 0;
}
