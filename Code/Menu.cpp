#include"Menu.hpp"
using namespace std;

Menu::Menu(TTF_Font* p_font,SDL_Renderer* p_screen):screen(p_screen),font(p_font)
{  
    soundtrack = NULL;
}
Menu::~Menu()
{
    //SDL_DestroyTexture(img);
}

void Menu::addText(const char* word)
{
    Text text;
    text.setText(word);
    text.SetColor(Text::WHITE);
    button.push_back(text);
    selectedItem.push_back(false);
}
int Menu::RenderMenu(SDL_Event p_event,int x ,int y)
{   
    if(soundtrack!=NULL)
        Mix_PlayMusic(soundtrack,-1);
    int mouse_posx;
    int mouse_posy;
    while (true)
    {   
        SDL_RenderClear(screen);
        SDL_RenderCopy(screen,img,NULL,&frame_img);
        for (int i = 0; i < button.size(); ++i)
        {   
            button[i].LoadFromRenderText(font,screen);
            button[i].RenderText(screen,x,y+i*50);//240 290
        }
        while (SDL_PollEvent(&p_event))
        {
            switch (p_event.type)
            {
                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEMOTION:
                    {
                        mouse_posx = p_event.motion.x;
                        mouse_posy = p_event.motion.y;

                        for (int i = 0; i < button.size(); i++)
                        {
                            if (MenuUtils::CheckMouseClick(mouse_posx, mouse_posy, button[i].GetRect()))
                            {
                                if (selectedItem[i] == false)
                                {
                                    selectedItem[i] = 1;
                                    button[i].SetColor(Text::RED);
                                }
                            }
                            else
                            {
                                if (selectedItem[i] == true)
                                {
                                    selectedItem[i] = 0;
                                    button[i].SetColor(Text::WHITE);
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    {
                        mouse_posx = p_event.button.x;
                        mouse_posy = p_event.button.y;

                        for (int i = 0; i < button.size(); i++)
                        {
                            if (MenuUtils::CheckMouseClick(mouse_posx, mouse_posy, button[i].GetRect()))
                            {   
                                return i-(button.size()-2);
                            }
                        }
                    }
                    break;
            default:
                break;
            }
        }
        for(int i =0;i <button.size();i++)
        {
            button[i].free();
        }
        SDL_RenderPresent(screen);
    }

    Mix_FreeMusic(soundtrack);
    soundtrack = NULL;   
    SDL_DestroyTexture(img);
    img = NULL;
    return 1;
}