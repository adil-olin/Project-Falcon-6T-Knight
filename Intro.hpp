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
	logo = loadTexture("Media/lg1.jpg");
	home = loadTexture("Media/home.jpg");
    load0 = loadTexture("Media/load0.jpg");
    load1 = loadTexture("Media/load1.jpg");
    load2 = loadTexture("Media/load2.jpg");
    title0 = loadTexture("Media/title0.jpg");
    title1 = loadTexture("Media/title1.jpg");
    title2 = loadTexture("Media/title2.jpg");
}

void homelogic(void)
{

	if(MouseX>=400 && MouseX<=855 && MouseY >=117 && MouseY<=220)
	{
		if(app.mouse[0]==1)
		{
			boss_timer = 60*FPS;
			initstage();
		}
	}
}

void homedraw(void)
{
	SDL_RenderCopy(app.renderer,home,NULL, NULL);
}
void homepage(void)
{
	app.delegate.logic=homelogic;
    app.delegate.draw=homedraw;
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

}

void ilogic(void)
{
    for(int i=0;i<MAX_KEYBOARD_KEYS;i++)
    {
        if(app.keyboard[i]==1)
        {
           homepage();
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


void MainIntro(void)
{
    app.delegate.logic=ilogic;
    app.delegate.draw=idraw;
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}

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
	//..............
	for(int i = 0; i <= 150;i++)
	{
		Uint8 a = i;
		SDL_Rect s = {0,0,1240,740};
		SDL_Rect d = {447,376,413,315};
		SDL_SetTextureAlphaMod(logo,a);
		SDL_RenderCopy(app.renderer,logo,&s,&d);
		presentScene();
		SDL_Delay(30);
	}
	//.................
	drawintro(title1);
	presentScene();
	SDL_Delay(1000);
	SDL_RenderClear(app.renderer);
	drawintro(title2);
	presentScene();
	MainIntro();
	
}


#endif