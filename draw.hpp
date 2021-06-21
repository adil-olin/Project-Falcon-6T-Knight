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
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
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
		//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
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
			rect.y = 18;
			if(c=='A')
			{
				rect.x = (c - 'A') * GLYPH_WIDTH+19;
				blitFont(fontTexture, &rect, x, y,45,50);

				x += GLYPH_WIDTH-107;

			}
			else if(c=='B')
			{
				rect.x = (c - 'A') * GLYPH_WIDTH+20;
				blitFont(fontTexture, &rect, x, y,45,50);

				x += GLYPH_WIDTH-108;

			}
			else if(c=='E')
			{
				rect.x = (c - 'A') * GLYPH_WIDTH+18;
				blitFont(fontTexture, &rect, x, y,45,50);

				x += GLYPH_WIDTH-112;

			}
			else if(c=='F')
			{
				rect.x = (c - 'A') * GLYPH_WIDTH+9;
				blitFont(fontTexture, &rect, x, y,40,50);
				x += GLYPH_WIDTH-112;
			}
			
			else if(c=='H')
			{
				rect.x = (c - 'A') * GLYPH_WIDTH+3;
				blitFont(fontTexture, &rect, x, y,40,50);

				x += GLYPH_WIDTH-108;

			}
			else if(c=='I')
			{
				rect.x = (c - 'A') * GLYPH_WIDTH+29;
				blitFont(fontTexture, &rect, x, y,40,50);

				x += GLYPH_WIDTH-122;

			} 
			else
			{
				rect.x = (c - 'A') * GLYPH_WIDTH+5;
				blitFont(fontTexture, &rect, x, y,40,50);
				x += GLYPH_WIDTH-108;
			}
		}
		else if (c >= 'J' && c <= 'R')
		{
			rect.y = GLYPH_HEIGHT;
			if(c=='L')
			{
				rect.x = (c - 'J') * GLYPH_WIDTH+19;
				rect.w = GLYPH_WIDTH-10;
				blitFont(fontTexture, &rect, x, y,40,50);
				rect.w = GLYPH_WIDTH;
				x += GLYPH_WIDTH-113;
			}
			else if(c=='M')
			{
				rect.x = (c - 'J') * GLYPH_WIDTH-9;
				blitFont(fontTexture, &rect, x, y,40,50);

				x += GLYPH_WIDTH-98;
			}
			
			else if(c=='N')
			{
				rect.x = (c - 'J') * GLYPH_WIDTH-3;
				blitFont(fontTexture, &rect, x, y,40,50);
				x += GLYPH_WIDTH-105;
			}
			else
			{
				rect.x = (c - 'J') * GLYPH_WIDTH+9;
				blitFont(fontTexture, &rect, x, y,40,50);

				x += GLYPH_WIDTH-111;
			}
		}
		
		else if (c >= 'S' && c <= 'Z' || c==' ')
		{
			rect.y = GLYPH_HEIGHT*2-18;
			 if (c == 'S')
			{
				rect.x = (c - 'S') * GLYPH_WIDTH+19;
				blitFont(fontTexture, &rect, x, y,40,50);

				x += GLYPH_WIDTH-111;
			}
			else if (c == 'T')
			{
				rect.x = (c - 'S') * GLYPH_WIDTH+10;
				blitFont(fontTexture, &rect, x, y,40,50);

				x += GLYPH_WIDTH-110;
			}
			
			else if (c == 'U')
			{
				rect.x = (c - 'S') * GLYPH_WIDTH+3;
				blitFont(fontTexture, &rect, x, y,40,50);
				x += GLYPH_WIDTH-106;
			}
			else if (c == ' ')
			{
				rect.x = 1130;
				blitFont(fontTexture, &rect, x, y,40,50);
				x += 20;
			}
			else if (c == 'W')
			{	
				rect.x = (c - 'S') * GLYPH_WIDTH;
				blitFont(fontTexture, &rect, x, y,45,50);
				x += GLYPH_WIDTH-99;

			}
			else 
			{	
				rect.x = (c - 'S') * GLYPH_WIDTH+3;
				blitFont(fontTexture, &rect, x, y,40,50);
				x += GLYPH_WIDTH-109;

			}
		}
		else if (c == ':')
		{
			rect.x = 183;
			rect.y = 2088;
			blitFont(fontTexture, &rect, x, y,40,68);
			x += 20;
		}
		else if (c == '.')
		{
			rect.x = 1000;
			rect.y = 2088;
			blitFont(fontTexture, &rect, x, y,40,68);
			x += 20;
		}
		else if (c == '#')
		{
			rect.x = 300;
			rect.y = 1830;
			blitFont(fontTexture, &rect, x, y,40,68);
			x += 35;
		}
		else if (c == '0')
		{
			rect.x = 1125;
			rect.y = 1155;
			rect.h = GLYPH_HEIGHT-5;
			blitFont(fontTexture, &rect, x, y,40,52);
			rect.h = GLYPH_HEIGHT;
			x += 30;
		}
		else if (c >= '1'&&c<='9')
		{
			rect.x = GLYPH_WIDTH*(c-'1')+15;
			rect.y = 1375;
			rect.h = GLYPH_HEIGHT-5;
			blitFont(fontTexture, &rect, x, y,40,52);
			rect.h = GLYPH_HEIGHT;
			x += 30;
		}
		else if (c == 39)
		{

			rect.h = GLYPH_HEIGHT;
			rect.w = 40;
			rect.x = 455;
			rect.y = 2080;
			blitFont(fontTexture, &rect, x, y,10,68);

			rect.w = GLYPH_WIDTH;
			rect.h = GLYPH_HEIGHT;
			x += 5;
		}
		 
		
		
		
	}
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

void drawintro(SDL_Texture* introtext)
{
	SDL_RenderCopy(app.renderer,introtext,NULL,NULL);
	SDL_DestroyTexture(introtext);
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
