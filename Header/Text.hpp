#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include"Math.hpp"

class Text
{
    public:
        Text();
        ~Text();

        enum TextColor
        {
            RED = 0,
            WHITE = 1,
            BLACK = 2,
        };

        bool LoadFromFile(string path);
        bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
        void free();

        void SetColor(Uint8 red,Uint8 green,Uint8 blue);
        void SetColor(int type);
        void RenderText(SDL_Renderer* screen,int x, int y, 
        SDL_Rect* clip = NULL,double angle = 0.0,
        SDL_Point*center = NULL,SDL_RendererFlip flip = SDL_FLIP_NONE);

        SDL_Rect GetRect() const{return showText;}
        void setText(const char* p_text){text = p_text; }
        string getText()const{return text;}
    private:
        string text;
        SDL_Color text_color;
        SDL_Texture* tex;
        Vector2f pos;
        Vector2f end_pos;  
        SDL_Rect showText;
};