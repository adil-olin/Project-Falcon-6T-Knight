#pragma once
#ifndef text_hpp
#define text_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>
#include "structure.hpp"
#include "draw.hpp"
using namespace std;

SDL_Texture *loadTexture(char *filename);

float GLYPH_WIDTH;
float GLYPH_HEIGHT;
void initfont()
{
      fontTexture = loadTexture("font/TNR.jpg");
      SDL_Surface* surface = IMG_Load("font/TNR.jpg");
      GLYPH_HEIGHT = surface->h/10;
      GLYPH_WIDTH = surface->w/9;
      SDL_FreeSurface(surface);
}


#endif