#include<iostream>
#include "RenderWindow.hpp"
#include "Map.hpp"

RenderWindow::RenderWindow(const char* p_title,int p_w, int p_h)
    :window(NULL),renderer(nullptr)
{
    window = SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_w,p_h,SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        cout << "Window failde to init. Error: " << SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

}
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer,p_filePath);

    if(texture == NULL)
        cout << "Fail to load texture: " << SDL_GetError() << endl;

    return texture;
    
}

SDL_Renderer* RenderWindow::erenderer()
{
    return renderer;
}

void RenderWindow::cleanUp()
{   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
    
}

void RenderWindow::render(SDL_Texture* p_tex,int x,int y,int w,int h)
{
	SDL_Rect src; 
	src.x = 0;
	src.y = 0;
	src.w = w;
	src.h = h;

	SDL_Rect dst;
	dst.x =x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}


