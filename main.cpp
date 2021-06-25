#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<bits/stdc++.h>
#include "init.hpp"
#include "defs.hpp"
#include "structure.hpp"
#include "stage.hpp"
#include "Input.hpp"
#include "draw.hpp"
#include "movement.hpp"
#include "Util.hpp"
#include "text.hpp"
#include "Intro.hpp"
#include "instruction.hpp"
#include "credit.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	long then;
	float remainder;
	isstarted=false;
   	memset(&app, 0, sizeof(App));

	initSDL();

    initGame();

	init_intro();

	intro();

	then = SDL_GetTicks();

	remainder = 0;

	while (1)
	{
		
		doInput();

		app.delegate.logic();
		
		app.delegate.draw();
        
		presentScene();

		capFrameRate(&then, &remainder);
	}
    return 0;
}
