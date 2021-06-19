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
	SDL_Delay(6000);
	SDL_RenderClear(app.renderer);
	
}

#endif
