#pragma once
#include"Map.hpp"
#include"Utils.hpp"
#include"Bullet.hpp"
#include<vector>
using namespace std;

class MainCharacter
{
    public:
        
        MainCharacter(SDL_Renderer* renderer);
        ~MainCharacter();
        enum Walktype
        {
            WALK_RIGHT = 0,
            WALK_LEFT =  1,    
        };
        Vector2f& getPos(){ return posc;}
        Vector2f& getMove_val(){return move_val;}
        Vector2f& getShowPos(){return show_pos;}
        SDL_Rect getRect(){return showClip;}
        bool Death(){return (respawn_time > 60);};
        void animationConfig();
        void Display();

        void HandlingUser(SDL_Event event,Map& m,Mix_Chunk* gun_shot);
        void Movement(map& map_data,Map& map);
        void HandleMoveandMap(map& map,Map& mapfull);
        void setMap(const int mapx,const int mapy){map_pos.x = mapx;map_pos.y = mapy;}// need to be cleenup
        void Respawn(){respawn_time = 120;showClip.y = 0;posc.y = 0;underwater = false;on_ground = true;};
        vector<Bullet*> get_magazine()const {return magazine;}
        void Fire();
        void removeBullet(const int& indx);
        Bullet* Reload();

        int Life;
        void Lives_display();
        //void Terminate(){respawn_time = 1000;showClip.x = 0;showClip.y = 0;}
        int get_Respawntime(){return respawn_time;}
    private:
        Vector2f posc; //starting position of the char
        Vector2f end_posc; //  width and height of the characteer
        Vector2f move_val;// move value of char
        Vector2f map_pos;// need clean up
        Vector2f show_pos;
        vector<Bullet*> magazine;
        SDL_Rect frame_clip_running[6];
        SDL_Rect frame_clip_standing[2];
        SDL_Rect frame_clip_jumping[4];
        SDL_Rect frame_clip_shooting[3];
        SDL_Rect frame_clip_shootup[2];
        SDL_Rect frame_clip_runshootup[3];
        SDL_Rect frame_clip_diving[5];
        SDL_Rect showClip;
        SDL_Renderer* screen;
        bool on_ground;
        bool underwater;
        bool shootimg;
        Input user_input;
        int status;
        int respawn_time;
        int gun_hold_time;
        Animation running;
        Animation standing;
        Animation jumping;
        Animation shooting;
        Animation shootup;
        Animation runshootup;
        Animation diving;
        SDL_Texture* fakewater;
        SDL_Rect waterframe;
        SDL_Rect life_frame;
        SDL_Texture* life_icon;
};