#pragma once
#ifndef init_hpp
#define init_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<bits/stdc++.h>
#include "draw.hpp"
#include "stage.hpp"
#include "text.hpp"
#include "HighScore.hpp"
#include "instruction.hpp"
#include"credit.hpp"
using namespace std;

void initSDL(void)
{
	int rendererFlags, windowFlags;
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	rendererFlags = SDL_RENDERER_ACCELERATED;

	SDL_ShowCursor(0);

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
	{
		cout<<"Couldn't initialize SDL: "<<SDL_GetError()<<endl;
		exit(1);
	}
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		exit(1);
	}

	app.window = SDL_CreateWindow("Falcon 6T : Knight", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!app.window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer)
	{
		cout<<"Failed to create renderer: "<<SDL_GetError()<<endl;
		exit(1);
	}
}

void initGame(void)
{
	initBackground();

	initStarfield();
	
	init_instruction();
	//initSounds();
	init_credit();
	initfont();

	initHighscoreTable();

	// loadMusic("music/Mercury.ogg");

	// playMusic(1);
}

#endif
