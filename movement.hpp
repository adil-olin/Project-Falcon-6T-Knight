#pragma once
#ifndef movement_hpp
#define movement_hpp 

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<bits/stdc++.h>
#include<SDL2/SDL_ttf.h>
using namespace std;

static void spawnenemy(void)
{
    if(--enemyspawntimer<=0)
    {
        Entity temp_enemy;
        memset(&temp_enemy,0,sizeof(Entity));
        temp_enemy.side=SIDE_ALIEN;
        temp_enemy.health=1;
        temp_enemy.w=80;
        temp_enemy.h=77;
        temp_enemy.y=0;
        temp_enemy.x= rand() % SCREEN_HEIGHT;
        temp_enemy.texture = enemyTexture;
        //SDL_QueryTexture(temp_enemy.texture, NULL, NULL, &temp_enemy.x, temp_enemy.y);
        temp_enemy.dy = (2 + (rand() % 4));
        temp_enemy.dx = 0;
		enemyspawntimer = 100 + (rand() % 60);
        temp_enemy.reload = FPS/2;
        stage.Fighter.push_back(temp_enemy);
    }
}

//stage.Fighter[0] is same as player id. So, we have to update them both to keep them same

static void fireBullet(void)
{
    Entity temp_bullet;
    memset(&temp_bullet,0,sizeof(Entity));
    temp_bullet.side=SIDE_PLAYER;
    temp_bullet.x = player.x;
	temp_bullet.y = player.y;
    temp_bullet.w=30;
    temp_bullet.h=53;
    temp_bullet.x += (player.w / 2) - (temp_bullet.w / 2);
	temp_bullet.y -= temp_bullet.h;
    temp_bullet.health=1;
    temp_bullet.dx=0;
    temp_bullet.dy= - PLAYER_BULLET_SPEED;
    temp_bullet.texture = bulletTexture;

    stage.Bullet.push_back(temp_bullet);

    player.reload=8;
    stage.Fighter[0].reload=8;
}

void movePlayer()
{
    if(!isplayernull)
    {
        player.dx = player.dy = 0;
        stage.Fighter[0].dx = stage.Fighter[0].dy=0;

        if (player.reload > 0)
        {
            player.reload--;
            stage.Fighter[0].reload--;
        }

        if (app.keyboard[SDL_SCANCODE_UP])
        {
            player.dy = -PLAYER_SPEED;
            stage.Fighter[0].dy = -PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_DOWN])
        {
            player.dy = PLAYER_SPEED;
            stage.Fighter[0].dy = PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_LEFT])
        {
            player.dx = -PLAYER_SPEED;
            stage.Fighter[0].dx = -PLAYER_SPEED;
        }

        if (app.keyboard[SDL_SCANCODE_RIGHT])
        {
            player.dx = PLAYER_SPEED;
            stage.Fighter[0].dx = PLAYER_SPEED;
        }
        if((app.keyboard[SDL_SCANCODE_LSHIFT] || app.keyboard[SDL_SCANCODE_RSHIFT]))
        {
            player.dx*=1.5;
            player.dy*=1.5;
            stage.Fighter[0].dy*=1.5;
            stage.Fighter[0].dx*=1.5;
        }

        if (player.reload == 0)
        {
            if(!(app.keyboard[SDL_SCANCODE_LSHIFT] || app.keyboard[SDL_SCANCODE_RSHIFT]))
            {
                fireBullet();
            }
        }

        player.x += player.dx;
        player.y += player.dy;
        stage.Fighter[0].x+=stage.Fighter[0].dx;
        stage.Fighter[0].y+=stage.Fighter[0].dy;


        if(player.x<0)
        {
            player.x=0;
            stage.Fighter[0].x=0;
        }
        if(player.x>SCREEN_WIDTH-player.w)
        {
            player.x=SCREEN_WIDTH-player.w;
            stage.Fighter[0].x = SCREEN_WIDTH-player.w;
        }
        if(player.y<0)
        {
            player.y=0;
            stage.Fighter[0].y=0;
        }
        if(player.y>SCREEN_HEIGHT-player.w)
        {
            player.y = SCREEN_HEIGHT-player.w;
            stage.Fighter[0].y = SCREEN_HEIGHT-player.w;
        }
    }
}
#endif