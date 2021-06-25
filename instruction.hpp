#pragma once
#ifndef instruction_hpp
#define instruction_hpp

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<bits/stdc++.h>
#include "structure.hpp"
#include "defs.hpp"
#include "stage.hpp"
#include "Intro.hpp"
#include "draw.hpp"
#include "HighScore.hpp"

using namespace std;

void homepage(void);
void initstage(void);
void Select(int x,int y,int z);

void instlogic(void)
{
    //cout<<MouseX<<" "<<MouseY<<endl;
    //play
    if(MouseX>=1071 && MouseX<=1248 && MouseY >=328 && MouseY<=376)
    {
            if(app.mouse[0]==1)
            {
                boss_timer = 60*FPS;
			    initstage();
            }
    }
    //mainmenu
    else if(MouseX>=1075 && MouseX<=1253&& MouseY >=428 && MouseY<=476)
	{
		if(app.mouse[0]==1)
		{
            SDL_RenderClear(app.renderer);
			homepage();
		}
	}
    
}
void instdraw(void)
{
    SDL_RenderCopy(app.renderer,instruction,NULL, NULL);
    //play
    if(MouseX>=1071 && MouseX<=1248 && MouseY >=328 && MouseY<=376)
    {
        Select(1071,328,178);
    }
    //main menu
    else if(MouseX>=1075 && MouseX<=1253 && MouseY >=428 && MouseY<=476)
	{
		Select(1075,428,178);
	}
}

void init_instruction(void)
{
    instruction = loadTexture("Media/instruction.jpg");
}
void Instruction(void)
{
    app.delegate.logic = instlogic;
    app.delegate.draw = instdraw;
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
	memset(app.mouse, 0, sizeof(int) * 360);
}

#endif
