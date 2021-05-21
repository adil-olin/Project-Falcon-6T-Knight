#pragma once
#ifndef structure_hpp
#define structure_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<bits/stdc++.h>
using namespace std;

struct Delegate
{
	void (*logic)(void);
	void (*draw)(void);
};


struct App
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
}app;

struct Entity
{
	float x;
	float y;
    int health,reload,w,h;
	float dx,dy;
	int side;
	SDL_Texture *texture;

	bool operator == (const Entity &p)
	{
		return (p.x==x && p.y==y && p.dx==dx && p.dy==dy && p.health==health && p.reload==reload && p.w==w && p.h==h && p.side==side &&p.texture==texture);
	}
	bool operator !=(const Entity &p)
	{
		return !(p.x==x && p.y==y && p.dx==dx && p.dy==dy && p.health==health && p.reload==reload && p.w==w && p.h==h && p.side==side && p.texture==texture);
	}

} player; 

struct Explosion 
{
	float x;
	float y;
	float dx;
	float dy;
	int r, g, b, a;
};

struct Debris 
{
	float x;
	float y;
	float dx;
	float dy;
	SDL_Rect rect;
	SDL_Texture *texture;
	int life;
};

struct Star
{
	int x;
	int y;
	int speed;
} stars[MAX_STARS];

struct Stage
{
	//bullet will contain all type of bullet from enemy or ally
	//Fighter will do same for enemy and the player. Here player will act as reference

	vector<Entity> Bullet,Fighter;
	vector<Explosion> explosion;
	vector<Debris> debris;

} stage;

bool isplayernull = false;
int enemyspawntimer,stageResetTimer,backgroundY;

SDL_Texture *alienBulletTexture;
SDL_Texture *playerTexture;
SDL_Texture *bulletTexture;
SDL_Texture *enemyTexture;
SDL_Texture *explosionTexture;
SDL_Texture *background;

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
