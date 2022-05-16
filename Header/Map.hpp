#pragma once
#include"Utils.hpp"
using namespace std;

class Map
{
    public:
        Map(Vector2f p_pos, SDL_Texture* p_tex);

        int& getDir() { return direction;}
        map& get_Map() {return game_map;};
        Vector2f& getPos(){ return pos;}

        void draw(SDL_Renderer* renderer);
        void LoadMap(const char* namefile);
    private:
        Vector2f pos;
        int direction;
        map game_map;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
};


