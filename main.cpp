#include <iostream>
#include "SourceSDL.h"
#include "Character.h"
#include "Zombie.h"
#include "Input_Valuable.h"
#include "Sound.h"
#include "Text.h"

using namespace std;


void renderBackground(SDL_Texture *texture, SDL_Renderer *renderer)
{
    SDL_Rect tmp;
    tmp.x = 0;
    tmp.y = 0;
    SDL_QueryTexture(texture, 0, 0, &tmp.w, &tmp.h);
    tmp.w = tmp.w / 3 * 2;
    tmp.h = tmp.h / 3 * 2;

    SDL_RenderCopy(renderer, texture, 0, &tmp);
}

string getscore(int score)
{
    string ss = "";
    if(score == 0)
    {
        ss = "0";
        return ss;
    }
    while(score > 0)
    {
        ss.push_back(char(score % 10 + '0'));
        score /= 10;
    }
    reverse(ss.begin(), ss.end());
    return ss;
}

char *s;
void Ending()
{
    SDL_Event e;
    SDL_Delay(500);
    End_Music_Game();
    End_Zombie_Music();
    text = loadFont("Font.otf", 50);
    Score = renderText(s, text, color);
    Lose_Sound();
    int cnt = 0;
    while(cnt <= 90)
    {
        SDL_Delay(40);
        renderBackground(BG, renderer);
        character.RenderCharacter(renderer, jumpping, attacking);
        SDL_RenderPresent(renderer);
        character.dead();
        cnt++;
    }

    RenderText(TheEnd, SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 150);
    RenderText(Score, SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50);
    SDL_RenderPresent(renderer);

    while(true)
    {
        if(SDL_PollEvent(&e) && e.type == SDL_KEYDOWN) return;
    }
}

int main(int argc, char *argv[])
{
    s = new char[20];
    for(int i = 0; i < 21; i++) s[i] = ' ';

    srand(time(0));
    BG = loadTexture("BackGround.png", renderer);
    character.input(renderer);
    initText();

    initSound();
    Music_BackGround();
    renderBackground(BG, renderer);
    RenderText(NameGame, SCREEN_WIDTH / 2 - 560, SCREEN_HEIGHT / 2 - 200);
    RenderText(KeyPressToPlay, SCREEN_WIDTH / 2 - 210, SCREEN_HEIGHT / 2);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while(true)
    {
        SDL_Delay(40);
        if(SDL_WaitEvent(&e) && e.type == SDL_KEYDOWN) break;
    }
    Mix_PauseMusic();
    End_Music_BackGround();
    Music_Game();
    OneMoreZombie(renderer);
    Zombie_Music();

    while (End == 0)
    {
        Time++;
        renderBackground(BG, renderer);
        character.RenderCharacter(renderer, jumpping, attacking);
        RenderZombie(renderer);
        if (e.type == SDL_QUIT)
            break;
        if (!attacking && !jumpping && SDL_PollEvent(&e) == 0);
        SDL_Delay(20);
        if (jumpping || attacking || e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN)
        {
            character.action(e);
        }
        ZombieAction(character.getDirection(), character.getlocation(), e );

        if (Time - old >= 5)
            character.nothing();

        if(Time - oldlevel >= 500)
        {
            level = max(0, level - 10);
            oldlevel = Time;
        }

        if(Time - Time2 >= level)
        {
            OneMoreZombie(renderer);
            Zombie_Music();
            Time2 = Time;
        }

        if (Time >= 1e18)
        {
            Time2 = Time2 - Time;
            oldlevel = oldlevel - Time;
            Time = old = 0;
        }

        string ss = getscore(score);
        *(s + 0) = 'S';
        *(s + 1) = 'C';
        *(s + 2) = 'O';
        *(s + 3) = 'R';
        *(s + 4) = 'E';
        *(s + 5) = ':';
        *(s + 6) = ' ';
        int id = 6;
        for(char &x : ss)
        {
            id++;
            *(s + id) = x;
        }
        Score = renderText(s, text, color);
        RenderText(Score, 0, 0);

        SDL_RenderPresent(renderer);
    }
    Ending();

    delete(s);


    Mix_Quit();
    character.quit();
    quitSDL(window, renderer);
    return 0;
}
