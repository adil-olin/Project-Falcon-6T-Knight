#pragma once
#ifndef draw_hpp
#define draw_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<bits/stdc++.h>
using namespace std;

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	SDL_Surface* surface = NULL;
	surface = IMG_Load(filename);
	SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0x00,0x00,0x00));
	texture = SDL_CreateTextureFromSurface(app.renderer,surface);
	SDL_FreeSurface(surface);
	surface = NULL;
	return texture;
}

void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;

	SDL_RenderCopy(app.renderer, texture, src, &dest);
}

static void drawStarfield(void)
{
	for (int i = 0 ; i < MAX_STARS ; i++)
	{
		int c = 32 * stars[i].speed;

		SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);

		SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
	}
}

static void drawBackground(void)
{
	SDL_Rect dest;

	for (int y = backgroundY ; y < SCREEN_HEIGHT ; y += SCREEN_HEIGHT)
	{
		dest.x = 0;
		dest.y = y;
		dest.w = SCREEN_WIDTH;
		dest.h = SCREEN_HEIGHT;

		SDL_RenderCopy(app.renderer, background, NULL, &dest);
	}
}

static void drawDebris(void)
{
	for(auto temp : stage.debris)
	{
		blitRect(temp.texture,&temp.rect,temp.x,temp.y);
	}
}

static void drawExplosions(void)
{

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
	SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);

	for(auto temp : stage.explosion)
	{
		SDL_SetTextureColorMod(explosionTexture, temp.r, temp.g, temp.b);
		SDL_SetTextureAlphaMod(explosionTexture, temp.a);

		blit(explosionTexture, temp.x, temp.y);
	}

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

void drawBullet(void)
{
	for(auto tmp : stage.Bullet)
	{
		blit(tmp.texture, tmp.x, tmp.y);
	}
}

static void drawFighter(void)
{
	for (auto tmp : stage.Fighter)
	{
		blit(tmp.texture, tmp.x, tmp.y);
	}
}
void drawintro(SDL_Texture *introtext){
	SDL_RenderCopy(app.renderer,introtext,NULL,NULL);
	SDL_DestroyTexture(introtext);
}

static void draw(void)
{
	
	drawBackground();

	drawStarfield();

	drawFighter();

	drawBullet();

	drawDebris();

	drawExplosions();
}

#endif
