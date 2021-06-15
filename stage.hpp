#pragma once

#ifndef Stage_hpp
#define Stage_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<bits/stdc++.h>
#include "Util.hpp"
#include "movement.hpp"
#include "init.hpp"
#include "draw.hpp"
#include "structure.hpp"

using namespace std;

static void initStarfield(void)
{
	for (int i = 0 ; i < MAX_STARS ; i++)
	{
		stars[i].x = rand() % SCREEN_WIDTH;
		stars[i].y = rand() % SCREEN_HEIGHT;
		stars[i].speed = 1 + rand() % 8;
	}
}

void initPlayer(void)
{
    memset(&player,0,sizeof(Entity));

    player.texture = playerTexture;
    player.x = 590;
	player.y = 597;
    player.w=100;
    player.h=123;
    player.side=SIDE_PLAYER;
    player.health=100;
    player.life=3;

    stage.Fighter.push_back(player);
}

static void doBackground(void)
{
	if (++backgroundY >= 0)
	{
		backgroundY = -SCREEN_HEIGHT;
	}
}

static void doStarfield(void)
{
	for (int i = 0 ; i < MAX_STARS ; i++)
	{
		stars[i].y += stars[i].speed;

		if (stars[i].y > SCREEN_HEIGHT)
		{
			stars[i].y = 0 ;
		}
	}
}

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}

static void addDebris(Entity *e)
{
	int w, h;

	w = e->w / 2;
	h = e->h / 2;

	for (int y = 0 ; y <= h ; y += h)
	{
		for (int x = 0 ; x <= w ; x += w)
		{
            Debris temp;
			memset(&temp , 0 , sizeof(Debris));

			temp.x = e->x + e->w / 2;
			temp.y = e->y + e->h / 2;
			temp.dx = (rand() % 5) - (rand() % 5);
			temp.dy = -(5 + (rand() % 12));
			temp.life = FPS * 2;
			temp.texture = e->texture;
			temp.rect.x = x;
			temp.rect.y = y;
			temp.rect.w = w;
			temp.rect.h = h;

            stage.debris.push_back(temp);
		}
	}
}

static void addExplosions(int x, int y, int num)
{
	for (int i = 0 ; i < num ; i++)
	{
        Explosion temp;
		memset(&temp, 0, sizeof(Explosion));

		temp.x = x + (rand() % 32) - (rand() % 32);
		temp.y = y + (rand() % 32) - (rand() % 32);
		temp.dx = 0;
		temp.dy = (rand() % 10) + (rand() % 10);

		temp.dx /= 10;
		temp.dy /= 10;

		switch (rand() % 4)
		{
			case 0:
				temp.r = 255;
				break;

			case 1:
				temp.r = 255;
				temp.g = 128;
				break;

			case 2:
				temp.r = 255;
				temp.g = 255;
				break;

			default:
				temp.r = 255;
				temp.g = 255;
				temp.b = 255;
				break;
		}
		temp.a = rand() % FPS * 3;
        stage.explosion.push_back(temp);
	}
}

static void doExplosions(void)
{
    vector<int>pos;
    for(int i=0;i<stage.explosion.size();i++)
    {
        stage.explosion[i].x += stage.explosion[i].dx;
        stage.explosion[i].y += stage.explosion[i].dy;

        if(--stage.explosion[i].a<=0)
        {
            pos.push_back(i);
        }
    }
    sort(pos.rbegin(),pos.rend());
    for(int i=0;i<pos.size();i++)
    {
        stage.explosion.erase(stage.explosion.begin()+pos[i]);
    }
}

static void doDebris(void)
{
    vector<int>pos;
    for(int i=0;i<stage.debris.size();i++)
    {
        stage.debris[i].x += stage.debris[i].dx;
        stage.debris[i].y += stage.debris[i].dy;
        stage.debris[i].dy += 0.5;

        if(--stage.debris[i].life<=0)
        {
            pos.push_back(i);
        }
    }
    sort(pos.rbegin(),pos.rend());
    for(int i=0;i<pos.size();i++)
    {
        stage.debris.erase(stage.debris.begin()+pos[i]);
    }
}

bool bulletHitfighet(Entity *temp)
{
    
    for(int i=0;i<stage.Fighter.size();i++)
    {
        if (stage.Fighter[i].side != temp->side && collision(temp->x, temp->y, temp->w, temp->h, stage.Fighter[i].x, stage.Fighter[i].y, stage.Fighter[i].w, stage.Fighter[i].h))
        {
            
            if(stage.Fighter[i]==player)
            {
                player.health-=temp->health;
            }
            else
            {
                stage.score++;
            }
            stage.Fighter[i].health -= temp->health;
            temp->health = 0;
           
            

        	highscore = max(stage.score, highscore);
        
            return true;
        }
    }
    return false;
}

