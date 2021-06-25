#pragma once
#ifndef defs_hpp
#define defs_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>
using namespace std; 

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720
#define PLAYER_SPEED          4
#define PLAYER_BULLET_SPEED   16
#define MAX_LINE_LENGTH 1024

#define MAX_KEYBOARD_KEYS 350
#define MAX_MOUSE_BUTTON 2
#define MOUSELEFT 0
#define MOUSERIGHT 1
#define SIDE_PLAYER 0
#define SIDE_ALIEN  1
#define Health_Pod  2
#define Life_Pod    3
#define Ult_Pod		4
#define FPS 60

#define ALIEN_BULLET_SPEED    6
#define MAX_STARS   500

#define NUM_HIGHSCORES 8

#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'

#define MAX_NAME_LENGTH 32
#define MAX_SCORE_NAME_LENGTH 12
enum
{
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};

#endif

