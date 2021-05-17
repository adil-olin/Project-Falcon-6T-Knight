#pragma once
#ifndef structure_hpp
#define structure_hpp 
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include <bits/stdc++.h>
using namespace std;

struct App
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	int keyboard[MAX_KEYBOARD_KEYS];
}app;

struct Entity
{
	int x;
	int y;
    int dx,dy,health,reload,w,h;
	int side;
	SDL_Texture *texture;
} player;
vector<Entity>bullet,enemy,destroyed_enemy;

int enemyspawntimer;

struct Explosion 
{
	float x;
	float y;
	float dx;
	float dy;
	int r, g, b, a;
};
vector<Explosion>explosion;

struct Debris {
	float x;
	float y;
	float dx;
	float dy;
	SDL_Rect rect;
	SDL_Texture *texture;
	int life;
};
vector<Debris> debris;

struct Star
{
	int x;
	int y;
	int speed;
};

#endif
