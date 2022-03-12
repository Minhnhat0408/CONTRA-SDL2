#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include "RenderWindow.hpp"
using namespace std;

int main(int argv,char* agrs[])
{   
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        cout << "Hey SDL_Init HAS FAILED. SDL_ERRROR: " << SDL_GetError() << endl;

    if(!(IMG_Init(IMG_INIT_PNG)))
        cout << "IMG_Init HAS FAILED. Error: " << SDL_GetError() << endl;

    RenderWindow window("Making SDLGame",1280,720);
    SDL_Texture* grassTexture = window.loadTexture("image/gfx/ground_grass_1.png");
    
    bool GameRunning = true;
    SDL_Event event;

    while(GameRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                GameRunning = false;
        }
        window.clear();
        window.render(grassTexture);
        window.display();
    }
    window.cleanUp();
    SDL_Quit();

    return 0;
}