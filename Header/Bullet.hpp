#pragma once
#include"Utils.hpp"


class Bullet
{
    public:
        Bullet();
        ~Bullet();
        enum BulletDir
        {
            DIR_RIGHT = 20,
            DIR_LEFT = 21,
            DIR_UP = 22,
            DIR_UP_LEFT = 23,
            DIR_UP_RIGHT = 24,
            DIR_DOWN_LEFT = 25,
            DIR_DOWN_RIGHT = 26,
            DIR_DOWN = 27,
            AUTO = 28,
        };  
        enum BulletType
        {
            RED_BULLET = 50,
            WHITE_BULLET = 51,
        };
        void setX(const int& x){move_val.x = x;}
        void setY(const int& y){move_val.y = y;}
        int getX(){return move_val.x;}
        int getY(){return move_val.y;}
        void setPos(const int x, const int y) {pos.x = x;pos.y =y;};    
        Vector2f getPos(){return pos;}
        void setType(const unsigned int& BulletType,SDL_Renderer* screen);
        void shoot(const bool& is_shot){shot = is_shot;}
        bool getStatus() const {return shot;}
        void Draw(SDL_Renderer* SDL_Renderer);
        void set_bullet_dir(const unsigned int& bulletDir) {dir= bulletDir;}
        unsigned int get_bullet_dir() const {return dir;}
        void HandleBullet(const int& borderX,const int& borderY,const double& move_VAL,const double& posc);
        void AutoAim(Vector2f& contra);

    private:
        Vector2f pos;
        Vector2f move_val;
        SDL_Texture* tex;
        SDL_Rect frame;
        SDL_Rect frameshot;
        bool shot;
        int dir;
        int type;
};