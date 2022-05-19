#include"Text.hpp"

Text::Text()
{
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
    tex = NULL;
}

Text::~Text()
{

}

bool Text::LoadFromRenderText(TTF_Font* font,SDL_Renderer* screen)
{
    SDL_Surface* text_sur = TTF_RenderText_Solid(font,text.c_str(),text_color);
    if(text_sur)
    {
        tex = SDL_CreateTextureFromSurface(screen,text_sur);
        end_pos.x = text_sur->w;
        end_pos.y = text_sur->h;
        SDL_FreeSurface(text_sur); 
    }
    return tex;
}

void Text::free()
{
    if(tex!= NULL)
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
        
    }
}

void Text::SetColor(Uint8 red,Uint8 green,Uint8 blue)
{
    text_color.r = red;
    text_color.g = green;
    text_color.b = blue;
}

void Text::SetColor(int type)
{
    if(type == RED)
    {
        SDL_Color color = {255,0,0};
        text_color = color;
    }else if(type == WHITE)
    {
        SDL_Color color = {255,255,255};
        text_color = color;
    }else if(type == BLACK)
    {
        SDL_Color color = {0,0,0};
        text_color = color;
    }
}

void Text::RenderText(SDL_Renderer* screen,int x, int y, SDL_Rect* clip ,double angle ,SDL_Point*center ,SDL_RendererFlip flip )
{

    showText = {x,y,(int)end_pos.x,(int)end_pos.y};
    if(clip != NULL)
    {
        showText.w = clip->w;
        showText.h = clip->h;
    }
    SDL_RenderCopyEx(screen,tex,clip,&showText,angle,center,flip);
}