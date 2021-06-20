#pragma once
#ifndef draw_hpp
#define draw_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<bits/stdc++.h>
#include "text.hpp"
using namespace std;
void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 0, 100, 100, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

static void addTextureToCache(char *Name, SDL_Texture *sdlTexture)
{
	Texture temp;

	STRNCPY(temp.name, Name, MAX_NAME_LENGTH);
	temp.texture = sdlTexture;
	app.AllTexture.push_back(temp);
}

static SDL_Texture *getTexture(char *Name)
{
	Texture t;
	for(auto temp : app.AllTexture)
	{
		if (strcmp(temp.name, Name) == 0)
		{
			return temp.texture;
		}
	}

	return NULL;
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	texture = getTexture(filename);

	if (texture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
		SDL_Surface* surface = NULL;
		surface = IMG_Load(filename);
		SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0x00,0x00,0x00));
		texture = SDL_CreateTextureFromSurface(app.renderer,surface);
		// texture = IMG_LoadTexture(app.renderer, filename);
		SDL_FreeSurface(surface);
		surface = NULL;
		
		addTextureToCache(filename, texture);
	}

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
	dest.w = 50;
	dest.h = 50;

	SDL_RenderCopy(app.renderer, texture, src, &dest);
}
void blitFont(SDL_Texture *texture, SDL_Rect *src, int x, int y, int w, int h)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

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


void drawText(float x, float y, int r, int g, int b,char *format, ...)
{
	int i, len, c;
	SDL_Rect rect;
	va_list args;
	char drawTextBuffer[205];

	memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

	va_start(args, format);
	vsprintf(drawTextBuffer, format, args);
	
	va_end(args);

	len = strlen(drawTextBuffer);

	rect.w = GLYPH_WIDTH;
	rect.h = GLYPH_HEIGHT;
	

	SDL_SetTextureColorMod(fontTexture, r, g, b);
	for (i = 0 ; i < len ; i++)
	{
		c = drawTextBuffer[i];
		if (c >= 'A' && c <= 'I')
		{
			rect.x = (c - 'A') * GLYPH_WIDTH;
			rect.y = 0;
			blitFont(fontTexture, &rect, x, y,50,50);

			x += GLYPH_WIDTH-53;
		}
		else if (c >= 'J' && c <= 'R')
		{
			rect.x = (c - 'J') * GLYPH_WIDTH;
			rect.y = GLYPH_HEIGHT;
			blitFont(fontTexture, &rect, x, y,50,50);

			x += GLYPH_WIDTH-53;
		}
		else if (c == ':')
		{
			rect.x =730;
			rect.y = 190;
			blitFont(fontTexture, &rect, x, y,50,50);

			x += GLYPH_WIDTH-53;
		}
		else if (c == '9')
		{
			rect.x =10;
			rect.y = 747;
			blitFont(fontTexture, &rect, x, y,50,87);

			x += GLYPH_WIDTH-53;
		}
		else if (c == ' ')
		{
			rect.x =725;
			rect.y = 850;
			blitFont(fontTexture, &rect, x, y,50,10);

			x += GLYPH_WIDTH-80;
		}
		else if (c >= 'S' && c <= 'Z')
		{
			rect.x = (c - 'S') * GLYPH_WIDTH;
			rect.y = GLYPH_HEIGHT*2-5;
			blitFont(fontTexture, &rect, x, y,50,50);

			x += GLYPH_WIDTH-53;
		}
		else if (c >= '0' && c <= '8')
		{
			int h = y-10;
			rect.x = (c - '0') * GLYPH_WIDTH;
			rect.y = 620-25;
			blitFont(fontTexture, &rect, x, h,50,50);

			x += GLYPH_WIDTH-55;
			
		}
		else if(c=='#')
		{
			int h = y-10;
			rect.x = 545;
			rect.y = 725;
			blitFont(fontTexture, &rect, x, y,50,50);

			x += GLYPH_WIDTH-55;
		}
		else if(c=='.')
		{
			int h = y-10;
			rect.x = 95;
			rect.y = 710;
			blitFont(fontTexture, &rect, x, y+10,50,50);

			x += GLYPH_WIDTH-55;
		}
		
	}
}

void drawintro(SDL_Texture* introtext)
{
	SDL_RenderCopy(app.renderer,introtext,NULL,NULL);
	SDL_DestroyTexture(introtext);
}

static void drawHud(void)
{
	drawText(10, 10, 255, 255, 255,"SCORE: %03d", stage.score);
}

static void drawHealth()
{
	float x,y;
	y=5;
	x=SCREEN_WIDTH/2 - (player.life/2)*60; //here 60 is the height of life image
	for(int i=1;i<=player.life;i++)
	{
		blit(Life, x, y);
		x+=60;
	}
	blit(healthbar,10,60);
	x=10+47;
	for(int i=1;i<=player.health;i+=10)
	{
		blit(healthstat,x,60+19);
		x+=15;
		if(x>=150)
		{
			x=150;
			blit(healthstat,x,60+19);
			break;
		}
	}
}

static void drawPod(void)
{
	for(auto tmp : stage.pointpod)
	{
		blit(tmp.texture,tmp.x,tmp.y);
	}
}


static void draw(void)
{

	drawBackground();

	drawStarfield();

	drawFighter();

	drawBullet();

	drawPod();

	drawDebris();

	drawExplosions();

	drawHealth();

	drawHud();
}

#endif
