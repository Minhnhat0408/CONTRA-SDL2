#include"Bullet.hpp"
#include"MainCharacter.hpp"
#include<iostream>

Bullet::Bullet()
{
    move_val.x = 0;
    move_val.y = 0;
    shot = false;
    frame = {0,0,20,20};

}
Bullet::~Bullet()
{
    SDL_DestroyTexture(tex);
}
void Bullet::setType(const unsigned int& BulletType,SDL_Renderer* screen)
{
    type = BulletType;
    if(type == RED_BULLET)
    {
        tex = IMG_LoadTexture(screen,"resources/gfx/bullet.png");
    }else if(type == WHITE_BULLET)
    {
        tex = IMG_LoadTexture(screen,"resources/gfx/WBullet.png");
    }
}
void Bullet::Draw(SDL_Renderer* renderer)
{   
    frameshot = {(int) (pos.x ),(int) (pos.y),10,10};
    SDL_RenderCopy(renderer,tex,&frame,&frameshot);
}
void Bullet::HandleBullet(const int& borderX, const int& borderY,const double& move_VAL,const double& posc)
{
    if (dir == DIR_RIGHT)
    {   
        if( posc > gWinWidth/2 && posc < 8300)
        {
            if(move_VAL < 0)
            {
                pos.x+= move_val.x +SPEED;
            }else if(move_VAL > 0)
            {
                pos.x += move_val.x-SPEED;
            }else{
                pos.x+= move_val.x;
            }
        }else{
            pos.x+= move_val.x;
        }
        if (pos.x > borderX)
        {
            shot = false;
        }
    }
    else if (dir == DIR_LEFT)
    {   
        //cout << " hello" << endl;
        if( posc > gWinWidth/2 && posc < 8300)
        {
            if(move_VAL > 0)
            {
                pos.x-= move_val.x +SPEED;
            }else if(move_VAL < 0)
            {
                pos.x -= move_val.x-SPEED;
            }else{
                pos.x-= move_val.x;
            }
        }else{
        pos.x-= move_val.x;
        }
        if (pos.x < 0)
        {
            shot = false;
        }
    }
    else if (dir == DIR_UP)
    {
        pos.y -= move_val.y;
        if( posc > gWinWidth/2 && posc < 8300)
        {
            if(move_VAL> 0)
            {
                pos.x -=SPEED;
            }else if(move_VAL<0)
            {
                pos.x+=SPEED;
            }
        }
        
        //pos.x -= (move_VAL/abs(move_VAL))*SPEED;
        if (pos.y < 0)
        {
            shot = false;
        }
    }
    else if (dir == DIR_UP_LEFT)
    {
        if( posc > gWinWidth/2 && posc < 8300)
        {
            if(move_VAL > 0)
            {
                pos.x-= move_val.x +SPEED;
            }else if(move_VAL < 0)
            {
                pos.x -= move_val.x-SPEED;
            }else{
                pos.x-= move_val.x;
            }
        }else{
        pos.x-= move_val.x;
        }
        if (pos.x < 0)
        {
            shot = false;
        }
    
        pos.y -= move_val.y;
        if (pos.y < 0)
        {
            shot = false;
        }
    }
    else if (dir == DIR_UP_RIGHT)
    {
        if( posc > gWinWidth/2 && posc < 8300)
        {
            if(move_VAL < 0)
            {
                pos.x+= move_val.x +SPEED;
            }else if(move_VAL > 0)
            {
                pos.x += move_val.x-SPEED;
            }else{
                pos.x+= move_val.x;
            }
        }else{
            pos.x+= move_val.x;
        }
        if (pos.x > borderX)
        {
            shot = false;
        }
 
        pos.y -= move_val.y;
        if (pos.y < 0)
        {
            shot = false;
        }
    }
    else if (dir == DIR_DOWN_LEFT)
    {
        pos.x -= move_val.x;
        if (pos.x < 0)
        {
            shot = false;
        }
 
        pos.y += move_val.y;
        if (pos.y > borderY)
        {
            shot = false;
        }
    }
    else if (dir == DIR_DOWN_RIGHT)
    {
        pos.x += move_val.x;
        if (pos.x > borderX)
        {
            shot = false;
 
        }
        pos.y += move_val.y;
        if (pos.y > borderY)
        {
            shot = false;
        }
    }else if(dir == AUTO)
    {   
        if( posc > gWinWidth/2 && posc < 8300){
            if(move_VAL > 0)
            {
                pos.x+= move_val.x -SPEED;
            }else if(move_VAL < 0)
            {
                pos.x += move_val.x+SPEED;
            }else{
                pos.x += move_val.x;
            }
        }else{
            pos.x+= move_val.x;
        }
        pos.y += move_val.y;
        if (pos.x > borderX || pos.x <0)
        {   
            shot = false;
 
        }
        if (pos.y > borderY || pos.y < 0)
        {   
            shot = false;
        }
        
    }
    
}

void Bullet::AutoAim(Vector2f& contra)
{   
    Vector2f dir_move_val = (contra - pos);
    dir_move_val /= dir_move_val.length();// Normalized vector so that the length is equal to 1
    dir_move_val*= BULLET_SPEED; //Scale it up to 18
    move_val = dir_move_val;
}