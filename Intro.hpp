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
#include "HighScore.hpp"
#include "instruction.hpp"
#include "credit.hpp"


using namespace std;

void initstage(void);
void initHighscores(void);
void credit(void);

void init_intro(void)
{
	point = loadTexture("Media/select.jpg");
	logo = IMG_LoadTexture(app.renderer,"Media/lg1.png");
	home = loadTexture("Media/home1.jpg");
    load0 = loadTexture("Media/load0.jpg");
    load1 = loadTexture("Media/load1.jpg");
    load2 = loadTexture("Media/load2.jpg");
    title0 = loadTexture("Media/title0.jpg");
    title1 = loadTexture("Media/title1.jpg");
    title2 = loadTexture("Media/title2.jpg");
}
void Select(int x,int y, int z)
{

		Uint8 a = 100;
	 	SDL_Rect d = {x,y,z,40};
		SDL_SetTextureAlphaMod(point,a);
		SDL_RenderCopy(app.renderer,point,NULL,&d);

}

void homelogic(void)
{
	//cout <<MouseX<<" "<<MouseY<<endl;
	if(MouseX>=149 && MouseX<=385 && MouseY >=262 && MouseY<=295)
	{
	//	cout <<MouseX<<" "<<MouseY<<endl;
		if(app.mouse[0]==1)
		{	
			isstarted=false;
			boss_timer = 60*FPS;
			initstage();
		}
	}

	//continue
	else if(MouseX>=160 && MouseX<=380 && MouseY >=314 && MouseY<=343)
	{
		if(app.mouse[0]==1 && isstarted)
		{	continue_timer=FPS*3;
			initstage();
		}
	}

	//ScoreBoard
	else if(MouseX>=156 && MouseX<=390 && MouseY >=365 && MouseY<=395)
	{
		if(app.mouse[0]==1)
		{
			initHighscores();
		}
	}
	//instruction
	else if(MouseX>=140 && MouseX<=390 && MouseY >=410 && MouseY<=450)
	{
		if(app.mouse[0]==1)
		{
			Instruction();
		}
	}
	//Credit
	else if(MouseX>=180 && MouseX<=350 && MouseY >=464 && MouseY<=498)
	{
		if(app.mouse[0]==1)
		{
			Credit();
		}
	}
	//Quit
	else if(MouseX>=195 && MouseX<=320 && MouseY >=516 && MouseY<=556)
	{
		if(app.mouse[0]==1)
		{
			exit(0);
		}
	}

}

void homedraw(void)
{

	SDL_RenderCopy(app.renderer,home,NULL, NULL);
	if(MouseX>=149 && MouseX<=385 && MouseY >=262 && MouseY<=295)
	{
		Select(143,258,250);
	}

	//continue
	else if(MouseX>=160 && MouseX<=380 && MouseY >=314 && MouseY<=343)
	{
		if(isstarted==true)
		{
			Select(154,310,225);
		}
	}

	//ScoreBoard
	else if(MouseX>=156 && MouseX<=390 && MouseY >=365 && MouseY<=395)
	{
		Select(150,361,240);
	}
	//instruction
	else if(MouseX>=140 && MouseX<=390 && MouseY >=410 && MouseY<=450)
	{
		Select(134,410,265);
	}
	//Credit
	else if(MouseX>=180 && MouseX<=350 && MouseY >=464 && MouseY<=498)
	{
		Select(175,460,170);
	}
	//Quit
	else if(MouseX>=195 && MouseX<=320 && MouseY >=516 && MouseY<=556)
	{
		Select(189,514,128);
	}
}
void homepage(void)
{
	app.delegate.logic=homelogic;
    app.delegate.draw=homedraw;
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	memset(app.mouse, 0, sizeof(int) * 360);

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
	memset(app.mouse, 0, sizeof(int) * 360);
}

static void intro()
{
	 prepareScene();
	drawintro(load0);
	presentScene();
	SDL_Delay(500);
	SDL_RenderClear(app.renderer);
	drawintro(load1);
	presentScene();
	SDL_Delay(500);
	SDL_RenderClear(app.renderer);
	drawintro(load2);
	presentScene();
	SDL_Delay(500);
	SDL_RenderClear(app.renderer);
	drawintro(title0);
	presentScene();
	SDL_Delay(200);
	//..............
	for(int i = 0; i <= 255;i++)
	{
		Uint8 a = i;
		SDL_Rect s = {0,0,1240,740};
		SDL_Rect d = {447,376,413,315};
		SDL_SetTextureAlphaMod(logo,a);
		SDL_RenderCopy(app.renderer,logo,&s,&d);
		presentScene();
		SDL_Delay(9);
	}
	//.................
	drawintro(title1);
	presentScene();
	SDL_Delay(200);
	SDL_RenderClear(app.renderer);
	drawintro(title2);
	presentScene();
	MainIntro();

}


#endif