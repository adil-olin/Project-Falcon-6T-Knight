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
#include "Collision.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	long then;
	float remainder;

    memset(&app, 0, sizeof(App));

	initSDL(); //in init.hpp header file

	initstage(); //in stage.hpp header file 

	then = SDL_GetTicks();

	remainder = 0;

	while (1)
	{
		prepareScene(); //in draw.hpp header file

		doInput(); //in Input.hpp header file 

		movePlayer(); //in movement.hpp header file 

		doenemy(); //in stage.hpp header file 

		doBullet(); //in stage.hpp header file

		spawnenemy(); //in movement.hpp header file 

        draw(); //in draw.hpp header file
        
		presentScene(); //in draw.hpp header file 

		capFrameRate(&then, &remainder); //in stage.hpp header file (used for getting exact 60 fps)
	}
    return 0;
}

