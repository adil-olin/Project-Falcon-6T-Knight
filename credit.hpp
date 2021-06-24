#pragma once
#ifndef credit_hpp
#define credit_hpp

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>
#include "structure.hpp"
#include "defs.hpp"
#include "stage.hpp"
#include "Intro.hpp"
#include "draw.hpp"
#include "HighScore.hpp"

using namespace std;

void homepage(void);

void creditlogic(void)
{
    //mainmenu
    if(app.keyboard[SDL_SCANCODE_ESCAPE])
    {
        homepage();
    }
    
}
void creditdraw(void)
{
    blit(crdt,0,0);
}

void init_credit(void)
{
    crdt = loadTexture("Media/credit.jpg");
}
void Credit(void)
{
    app.delegate.logic = creditlogic;
    app.delegate.draw = creditdraw;
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
    memset(app.mouse, 0, sizeof(int) * 360);
}

#endif