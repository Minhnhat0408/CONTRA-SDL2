#pragma once
#include<vector>
#include"Utils.hpp"

class Menu
{
    public:
        Menu(TTF_Font* p_font,SDL_Renderer* p_screen);
        ~Menu();
        void set_Frame(int x,int y,int w, int h){frame_img = {x,y,w,h};}
        void addText(const char* word);//{button.push_back(word);selectedItem.push_back(false);}
        void setImg(SDL_Texture* tex){img = tex;}
        void setMusic(Mix_Music* st){soundtrack = st;}
        int RenderMenu(SDL_Event p_event,int x,int y);
        

    private:
        vector <Text> button;
        vector<bool> selectedItem;
        SDL_Texture* img;
        SDL_Rect frame_img;
        SDL_Renderer* screen;
        Mix_Music* soundtrack;
        TTF_Font* font;
    
};
