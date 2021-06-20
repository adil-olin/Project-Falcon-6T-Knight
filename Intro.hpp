#pragma once
#ifndef Intro_hpp
#define Intro_hpp

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>
#include "structure.hpp"
#include "defs.hpp"
#include "stage.hpp"
#include "draw.hpp"

using namespace std;

void initstage(void);

void init_intro(void)
{
    load0 = loadTexture("Media/load0.jpg");
    load1 = loadTexture("Media/load1.jpg");
    load2 = loadTexture("Media/load2.jpg");
    title0 = loadTexture("Media/title0.jpg");
    title1 = loadTexture("Media/title1.jpg");
    title2 = loadTexture("Media/title2.jpg");
    blit(load0,0,0);
	SDL_Delay(500);
    blit(load1,0,0);
	SDL_Delay(500);
	blit(load2,0,0);
	SDL_Delay(500);
}

void ilogic(void)
{
    for(int i=0;i<MAX_KEYBOARD_KEYS;i++)
    {
        if(app.keyboard[i]==1)
        {
            initstage();
        }
    }
}

void idraw(void)
{
	SDL_Rect dest;

	dest.x = 0;
    dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;

    SDL_RenderCopy(app.renderer, title0, NULL, &dest);
    SDL_RenderCopy(app.renderer, title1, NULL, &dest);
    SDL_RenderCopy(app.renderer, title2, NULL, &dest);
}

void intro(void)
{
    app.delegate.logic=ilogic;
    app.delegate.draw=idraw;
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}

#endif