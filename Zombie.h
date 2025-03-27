#ifndef ZOMBIE
#define ZOMBIE

#include<bits/stdc++.h>
#include "SourceSDL.h"
#include "Sound.h"

struct zombie
{
    int direction;
    int x = 50, y = 650;
    int act_walk = 0;
    int act_dead = 0;
    int speed = 2;
    int dead = 0;
    SDL_Texture *zombie_walk[10];
    SDL_Texture *zombie_dead[5];
    void input(SDL_Renderer *renderer)
    {
        zombie_walk[0] = loadTexture("Animation/ZombieWalk/Walk (1).png", renderer);
        zombie_walk[1] = loadTexture("Animation/ZombieWalk/Walk (2).png", renderer);
        zombie_walk[2] = loadTexture("Animation/ZombieWalk/Walk (3).png", renderer);
        zombie_walk[3] = loadTexture("Animation/ZombieWalk/Walk (4).png", renderer);
        zombie_walk[4] = loadTexture("Animation/ZombieWalk/Walk (5).png", renderer);
        zombie_walk[5] = loadTexture("Animation/ZombieWalk/Walk (6).png", renderer);
        zombie_walk[6] = loadTexture("Animation/ZombieWalk/Walk (7).png", renderer);
        zombie_walk[7] = loadTexture("Animation/ZombieWalk/Walk (8).png", renderer);
        zombie_walk[8] = loadTexture("Animation/ZombieWalk/Walk (9).png", renderer);
        zombie_walk[9] = loadTexture("Animation/ZombieWalk/Walk (10).png", renderer);

        zombie_dead[0] = loadTexture("Animation/ZombieDead/Dead (1).png", renderer);
        zombie_dead[1] = loadTexture("Animation/ZombieDead/Dead (2).png", renderer);
        zombie_dead[2] = loadTexture("Animation/ZombieDead/Dead (3).png", renderer);
        zombie_dead[3] = loadTexture("Animation/ZombieDead/Dead (4).png", renderer);
        zombie_dead[4] = loadTexture("Animation/ZombieDead/Dead (5).png", renderer);
    }

    void appear()
    {
        int location = rand() % 2;
        x = SCREEN_WIDTH - location * SCREEN_WIDTH;
    }

    void RenderZombie(SDL_Renderer *renderer)
    {
        SDL_Texture *texture;
        if(dead == 0) texture = zombie_walk[act_walk];
        else texture = zombie_dead[act_dead];

        SDL_Rect dest;

        dest.x = x;
        dest.y = y;

        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        dest.w /= 7;
        dest.h /= 7;

        SDL_Point center;
        center.x = 0;
        center.y = 0;

        if (direction == 1)
            SDL_RenderCopyEx(renderer, texture, 0, &dest, 0, &center, SDL_FLIP_NONE);
        else
            SDL_RenderCopyEx(renderer, texture, 0, &dest, 0, &center, SDL_FLIP_HORIZONTAL);
    }

    void left()
    {
        direction = -1;
        act_walk++;
        if (act_walk == 9)
            act_walk = 0;
        x -= speed;
    }

    void right()
    {
        direction = 1;
        act_walk++;
        if (act_walk == 9)
            act_walk = 0;
        x += speed;
    }

    void action(int &direction_main, pair<int, int> &location, SDL_Event &e )
    {
        if(dead == -1)
        {
            act_dead++;
            if(act_dead > 4)
            {
                dead = 1;
                quit();
            }
            return;
        }
        if(location.first > x) right();
        else left();
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(direction_main + direction == 0 && abs(x - location.first) <= 50 && location.second == 625)
            {
                dead = -1;
                Zombie_Dead_Sound();
                score++;
            }
        }
        else if(dead == 0 && x == location.first)
        {
            End = 1;
            Human_Heart();
        }
    }

    void quit()
    {
        for(int i = 0; i <= 9; i++)
        {
            SDL_DestroyTexture(zombie_walk[i]);
            zombie_walk[i] = NULL;
        }
    }
};
vector<zombie> Zombie;

void OneMoreZombie(SDL_Renderer *renderer)
{
    zombie a;
    a.input(renderer);
    a.appear();
    Zombie.push_back(a);
}

void RenderZombie(SDL_Renderer *renderer)
{
    int i = 0;
    while(i < Zombie.size())
    {
        if(Zombie[i].dead == 1) Zombie.erase(Zombie.begin() + i);
        else i++;
    }
    for(zombie &x : Zombie) x.RenderZombie(renderer);
}

void ZombieAction(int direction, pair<int, int> location, SDL_Event &e)
{
    for(zombie &x : Zombie) x.action(direction, location, e);
}

#endif // ZOMBIE
