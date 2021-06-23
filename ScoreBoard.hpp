#pragma once
#ifndef ScoreBoard_hpp
#define ScoreBoard_hpp

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<bits/stdc++.h>
#include "defs.hpp"
#include "structure.hpp"
#include "draw.hpp"
#include "stage.hpp"
#include "HighScore.hpp"
using namespace std;

static void drawHighscoresIn(void)
{
	drawBackground();
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

static void SCdraw(void)
{
	drawBackground();
	drawStarfield();
	drawHighscoresIn();

}

#endif