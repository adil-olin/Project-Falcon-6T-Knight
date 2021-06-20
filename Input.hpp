#pragma once
#ifndef Input_hpp
#define Input_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<bits/stdc++.h>
#include<SDL2/SDL_ttf.h>
#include "structure.hpp"
using namespace std;

void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}
}

void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}
}

void doInput(void)
{
	SDL_Event event;
	memset(app.inputText, '\0', MAX_LINE_LENGTH);
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;
			
			case SDL_TEXTINPUT:
				STRNCPY(app.inputText, event.text.text, MAX_LINE_LENGTH);
				break;

			default:
				break;
		}
	}
}

#endif
