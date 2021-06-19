#pragma once
#ifndef Highscore_hpp
#define Highscore_hpp

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>
#include "structure.hpp"
#include "draw.hpp"
using namespace std;

Highscores highscores;

static int highscoreComparator(const void *a, const void *b)
{
	Highscore *h1 = ((Highscore*)a);
	Highscore *h2 = ((Highscore*)b);

	return h2->score - h1->score;
}

void initHighscoreTable(void)
{

	memset(&highscores, 0, sizeof(Highscores));

	for (int i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		highscores.highscore[i].score = NUM_HIGHSCORES - i;
	}
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

	for (int i = 0 ; i < NUM_HIGHSCORES ; i++)
	{
		highscores.highscore[i] = newHighscores[i];
	}
}

static void draw(void)
{
	drawBackground();

	drawStarfield();

	drawHighscores();
}

static void logic(void)
{
	doBackground();

	doStarfield();

	if (app.keyboard[SDL_SCANCODE_LCTRL])
	{
		initStage();
	}
}

void initHighscores(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}



#endif 