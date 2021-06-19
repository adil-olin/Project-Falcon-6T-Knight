#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>
#include "defs.hpp"
#include "structure.hpp"
#include "init.hpp"
#include "Input.hpp"
#include "draw.hpp"
#include "movement.hpp"
#include "stage.hpp"
#include "Util.hpp"
#include "text.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	long then;
	float remainder;

    memset(&app, 0, sizeof(App));

	initSDL();

	initstage();

	initGame();

	initHighscores();

	then = SDL_GetTicks();

	remainder = 0;

	while (1)
	{
		prepareScene();
		
		doInput();

		app.delegate.logic();

		app.delegate.draw();

		presentScene();

		capFrameRate(&then, &remainder);

	}
    return 0;
}
