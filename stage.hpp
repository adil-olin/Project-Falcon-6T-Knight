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
#include "HighScore.hpp"

using namespace std;
void initHighscores(void);
void addHighscore(int score);


static void initStarfield(void)
{
	for (int i = 0 ; i < MAX_STARS ; i++)
	{
		stars[i].x = rand() % SCREEN_WIDTH;
		stars[i].y = rand() % SCREEN_HEIGHT;
		stars[i].speed = 1 + rand() % 8;
	}
}

static void initBackground(void)
{
    background = loadTexture("Media/Background.jpg");
    backgroundY = -SCREEN_HEIGHT;
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
    player.energy=3;

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
void spwanUlt(void)
{
    ultEnergy.texture=ultpower;   
    ultEnergy.health=200;
    ultEnergy.w=1280;
    ultEnergy.h=123;
    ultEnergy.dx=0;
    ultEnergy.dy=-5;
    ultEnergy.x=0;
    ultEnergy.y=player.y;
    ultEnergy.side=player.side;
}
void doultEnergy(void)
{
    ultEnergy.x+=ultEnergy.dx;
    ultEnergy.y+=ultEnergy.dy;
    for(int i=0; i<stage.Fighter.size();i++)
    {
        if(stage.Fighter[i].side!=ultEnergy.side && collision(stage.Fighter[i].x,stage.Fighter[i].y,stage.Fighter[i].w,stage.Fighter[i].h,ultEnergy.x,ultEnergy.y,ultEnergy.w,ultEnergy.h))
        {
            stage.Fighter[i].health=0;
            stage.score++;
        }

    }
    if(ultEnergy.y<=-200){
        ultEnergy.health=0;
        if(!isbossnull)
        {
            Boss.health-=50;
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
        
            return true;
        }
    }
    if(!isbossnull && temp->side==player.side)
    {
        if (collision(temp->x, temp->y, temp->w, temp->h, Boss.x, Boss.y, Boss.w, Boss.h))
        {
            stage.score++;
            
            Boss.health -= temp->health;
            temp->health = 0;
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
	tmp_bullet.health = 10+level*2;
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
	e->reload = FPS-level + (rand()%(FPS)/2);
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

void doPod(void)
{
    vector<int>pos;
    for(int i=0;i<stage.pointpod.size();i++)
    {
        stage.pointpod[i].x+=stage.pointpod[i].dx;
        stage.pointpod[i].y+=stage.pointpod[i].dy;
        if(collision(player.x,player.y,player.w,player.h,stage.pointpod[i].x,stage.pointpod[i].y,stage.pointpod[i].w,stage.pointpod[i].h))
        {
            if(stage.pointpod[i].side==Life_Pod)
            {
                player.life=min(5,player.life+1);
                stage.Fighter[0].life=player.life;
            }
            else if(stage.pointpod[i].side==Ult_Pod)
            {
                player.energy=min(3,player.energy++);
                stage.Fighter[0].energy=player.energy;   
            }
            pos.push_back(i);
        }
        else if(stage.pointpod[i].y>=SCREEN_HEIGHT)
        {
            pos.push_back(i);
        }
    }
    sort(pos.rbegin(),pos.rend());
    for(int i=0;i<pos.size();i++)
    {
        stage.pointpod.erase(stage.pointpod.begin()+pos[i]);
    }
}

void AddPod(int x,Entity *e)
{
    Entity tmp;
    tmp.x=e->x;
    tmp.y=e->y;
    tmp.dx=0;
    tmp.dy=5;
    tmp.side=x;
    tmp.w=30;
    tmp.h=30;
    if(x==Life_Pod)
    {
        tmp.texture=lifepod;
        tmp.health=50;
        stage.pointpod.push_back(tmp);
    }
    else if(x==Ult_Pod)
    {
        tmp.texture=Ult;
        
        stage.pointpod.push_back(tmp);
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

                AddPod(rand()%(40-level),&stage.Fighter[i]);

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

void addBossBullets(void)
{
    int bulletCount = min(15,level/3+7);
    for(int i=1;i<=bulletCount;i++)
    {
        Entity tmp_bullet;

	    memset(&tmp_bullet, 0 , sizeof(Entity));

        tmp_bullet.x = Boss.x;
        tmp_bullet.y = Boss.y;
        tmp_bullet.health = 50;
        tmp_bullet.texture = alienBulletTexture;
        tmp_bullet.side = Boss.side;
	//SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
        tmp_bullet.w=30;
        tmp_bullet.h=53;

        tmp_bullet.x += (Boss.w / 2) - (tmp_bullet.w / 2);
        tmp_bullet.y += (Boss.h / 2) - (tmp_bullet.h / 2);
        calcSlope(Boss.x+SCREEN_WIDTH/bulletCount*i - bulletCount/2 * SCREEN_WIDTH/bulletCount, 500, Boss.x, Boss.y, &tmp_bullet.dx, &tmp_bullet.dy);

        tmp_bullet.dx *= ALIEN_BULLET_SPEED;
        tmp_bullet.dy *= ALIEN_BULLET_SPEED;
    
        stage.Bullet.push_back(tmp_bullet);
    }
}

void doBoss(void)
{
    if(Boss.y<=50)
    {
        Boss.y+=8;
    }
    else
    {
        if((Boss.x<=100 && Boss.dx<0) || (Boss.x>=1000 && Boss.dx>0))
        {
            Boss.dx*=(-1);
        }
        Boss.x+=Boss.dx;
    }
    if(Boss.reload--<=0)
    {
        fireAlienBullet(&Boss);
        Boss.reload = FPS;

    }
    if(boss_reload--<=0)
    {
        boss_reload=FPS*10;
        addBossBullets();
    }
    
    if(Boss.health<=0)
    {
        Boss.life--;
    }
    if(Boss.life<=0)
    {
        stage.score+=50*(level);
        boss_timer=FPS*60;
        isbossnull=true;
        addDebris(&Boss);
        addExplosions(Boss.x,Boss.y,3 + rand()%3);
        AddPod(rand()%10,&Boss);
        level++;
        level=min(25,level);
    }
}

void spawnBoss(void)
{
    isbossnull=false;
    Boss.texture = loadTexture("Media/REDBOSS.png");
    Boss.health = 1000 + level*400;
    Boss.side = SIDE_ALIEN;
    Boss.reload = FPS + rand()%10 - level;
    Boss.w = 150;
    Boss.h = 202;
    Boss.x = SCREEN_WIDTH - Boss.w/2;
    Boss.y = -300;
    Boss.life = level+1;
    Boss.dy = 8;
    Boss.dx = 5;
    boss_reload=FPS*2;
}


static void resetStage(void)
{   
    isstarted=true;
	stage.Bullet.clear();
    stage.Fighter.clear();
    stage.explosion.clear();
    stage.debris.clear();
    stage.pointpod.clear();
    memset(&stage,0,sizeof(Stage));
    
    initfont();

	initPlayer();

    initStarfield();

    isplayernull=false;

    isbossnull = true;

	enemyspawntimer=0;

    initBackground();

	stageResetTimer = FPS * 3;
    stage.score = 0;
}

static void logic(void)
{   
    if(app.keyboard[SDL_SCANCODE_ESCAPE])
    {
        homepage();
    }

    if(continue_timer--<=0){
        
        doBackground();

	    doStarfield();

        doEnemy();

        doFighter();

	    doBullet();
        
        doExplosions();

	    doDebris();

        doPod();
        
        if(ultEnergy.health>0)
        {
            doultEnergy();
        }

        if(player.energy==3 && app.keyboard[SDL_SCANCODE_SPACE])
        {
            player.energy=0;
            stage.Fighter[0].energy=0;
            spwanUlt();
        }

        if(isbossnull)
        {
    	    spawnenemy();
        }
    
        if(--boss_timer<=0)
        {
            boss_timer=max(0,boss_timer);
            if(isbossnull)
            {
                spawnBoss();
            }
            else
            {
                doBoss();
            }
        }

        continue_timer=max(0,continue_timer);
    }

    if (isplayernull && --stageResetTimer <= 0)
	{   
        isstarted=false;

        level=0;

        boss_timer=FPS*60;

		addHighscore(stage.score);

		initHighscores();
	}
}

void initstage(void)
{
    playerTexture = loadTexture("Media/ship2.png");
    bulletTexture = loadTexture("Media/bullet_level_1.png");
    enemyTexture = loadTexture("Media/enemy_ships_1.png");
    alienBulletTexture = loadTexture("Media/enemybullet.png");
    explosionTexture = loadTexture("Media/explosion.png");
	
    healthbar = loadTexture("Media/Health bar.png");
    lifepod = loadTexture("Media/lifepod.png");
    healthstat = loadTexture("Media/health_stat.png");
    Life = loadTexture("Media/life.png");
    BLife = loadTexture("Media/Blife.png");
    one=loadTexture("Media/one.png");
    two=loadTexture("Media/two.png");
    three=loadTexture("Media/three.png");
    Ult=loadTexture("Media/ult.png");
    engr=loadTexture("Media/energy.png");
    ultpower=loadTexture("Media/ultpower.png");

    app.delegate.logic = logic;
	app.delegate.draw = draw;
    r.x=210;
    if(isstarted==false)
    {
        resetStage();
    }
}
#endif
