#include<iostream>
#include "RenderWindow.hpp"


RenderWindow::RenderWindow(const char* p_title,int p_w, int p_h)
    :window(NULL),renderer(nullptr)
{
    window = SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_w,p_h,SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        cout << "Window failde to init. Error: " << SDL_GetError() << endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer,p_filePath);

    if(texture == NULL)
        cout << "Fail to load texture: " << SDL_GetError() << endl;

    return texture;
    
}
void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_tex)
{   
    SDL_Rect src,dst;
    src.x = 0;src.y = 0;src.h = 32;src.w = 32;
    dst.x = 600;dst.y = 400;dst.h = 100;dst.w = 100;
    SDL_RenderCopy(renderer,p_tex,&src,&dst);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}