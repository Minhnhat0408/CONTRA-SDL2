#pragma once
#include"Utils.hpp"
#include"Map.hpp"
#include"Bullet.hpp"
#include"MainCharacter.hpp"

class Enemy
{   
    public:
    Enemy();
    ~Enemy();
    enum TypeEnemy
    {
        TANK = 0,
        TROOP = 1,
    };
    Vector2f setMove_val(const int x,const int y) {move_val.x = x;move_val.y = y;}
    Vector2f setPos(const double x, const double y) { pos.x = x; pos.y = y;}
    vector <Bullet*> getmagazine(){return magazine;}
    Vector2f getPos(){return pos;}
    SDL_Rect getRect(){return showClip;}
    int getFrequency(){return frequency;}
    int getType(){return type_enemy;}
    bool Death(){return terminated;}
    void Terminate(const bool stas) { terminated = stas;}
    void LoadTexture(SDL_Renderer* renderer);
    void setMap_pos(const Vector2f pos) {map_pos.x = pos.x;map_pos.y = pos.y;}
    void animationConfig();
    void Display(SDL_Renderer* renderer);
    void Movement(map& map_data,Map& map);
    void HandleMoveandMap(map& map,Map& mapfull);
    void set_enemy(const int &typeEnemy){type_enemy = typeEnemy;}
    void PathGuidance(MainCharacter& contra);

    void Init_armor(SDL_Renderer* renderer,Bullet* armor,MainCharacter& contra);
    void MakeBullet(SDL_Renderer* renderer,const int& x_limit,const int& y_limit,const double& move_VAL,Vector2f& posc);
    void removeBullet(const int& indx);
    void free(){SDL_DestroyTexture(Clips.tex);end_pos *= 0;}

    int Life;

    private:
        Vector2f pos;
        Vector2f end_pos;
        Vector2f move_val;
        Vector2f map_pos;
        bool on_ground;
        bool terminated;
        bool head_back;
        bool move_back;
        Animation Clips;
        SDL_Rect frame_clip_troop[6];
        SDL_Rect frame_clip_tank[4];
        SDL_Rect showClip;
        int type_enemy;
        int frequency;
        Input Status_type;
        vector <Bullet*> magazine;

};