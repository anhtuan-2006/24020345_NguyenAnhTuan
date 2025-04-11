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

char* getstringandint(string s, int val)
{
    string ss;
    if (val == 0)
    {
        ss.push_back('0');
    }
    else
    {
        while (val > 0)
        {
            ss.push_back('0' + (val % 10));
            val /= 10;
        }
        reverse(ss.begin(), ss.end());
    }
    char *res;
    res = new char[int(s.size() + ss.size()) + 1];
    for(int i = 0; i < s.size(); i++) res[i] = s[i];
    for(int i = 0; i < ss.size(); i++) res[i + s.size()] = ss[i];
    res[int(s.size() + ss.size())] = '\0';
    return res;
}

void get_high_score()
{
    ifstream inp;
    inp.open("HighScore.txt");
    inp >> highscore;
    inp.close();
}

void update_high_score()
{
    ofstream out;
    out.open("HighScore.txt");
    highscore = max(highscore, score);
    out << highscore;
    out.close();
}

char *s;
void Ending()
{
    update_high_score();
    SDL_Event e;
    SDL_Delay(500);
    End_Music_Game();
    End_Zombie_Music();
    Lose_Sound();
    int cnt = 0;
    while(cnt <= 10)
    {
        SDL_Delay(40);
        renderBackground(BG, renderer);
        character.RenderCharacter(renderer, jumpping, attacking);
        SDL_RenderPresent(renderer);
        character.dead();
        cnt++;
    }

    renText("The End !!!", 100, SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 150, 225, 225, 225);
    renText(getstringandint("Score: ", score), 50, SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 225, 225, 225);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    while(true)
    {
        if(SDL_PollEvent(&e) && e.type == SDL_KEYDOWN) return;
    }
}

int Rand(int l, int r)
{
    return rand() % (r - l + 1) + l;
}

int main(int argc, char *argv[])
{
    get_high_score();
    srand(time(0));
    BG = loadTexture("BackGround.png", renderer);
    character.input(renderer);
    initText();

    initSound();
    Music_BackGround();
    renderBackground(BG, renderer);
    renText("BLACK VS ZOMBIE", 100, SCREEN_WIDTH / 2 - 560, SCREEN_HEIGHT / 2 - 200, 225, 225, 225);
    renText("Press any key to start", 25, SCREEN_WIDTH / 2 - 210, SCREEN_HEIGHT / 2, 225, 225, 225);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while(true)
    {
        SDL_Delay(40);
        if(SDL_WaitEvent(&e) && e.type == SDL_KEYDOWN) break;
    }
    End_Music_BackGround();
    //Music_Game();
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
        health.action();

        if (Time - old >= 5)
            character.nothing();

        if(score >= (10 + Level) * Level)
        {
            level = max(5, level - 10);
            Level++;
            Level_Up();
            oldlevel = Time;
            health.More(Rand(10, SCREEN_WIDTH - 10));
        }
        if(Time - oldlevel <= 100 && Level != 1)
        {
            int r = rand() % 226;
            int g = rand() % 226;
            int b = rand() % 226;
            renText("Level Up", 100, SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 350, r, g, b);
        }

        if(Time - Time2 >= level)
        {
            OneMoreZombie(renderer);
            Time2 = Time;
        }

        if (Time >= 1e18)
        {
            Time2 = Time2 - Time;
            oldlevel = oldlevel - Time;
            oldHeart = oldHeart - Time;
            Time = old = 0;
        }

        renText(getstringandint("High Score: ", highscore), 25, 0, 0, 225, 225, 225);
        renText(getstringandint("Score: ", score), 25, 0, 25, 225, 225, 225);
        renText(getstringandint("Level: ", Level), 25, 0, 50, 225, 225, 225);
        renText(getstringandint("Heart: ", Heart), 25, 0, 75, 225, 225, 225);

        SDL_RenderPresent(renderer);
    }
    Ending();

    delete(s);


    Mix_Quit();
    character.quit();
    quitSDL(window, renderer);
    return 0;
}
