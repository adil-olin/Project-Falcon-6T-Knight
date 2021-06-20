#pragma once

#ifndef Intro_hpp
#define Intro_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<bits/stdc++.h>
#include"structure.hpp"
#include"stage.hpp"
#include"draw.hpp"
using namespace std;

static void intro()
{
	prepareScene();
	drawintro(load0);
	presentScene();
	SDL_Delay(1000);
	SDL_RenderClear(app.renderer);
	drawintro(load1);
	presentScene();
	SDL_Delay(1000);
	SDL_RenderClear(app.renderer);
	drawintro(load2);
	presentScene();
	SDL_Delay(1000);
	SDL_RenderClear(app.renderer);
	drawintro(title0);
	presentScene();
	SDL_Delay(1000);
	SDL_RenderClear(app.renderer);
	drawintro(title1);
	presentScene();
	SDL_Delay(1000);
	SDL_RenderClear(app.renderer);
	drawintro(title2);
	presentScene();
	SDL_Delay(2000);
	SDL_RenderClear(app.renderer);
	
}

#endif
