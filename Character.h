#ifndef CHARACTER
#define CHARACTER

#include<bits/stdc++.h>
#include "SourceSDL.h"
#include "Input_Valuable.h"
#include "Sound.h"

SDL_Texture *ninja_walk[7];
SDL_Texture *ninja_jump[9];
SDL_Texture *ninja_attack[2][5];

struct Character
{
    int x = SCREEN_WIDTH / 2;
    int y = 625;
    int speed = 10;
    int direction = 1;
    int act_walk = 0;
    int act_jump = 1;
    int act_attack = 0;
    int type_attack = 1;

    int getDirection()
    {
        return direction;
    }

    pair<int, int> getlocation()
    {
        return make_pair(x, y);
    }

    void input(SDL_Renderer *renderer)
    {
        ninja_walk[0] = loadTexture("Animation/Walk/Walk.png", renderer);
        ninja_walk[1] = loadTexture("Animation/Walk/Walk1.png", renderer);
        ninja_walk[2] = loadTexture("Animation/Walk/Walk2.png", renderer);
        ninja_walk[3] = loadTexture("Animation/Walk/Walk3.png", renderer);
        ninja_walk[4] = loadTexture("Animation/Walk/Walk4.png", renderer);
        ninja_walk[5] = loadTexture("Animation/Walk/Walk5.png", renderer);
        ninja_walk[6] = loadTexture("Animation/Walk/Walk6.png", renderer);

        ninja_jump[1] = loadTexture("Animation/Jump/Jump1.png", renderer);
        ninja_jump[2] = loadTexture("Animation/Jump/Jump2.png", renderer);
        ninja_jump[3] = loadTexture("Animation/Jump/Jump3.png", renderer);
        ninja_jump[4] = loadTexture("Animation/Jump/Jump4.png", renderer);
        ninja_jump[5] = loadTexture("Animation/Jump/Jump5.png", renderer);
        ninja_jump[6] = loadTexture("Animation/Jump/Jump6.png", renderer);
        ninja_jump[7] = loadTexture("Animation/Jump/Jump7.png", renderer);
        ninja_jump[8] = loadTexture("Animation/Jump/Jump8.png", renderer);

        ninja_attack[0][0] = loadTexture("Animation/Attack1/0.png", renderer);
        ninja_attack[0][1] = loadTexture("Animation/Attack1/1.png", renderer);
        ninja_attack[0][2] = loadTexture("Animation/Attack1/2.png", renderer);
        ninja_attack[0][3] = loadTexture("Animation/Attack1/3.png", renderer);
        ninja_attack[0][4] = loadTexture("Animation/Attack1/4.png", renderer);

        ninja_attack[1][0] = loadTexture("Animation/Attack2/0.png", renderer);
        ninja_attack[1][1] = loadTexture("Animation/Attack2/1.png", renderer);
        ninja_attack[1][2] = loadTexture("Animation/Attack2/2.png", renderer);
        ninja_attack[1][3] = loadTexture("Animation/Attack2/3.png", renderer);
        ninja_attack[1][4] = loadTexture("Animation/Attack2/4.png", renderer);
    }

    void RenderCharacter(SDL_Renderer *renderer, bool &jumpping, bool &attacking)
    {
        SDL_Texture *texture;

        if(attacking) texture = ninja_attack[type_attack][act_attack];
        else if(jumpping) texture = ninja_jump[act_jump];
        else texture = ninja_walk[act_walk];

        SDL_Rect dest;

        dest.x = x;
        dest.y = y;

        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_Point center;
        center.x = 0;
        center.y = 0;

        if (direction == 1)
            SDL_RenderCopyEx(renderer, texture, 0, &dest, 0, &center, SDL_FLIP_NONE);
        else
            SDL_RenderCopyEx(renderer, texture, 0, &dest, 0, &center, SDL_FLIP_HORIZONTAL);
    }

    void nothing()
    {
        act_walk = 3;
    }

    void left()
    {
        direction = -1;
        act_walk++;
        if (act_walk == 7)
            act_walk = 0;
        x -= speed;
    }

    void right()
    {
        direction = 1;
        act_walk++;
        if (act_walk == 7)
            act_walk = 0;
        x += speed;
    }

    void up()
    {
        if(act_jump <= 3) y -= 3 * speed;
        if(act_jump >= 5) y += 3 * speed;
    }

    void action(SDL_Event &e)
    {
        if (e.key.keysym.sym == SDLK_a)
        {
            left();
            old = Time;
        }

        if (e.key.keysym.sym == SDLK_d)
        {
            right();
            old = Time;
        }
        if (e.key.keysym.sym == SDLK_w)
        {
            jumpping = 1;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            attacking = 1;
            Fight_Sound();
        }

        if(jumpping == 1)
        {
            if(act_jump >= 8)
            {
                y = 625;
                act_jump = 1;
                jumpping = 0;
                x += direction * 20;
            }
            else
            {
                up();
                if(direction == -1) left();
                else right();
                act_jump++;
            }
        }

        if(attacking == 1)
        {
            type_attack = 1 - type_attack;
            if(act_attack >= 4)
            {
                act_attack = 0;
                attacking = 0;
                SDL_Delay(20);
            }
            else
            {
                act_attack++;
            }
        }
    }

    void quit()
    {
        for (int i = 0; i < 7; i++)
        {
            SDL_DestroyTexture(ninja_walk[i]);
            ninja_walk[i] = NULL;
        }

        for (int i = 1; i <= 8; i++)
        {
            SDL_DestroyTexture(ninja_jump[i]);
            ninja_jump[i] = NULL;
        }

        for(int i = 0; i <= 1; i++) for(int j = 0; j < 5; j++)
        {
            SDL_DestroyTexture(ninja_attack[i][j]);
            ninja_attack[i][j] = NULL;
        }
    }
} character;




#endif
