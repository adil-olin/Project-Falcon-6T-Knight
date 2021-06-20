#pragma once
#ifndef HighScore_hpp
#define HighScore_hpp

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>
#include "defs.hpp"
#include "structure.hpp"
#include "draw.hpp"
#include "stage.hpp"
#include "Intro.hpp"
using namespace std;

Highscores highscores;
Highscore* newHighscore ;
int cursorBlink,_timer=FPS*3;

static void doBackground(void);
static void doStarfield(void);
void initstage(void);

static void drawHighscores(void)
{
	int i, y, r, g, b;

	y = 150;

	drawText(SCREEN_WIDTH/2 -200, 70, 255, 255, 255, "HIGHSCORES");

	for (i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		r = 255;
		g = 255;
		b = 255;

		if (highscores.highscore[i].recent)
		{
			b = 0;
		}

		drawText(200, y, r, g, b, "#%d.%-15s ...... %03d", (i + 1), highscores.highscore[i].name, highscores.highscore[i].score);

		y += 50;
	}

	drawText(255, 600, 255, 255, 255, "PRESS SPACE TO PLAY!");
}

static void drawNameInput(void)
{
	SDL_Rect r;

	drawText(10 , 70, 255, 255, 255, "CONGRATULATIONS, YOU'VE GAINED A HIGHSCORE!");

	drawText(200 , 130, 255, 255, 255, "ENTER YOUR NAME BELOW:");

	drawText(200 , 250, 128, 255, 128, newHighscore->name);

	if (cursorBlink < FPS / 2)
	{
		r.x = (200 + (strlen(newHighscore->name) * GLYPH_WIDTH) / 2) + 5;
		r.y = 250;
		r.w = GLYPH_WIDTH-70;
		r.h = GLYPH_HEIGHT-60;

		SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(app.renderer, &r);
	}

	drawText(150 , 625, 255, 255, 255, "PRESS RETURN WHEN FINISHED");
}

static void doNameInput(void)
{
	int i, n;
	char c;

	n = strlen(newHighscore->name);
	int sz=strlen(app.inputText);

	for (i = 0 ; i < sz ; i++)
	{
		c=app.inputText[i];
		if (n < MAX_SCORE_NAME_LENGTH - 1 && (c==' ' || (c>='a' && c<='z') || (c>='A' && c<='Z')))
		{
			c = toupper(app.inputText[i]);
			newHighscore->name[n] = c;
			n++;
			//cout<<"DHUKSI "<<c<<" "<<n<<endl;
		}
	}

	if (n > 0 && app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		newHighscore->name[--n] = '\0';

		app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
	}

	if (app.keyboard[SDL_SCANCODE_RETURN])
	{
		if (strlen(newHighscore->name) == 0)
		{
			STRNCPY(newHighscore->name, "ANONYMOUS", MAX_SCORE_NAME_LENGTH);
		}

		newHighscore = NULL;
	}
	//cout<<newHighscore->name<<" "<<n<<" "<<app.inputText<<endl;
}

static int highscoreComparator(const void *a, const void *b)
{
	Highscore *h1 = ((Highscore*)a);
	Highscore *h2 = ((Highscore*)b);

	return h2->score - h1->score;
}

void addHighscore(int score)
{
	
	Highscore newHighscores[NUM_HIGHSCORES + 1];

	for (int i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		newHighscores[i] = highscores.highscore[i];
		newHighscores[i].recent = 0;
	}

	newHighscores[NUM_HIGHSCORES].score = score;
	newHighscores[NUM_HIGHSCORES].recent = 1;

	qsort(newHighscores, NUM_HIGHSCORES + 1, sizeof(Highscore), highscoreComparator);

	newHighscore = NULL;

	for (int i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		highscores.highscore[i] = newHighscores[i];

		if (highscores.highscore[i].recent)
		{
			newHighscore = &highscores.highscore[i];
		}
	}
}

static void hlogic(void)
{
	freopen("HighScores.text","w",stdout);
	doBackground();

	doStarfield();

	if (newHighscore != NULL)
	{
		doNameInput();
	}
	else
	{
		if (app.keyboard[SDL_SCANCODE_SPACE] || --_timer<=0)
		{
			for(int i=0;i<NUM_HIGHSCORES;i++)
			{
				cout<<highscores.highscore[i].name<<" "<<highscores.highscore[i].score<<endl;
			}
			intro();
			//initstage();
		}
	}

	if (++cursorBlink >= FPS)
	{
		cursorBlink = 0;
	}
}

static void hdraw(void)
{
	drawBackground();

	drawStarfield();

	if (newHighscore != NULL)
	{
		drawNameInput();
	}
	else
	{
		drawHighscores();
	}
}

void initHighscores(void)
{
	app.delegate.logic = hlogic;
	app.delegate.draw = hdraw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}

void initHighscoreTable(void)
{
	freopen("HighScores.text","r",stdin);

	memset(&highscores, 0, sizeof(Highscores));

	char s[20];
	int sc;

	for (int i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		
		if(scanf("%s%d",s,&sc)==EOF)
		{
			STRNCPY(highscores.highscore[i].name, "ANONYMOUS", MAX_SCORE_NAME_LENGTH);
			highscores.highscore[i].score = 0;
		}
		else
		{
			STRNCPY(highscores.highscore[i].name, s , MAX_SCORE_NAME_LENGTH);
			highscores.highscore[i].score = sc;
		}
	}

	newHighscore = NULL;

	cursorBlink = 0;
}

#endif