#pragma once
#ifndef text_hpp
#define text_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>
using namespace std;

int GLYPH_WIDTH;
int GLYPH_HEIGHT;
void initfont()
{
      SDL_Surface* surface = IMG_Load("font/font.png");
      GLYPH_HEIGHT = surface->h/9;
      GLYPH_WIDTH = surface->w/9;
      SDL_FreeSurface(surface);

}


#endif