void doBullet(void)
{
    vector<int>pos;
    for(int i=0;i<stage.Bullet.size();i++)
    {
        stage.Bullet[i].x += stage.Bullet[i].dx;
		stage.Bullet[i].y += stage.Bullet[i].dy;
        if(stage.Bullet[i].y<-stage.Bullet[i].h || stage.Bullet[i].y>SCREEN_HEIGHT || stage.Bullet[i].x<stage.Bullet[i].w || stage.Bullet[i].x>SCREEN_WIDTH || bulletHitfighet(&stage.Bullet[i]))
        {
            pos.push_back(i);
        }
    }
    sort(pos.rbegin(),pos.rend());
    for(int i=0;i<pos.size();i++)
    {
        stage.Bullet.erase(stage.Bullet.begin()+pos[i]);
    }
}

static void fireAlienBullet(Entity *e)
{
	Entity tmp_bullet;

	memset(&tmp_bullet, 0 , sizeof(Entity));

	tmp_bullet.x = e->x;
	tmp_bullet.y = e->y;
	tmp_bullet.health = 10;
	tmp_bullet.texture = alienBulletTexture;
	tmp_bullet.side = e->side;
	//SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	tmp_bullet.x += (e->w / 2) - (tmp_bullet.w / 2);
	tmp_bullet.y += (e->h / 2) - (tmp_bullet.h / 2);
    tmp_bullet.w=30;
    tmp_bullet.h=53;

	if(!isplayernull)
    {
        calcSlope(player.x + (player.w / 2), player.y + (player.h / 2), e->x, e->y, &tmp_bullet.dx, &tmp_bullet.dy);

        tmp_bullet.dx *= ALIEN_BULLET_SPEED;
        tmp_bullet.dy *= ALIEN_BULLET_SPEED;
    }
    //if player died enemy will shoot straight forward
    else
    {
        tmp_bullet.dx = 0;
        tmp_bullet.dy = ALIEN_BULLET_SPEED;
    }
    
    stage.Bullet.push_back(tmp_bullet);
	e->reload = FPS/2 + (rand()%(FPS)/2);
}

void doEnemy(void)
{
    for(int i=1;i<stage.Fighter.size();i++)
    {
        stage.Fighter[i].reload--;
        if(stage.Fighter[i].reload<=0)
        {
            fireAlienBullet(&stage.Fighter[i]);
        }
    }
}

void doFighter(void)
{
    vector<int>pos;

    for(int i=0;i<stage.Fighter.size();i++)
    {   
        if(stage.Fighter[i]!= player)
        {
            stage.Fighter[i].x += stage.Fighter[i].dx;
		    stage.Fighter[i].y += stage.Fighter[i].dy;

            if(stage.Fighter[i].y>SCREEN_HEIGHT || stage.Fighter[i].health<=0)
            {
                stage.Fighter[i].health=0;
            }
        }
        else
        {
            movePlayer();
        }
        if(stage.Fighter[i].health<=0)
        {
            if(stage.Fighter[i]==player)
            {
                stage.Fighter[i].life--;
                player.life--;
                if(stage.Fighter[i].life<=0)
                {
                    isplayernull=true;
                    addExplosions(stage.Fighter[i].x,stage.Fighter[i].y,3+rand()%3);
                    addDebris(&stage.Fighter[i]);
                    pos.push_back(i);
                }
                else
                {
                    player.health=100;
                    stage.Fighter[i].health=100;
                }
            }
            else
            {
                addExplosions(stage.Fighter[i].x,stage.Fighter[i].y,3+rand()%3);
                addDebris(&stage.Fighter[i]);
                pos.push_back(i);
            }
        }
    }

    sort(pos.rbegin(),pos.rend());

    for(int i=0;i<pos.size();i++)
    {
        stage.Fighter.erase(stage.Fighter.begin()+pos[i]);
    }
}


static void resetStage(void)
{
	stage.Bullet.clear();
    stage.Fighter.clear();
    stage.explosion.clear();
    stage.debris.clear();
    memset(&stage,0,sizeof(Stage));
    
	initPlayer();

    initStarfield();

    isplayernull=false;

	enemyspawntimer=0;

    backgroundY = -720;

	stageResetTimer = FPS * 3;
    stage.score = 0;
}

static void logic(void)
{
    initfont();

    doBackground();

	doStarfield();

    doEnemy();

    doFighter();

	doBullet();

	spawnenemy();

    doExplosions();

	doDebris();

    if (isplayernull && --stageResetTimer <= 0)
	{
		resetStage();
	}
}

void initstage(void)
{
    playerTexture = loadTexture("Media/ship2.png");
    bulletTexture = loadTexture("Media/bullet_level_1.png");
    enemyTexture = loadTexture("Media/enemy_ships_1.png");
    alienBulletTexture = loadTexture("Media/enemybullet.png");
    explosionTexture = loadTexture("Media/explosion.png");
	background = loadTexture("Media/Background.jpg");
    fontTexture = loadTexture("font/font.png");
    healthbar = loadTexture("Media/Health bar.jpg");
    healthpod = loadTexture("Media/Healthpod.png");
    healthstat = loadTexture("Media/health_stat.png");
    Life = loadTexture("Media/life.png");

    app.delegate.logic = logic;
	app.delegate.draw = draw;
    resetStage();
}
#endif
