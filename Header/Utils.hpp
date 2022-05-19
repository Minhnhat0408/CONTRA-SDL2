#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include"Text.hpp"
#include"Math.hpp"
#define MAX_FALL_SPEED 50
#define JUMPPXL 20
#define TILE_SIZE 86
#define MAX_MAP_Y 7
#define MAX_MAP_X 100
#define SPEED 6
#define BULLET_SPEED 15
#define LEFT -1
#define RIGHT 1
#define BULLET_NUMBER 4
const int FRAME_PER_SECOND = 30  ;
const int gWinWidth = 1000;
const int gWinHeight = 560;

struct Input
{
     int left;
     int right;
     int up;
     int down;
     bool shoot;
     bool Jump;
};
struct map
{
    int start_x;
    int start_y ;
    int max_x;
    int max_y;
    int Tiles[MAX_MAP_Y][MAX_MAP_X];
};

struct Animation
{
    SDL_Texture* tex;
    int frame;
};

namespace utils
{
    inline float hirTimeInSeconds()
    {
        float t = SDL_GetTicks();
        t *= 0.001f;
        return t;
    }
}
namespace Collisions
{
    inline bool Collide(const SDL_Rect& object1,const SDL_Rect& object2)
    {
     

        int left_a = object1.x;
        int right_a = object1.x + object1.w;
        int top_a = object1.y;
        int bottom_a = object1.y + object1.h;
        
        int left_b = object2.x;
        int right_b = object2.x + object2.w;
        int top_b = object2.y;
        int bottom_b = object2.y + object2.h;
        
        //Case 1: size object 1 < size object 2
        if (left_a > left_b && left_a < right_b)
        {
            if (top_a > top_b && top_a < bottom_b)
            {
            return true;
            }
        }
        
        if (left_a > left_b && left_a < right_b)
        {
            if (bottom_a > top_b && bottom_a < bottom_b)
            {
            return true;
            }
        }
        
        if (right_a > left_b && right_a < right_b)
        {
            if (top_a > top_b && top_a < bottom_b)
            {
            return true;
            }
        }
        
        if (right_a > left_b && right_a < right_b)
        {
            if (bottom_a > top_b && bottom_a < bottom_b)
            {
            return true;
            }
        }
        
        //Case 2: size object 1 > size object 2
        if (left_b > left_a && left_b < right_a)
        {
            if (top_b > top_a && top_b < bottom_a)
            {
            return true;
            }
        }
        if (left_b > left_a && left_b < right_a)
        {
            if (bottom_b > top_a && bottom_b < bottom_a)
            {
            return true;
            }
        }

        if (right_b > left_a && right_b < right_a)
        {
            if (top_b > top_a && top_b < bottom_a)
            {
            return true;
            }
        }
        
        if (right_b > left_a && right_b < right_a)
        {
            if (bottom_b > top_a && bottom_b < bottom_a)
            {
            return true;
            }
        }
    //Case 3: size object 1 = size object 2
        if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
        {
            return true;
        }
        
        return false;
    }
}
namespace MenuUtils
{   
    inline bool CheckMouseClick(const int& x, const int& y, const SDL_Rect& rect)
    {
        if (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h)
        {
            return true;
        }
        return false;
    }

}
