#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<Map.hpp>
using namespace std;


class RenderWindow
{
    public:
        RenderWindow(const char* p_title,int p_w,int p_h);
        SDL_Texture* loadTexture(const char* p_filePath); 
        SDL_Renderer* erenderer();
        void cleanUp();
        void clear();
        void render(SDL_Texture* p_tex,int x,int y,int w,int h);
        void display();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};