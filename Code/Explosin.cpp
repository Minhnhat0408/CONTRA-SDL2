#include"Explosion.hpp"
using namespace std;

Explosion::Explosion(SDL_Renderer* screen)
{
    end_pos.x = 80;
    end_pos.y = 80;
    explosion.frame = 0;
    explosion.tex = IMG_LoadTexture(screen,"resources/gfx/BOOM.png");
}

Explosion::~Explosion()
{
    
}

void Explosion::animationconfig()
{
    if(end_pos.x > 0 && end_pos.y >0 )
    {
        for(int i = 0;i < 7;i++)
        {
            frame_clip[i].x = i*end_pos.x;
            frame_clip[i].y = 0;
            frame_clip[i].w = end_pos.x;
            frame_clip[i].h = end_pos.x;
        }
    }
    
}

void Explosion::Display(SDL_Renderer* screen)
{
    SDL_Rect* boom_clip = &frame_clip[explosion.frame/3];
    SDL_Rect showClip = {(int) pos.x, (int) pos.y , (int) end_pos.x , (int) end_pos.y};
    
    SDL_RenderCopy(screen,explosion.tex,boom_clip,&showClip);
}

