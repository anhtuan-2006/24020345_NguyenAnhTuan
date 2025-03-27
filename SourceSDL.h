#ifndef SOURCESDL
#define SOURCESDL

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include<bits/stdc++.h>

using namespace std;

const int SCREEN_WIDTH = 1536;
const int SCREEN_HEIGHT = 864;

void logErrorAndExit(const char *msg, const char *error);
SDL_Window *initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char *WINDOW_TITLE);
SDL_Renderer *createRenderer(SDL_Window *window);
void quitSDL(SDL_Window *window, SDL_Renderer *renderer);
void waitUntilKeyPressed();
void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer *renderer);
SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer);
Mix_Music *loadMusic(const char* path);
void playMusic(Mix_Music *gMusic);
Mix_Chunk* loadSound(const char* path);
void playSound(Mix_Chunk* gChunk);

#endif
