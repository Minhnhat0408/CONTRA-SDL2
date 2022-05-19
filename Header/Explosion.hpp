#pragma once
#include"Utils.hpp"

class Explosion
{
    public:
        Explosion(SDL_Renderer* screen);
        ~Explosion();

        
        Vector2f get_endpos(){return end_pos;}
        void setFrame(const int x){explosion.frame = x;}
        void setPos(Vector2f& t_pos){pos = t_pos;}
        void animationconfig();
        void Display(SDL_Renderer* screen);
        
    private:
        Vector2f pos;
        Vector2f end_pos;
        Animation explosion;
        SDL_Rect frame_clip[7];
};