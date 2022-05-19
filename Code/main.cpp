#include<iostream>
#include<vector>
#include"RenderWindow.hpp"
#include"Map.hpp"
#include"MainCharacter.hpp"
#include"Utils.hpp"
#include"Timer.hpp"
#include"Enemy.hpp"
#include"Explosion.hpp"
<<<<<<< HEAD
#include"Menu.hpp"
=======
>>>>>>> 27b7e42e2bd791de28fc9a352244f6b2f1541760
#include<time.h>

using namespace std;

RenderWindow window("CONTRA VERSION MINHMATMONG",gWinWidth,gWinHeight);

vector <Enemy*> MakeStandardTroopList(MainCharacter& contra);

vector <Enemy*> MakeRandomTroopList(MainCharacter& contra);


int main(int argv,char* agrs[])
{      
    
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        cout << "Hey SDL_Init HAS FAILED. SDL_ERRROR: " << SDL_GetError() << endl;
    if(!(IMG_Init(IMG_INIT_PNG)))
        cout << "IMG_Init HAS FAILED. Error: " << SDL_GetError() << endl;
    if (TTF_Init() == -1)
    {
        cout << SDL_GetError() << endl;
    }
    //TIME STEPPING
    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hirTimeInSeconds();

    //HANDLE TEXT
    TTF_Font* font = TTF_OpenFont("resources/fonts/Contra.ttf",30);
    Text Word;
    if(font == NULL)
    {
        cout << SDL_GetError() << endl;
    }
    Word.SetColor(Text::WHITE);

<<<<<<< HEAD
    //HANDLE SOUNDS
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music* BGsoundtrack = Mix_LoadMUS("resources/Sound effects/Stage1music.wav");
    Mix_Chunk* exp_seffect = Mix_LoadWAV("resources/Sound effects/BOOM.wav");
    Mix_Chunk* contra_death = Mix_LoadWAV("resources/Sound effects/death.wav");
    Mix_Chunk* gun_shot = Mix_LoadWAV("resources/Sound effects/enemy-gun.wav");

    //MENU ITEM
    SDL_Texture* Bg_title = IMG_LoadTexture(window.erenderer(),"resources/gfx/TilteBG.png");
    Mix_Music* title_song = Mix_LoadMUS("resources/Sound effects/Title song.wav");
    Mix_Music* wingame = Mix_LoadMUS("resources/Sound effects/Victory.wav");
    
    //GAME STATE
    bool Quit = false;
    bool gameRunning = false;
=======
    //OPEN AUDIO
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048);
    
    //GAME STATE
    bool gameRunning = false;
    bool Quit = false;
>>>>>>> 27b7e42e2bd791de28fc9a352244f6b2f1541760

    //HANDLING EVENTS
    SDL_Event event;

<<<<<<< HEAD
    //ALL MENU
    Menu MainMenu(font,window.erenderer());
    MainMenu.addText("PLAY");
    MainMenu.addText("CONTROLS");
    MainMenu.addText("QUIT");
    MainMenu.set_Frame(0,0,1000,500);
    MainMenu.setMusic(title_song);
    Menu Pause(font,window.erenderer());
    Pause.addText("CONTINUE");
    Pause.addText("MENU");
    Pause.setImg(Bg_title);
    Pause.set_Frame(100,100,800,300);
    
    Menu WinGame(font,window.erenderer());
    WinGame.addText("PLAY AGAIN");
    WinGame.addText("QUIT");
    WinGame.setImg(IMG_LoadTexture(window.erenderer(),"resources/gfx/WIN.png"));
    WinGame.set_Frame(0,0,1000,500);
    WinGame.setMusic(wingame);

    Menu Controls(font,window.erenderer());
    Controls.addText("MENU");
    Controls.set_Frame(0,0,1000,500);
    Controls.setMusic(title_song);
    while(!Quit)
    {   
        MainMenu.setImg(Bg_title);
        int menu = MainMenu.RenderMenu(event,240,290);//Menu::showMenu(font,window.erenderer(),event,"PLAY");
        if(menu == 1)
        {
            Quit = true;
        }else if(menu == 0)
        {   
            Controls.setImg(IMG_LoadTexture(window.erenderer(),"resources/gfx/CONTROLS.png"));
            int controls = Controls.RenderMenu(event,580,300);//Menu::Controls(font,window.erenderer(),event,"MENU");
        }else{
            gameRunning = true;
            srand(time(0));
            Timer control_time;
            

            //PLAY BACKGROUND MUSIC
            Mix_PlayMusic(BGsoundtrack,-1);

            //MAP
            SDL_Texture* Contramap1 = window.loadTexture("resources/gfx/ContraMapStage1BG.jpg");
            Map mapcontra(Vector2f(-10,-55),Contramap1);
            mapcontra.LoadMap("resources/tilemap.txt");
            map game_map = mapcontra.get_Map();
            

            // MAINCHARACTER
            MainCharacter contra(window.erenderer());
            contra.animationConfig();
            // SDL_SetRenderDrawColor(window.erenderer(),206, 66, 245,255);

            //MAKING TROOP
            vector <Enemy*> enemy_troops = MakeStandardTroopList(contra);

            //EXPLOSION EFFECT
            Explosion boom(window.erenderer());
            boom.animationconfig();

            //MAGIC NUMBER
            int Time = 1;
            int TankNumber = 8;
            int delay = 0;
            int delay2 = 0;
            while(gameRunning)
            {   
                control_time.start();
                // TIME STEPPING CONTROL GPU
                float newTime = utils::hirTimeInSeconds();
                float frameTime = newTime - currentTime;
                currentTime = newTime;
                accumulator += frameTime;
                while(accumulator >= timeStep)
                {   
                    while (SDL_PollEvent(&event))
                    {
                        if (event.type == SDL_QUIT)
                        {   
                            gameRunning = false;
                            Quit = true;
                        }else{
                            contra.HandlingUser(event,mapcontra,gun_shot);
                            if(SDL_KEYDOWN)
                            {
                                if(event.key.keysym.sym == SDLK_ESCAPE)
                                {   
                                    int pause = Pause.RenderMenu(event,350,400);
                                    if(pause == 1)
                                    {
                                        gameRunning = false;
                                    }
                                }
                            }
                            
                        }
                    }
                    accumulator -= timeStep;  
                }
                const float alpha = accumulator / timeStep; //50
                window.clear();
                mapcontra.draw(window.erenderer());
                
                //RANDOM FREQUENCY
                if(Time % 300 == 0)
                {   
                    vector <Enemy*> list = MakeRandomTroopList(contra);
                    enemy_troops.insert(enemy_troops.end(),list.begin(),list.end());
                    Time = 1;
                }else{
                    Time++;
                }
                //HANDLE TROOP AND COLLISIONS
                for(int i = 0;i < enemy_troops.size();i++)
                {      
                    Enemy* troop = enemy_troops[i];  
                    if(!troop->Death() && troop != NULL)
                    {   
                        double distance = contra.getPos().x - troop->getPos().x;
                        if(troop->getType() == Enemy::TROOP &&  distance >= 1000 && distance>=0)
                            troop->Terminate(true);
                        troop->setMap_pos(mapcontra.getPos());
                        troop->PathGuidance(contra);
                        troop->Movement(game_map,mapcontra);
                        vector<Bullet*> Tank_magazine = troop->getmagazine();
                        if(troop->getType() == Enemy::TANK )
                        {   
                            
                            if(Tank_magazine.size() < 3 && !contra.Death())
                            {   
                                Bullet* armor = new Bullet();
                                if(troop->getFrequency() %5 == 0)
                                {
                                    troop->Init_armor(window.erenderer(),armor,contra);
                                }
                            }
                            troop->MakeBullet(window.erenderer(),gWinWidth,gWinHeight,contra.getMove_val().x,contra.getPos());
                        }
                        troop->Display(window.erenderer());
                        SDL_Rect contra_hitbox = contra.getRect();
                        bool hitcontra =false;
                        
                        for(int j =0 ;j< Tank_magazine.size();j++)
                        {
                            Bullet* armor = Tank_magazine[j];
                            if(armor!= NULL)
                            {
                                SDL_Rect armor_hitbox = {(int) armor->getPos().x,(int) armor->getPos().y,10,10};

                                hitcontra = Collisions::Collide(contra_hitbox,armor_hitbox);
                                if(hitcontra && !contra.Death())
                                {   
                                    troop->removeBullet(j);
                                    break; 
                                }
                            }
                        } 
                        SDL_Rect troop_hitbox = troop->getRect();
                        if( Collisions::Collide(troop_hitbox,contra_hitbox) || hitcontra)
                        {   
                            if(contra.get_Respawntime() == 0)
                            {
                                contra.Life--;
                                for(int e = 0; e < 21;e++)
                                {
                                    Vector2f pos(contra_hitbox.x+contra_hitbox.w/2 - boom.get_endpos().x*0.5,contra_hitbox.y+contra_hitbox.h/2 - boom.get_endpos().y*0.5);
=======
    int menu = Menu::showMenu(font,window.erenderer(),event,"PLAY");
    if(menu == 1)
        Quit = true;
    if(Quit != true)
    {   
        gameRunning = true;
        srand(time(0));
        Timer control_time;
        //HANDLE SOUNDS
        
        Mix_Music* gchunk = Mix_LoadMUS("resources/Sound effects/Stage1music.wav");
        Mix_Chunk* exp_seffect = Mix_LoadWAV("resources/Sound effects/BOOM.wav");
        Mix_Chunk* contra_death = Mix_LoadWAV("resources/Sound effects/death.wav");
        Mix_Chunk* gun_shot = Mix_LoadWAV("resources/Sound effects/enemy-gun.wav");

        //PLAY BACKGROUND MUSIC
        Mix_PlayMusic(gchunk,-1);

        //MAP
        SDL_Texture* Contramap1 = window.loadTexture("resources/gfx/ContraMapStage1BG.jpg");
        Map mapcontra(Vector2f(-10,-55),Contramap1);
        mapcontra.LoadMap("resources/tilemap.txt");
        map game_map = mapcontra.get_Map();
        

        // MAINCHARACTER
        MainCharacter contra(window.erenderer());
        contra.animationConfig();
        // SDL_SetRenderDrawColor(window.erenderer(),206, 66, 245,255);

        //MAKING TROOP
        vector <Enemy*> enemy_troops = MakeStandardTroopList(contra);

        //EXPLOSION EFFECT
        Explosion boom(window.erenderer());
        boom.animationconfig();
        int Time = 1;
        while(gameRunning)
        {   
            control_time.start();
            // TIME STEPPING CONTROL GPU
            float newTime = utils::hirTimeInSeconds();
            float frameTime = newTime - currentTime;
            currentTime = newTime;
            accumulator += frameTime;
            while(accumulator >= timeStep)
            {   
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        gameRunning = false;
                    }else{
                        contra.HandlingUser(event,mapcontra,gun_shot);
                        if(SDL_KEYDOWN)
                        {
                            if(event.key.keysym.sym == SDLK_ESCAPE)
                            {
                                int menu_tmp = Menu::showMenu(font,window.erenderer(),event,"CONTINUE");
                                if(menu_tmp == 1)
                                    Quit = true;
                            }
                        }
                        
                    }
                }
                accumulator -= timeStep;  
            }
            const float alpha = accumulator / timeStep; //50
            window.clear();

            mapcontra.draw(window.erenderer());
            
            if(Time % 300 == 0)
            {   
                vector <Enemy*> list = MakeRandomTroopList(contra);
                enemy_troops.insert(enemy_troops.end(),list.begin(),list.end());
                Time = 1;
            }else{
                Time++;
                //cout << Time;
            }
            
            for(int i = 0;i < enemy_troops.size();i++)
            {      
                Enemy* troop = enemy_troops[i];  
                if(!troop->Death() && troop != NULL)
                {   
                    double distance = contra.getPos().x - troop->getPos().x;
                    if(troop->getType() == Enemy::TROOP &&  distance >= 1000 && distance>=0)
                        troop->Terminate(true);
                    troop->setMap_pos(mapcontra.getPos());
                    troop->PathGuidance(contra);
                    troop->Movement(game_map,mapcontra);
                    vector<Bullet*> Tank_magazine = troop->getmagazine();
                    if(troop->getType() == Enemy::TANK )
                    {   
                        
                        if(Tank_magazine.size() < 3 && !contra.Death())
                        {   
                            Bullet* armor = new Bullet();
                            if(troop->getFrequency() %5 == 0)
                            {
                                troop->Init_armor(window.erenderer(),armor,contra);
                            }
                        }
                        troop->MakeBullet(window.erenderer(),gWinWidth,gWinHeight,contra.getMove_val().x,contra.getPos());
                    }
                    troop->Display(window.erenderer());
                    SDL_Rect contra_hitbox = contra.getRect();
                    bool hitcontra =false;
                    
                    for(int j =0 ;j< Tank_magazine.size();j++)
                    {
                        Bullet* armor = Tank_magazine[j];
                        if(armor!= NULL)
                        {
                            SDL_Rect armor_hitbox = {(int) armor->getPos().x,(int) armor->getPos().y,10,10};

                            hitcontra = Collisions::Collide(contra_hitbox,armor_hitbox);
                            if(hitcontra && !contra.Death())
                            {   
                                troop->removeBullet(j);
                                break; 
                            }
                        }
                    } 
                    SDL_Rect troop_hitbox = troop->getRect();
                    if( Collisions::Collide(troop_hitbox,contra_hitbox) || hitcontra)
                    {   
                        contra.Life--;
                        for(int e = 0; e < 21;e++)
                        {
                            Vector2f pos(contra_hitbox.x+contra_hitbox.w/2 - boom.get_endpos().x*0.5,contra_hitbox.y+contra_hitbox.h/2 - boom.get_endpos().y*0.5);
                            boom.setFrame(e);
                            boom.setPos(pos);
                            boom.Display(window.erenderer());
                        }
                        Mix_PlayChannel(-1,contra_death,0);
                        if(contra.Life > 0) 
                        {
                            contra.Respawn();
                        }
                        if(Collisions::Collide(troop_hitbox,contra_hitbox))
                        {
                            troop->Terminate(true);
                        } 
                    }

                    
                }else{
                    troop->free();
                    troop = NULL;
                    enemy_troops.erase(enemy_troops.begin()+i);
                }
                
            }
            contra.Display();
            contra.setMap(mapcontra.getPos().x,mapcontra.getPos().y);
            contra.Movement(game_map,mapcontra);
            contra.Fire();
            if(contra.Life <= 0)
            {
                gameRunning = false;
            }
            //Check contra's bullet collisions 
            Vector2f exp_hitbox = boom.get_endpos();
            vector <Bullet*> magazine = contra.get_magazine();
            for(int i = 0;i < magazine.size();i++)
            {
                Bullet* armor = magazine[i];
                if(armor != NULL)
                {
                    for(int j = 0; j < enemy_troops.size();j++)
                    {
                        Enemy* troop = enemy_troops.at(j);
                        if(troop != NULL)
                        {   
                            SDL_Rect troop_hitbox = troop->getRect();
                            SDL_Rect armor_hitbox = {(int) armor->getPos().x,(int) armor->getPos().y,10,10};
                            if(Collisions::Collide(troop_hitbox,armor_hitbox))
                            {
                                for(int e = 0; e < 21;e++)
                                {
                                    Vector2f pos(troop_hitbox.x+troop_hitbox.w/2 - exp_hitbox.x*0.5,troop_hitbox.y+troop_hitbox.h/2 - exp_hitbox.y*0.5);
>>>>>>> 27b7e42e2bd791de28fc9a352244f6b2f1541760
                                    boom.setFrame(e);
                                    boom.setPos(pos);
                                    boom.Display(window.erenderer());
                                }
<<<<<<< HEAD
                                Mix_PlayChannel(-1,contra_death,0);
                                if(contra.Life > 0) 
                                {
                                    contra.Respawn();
                                }
                                if(Collisions::Collide(troop_hitbox,contra_hitbox))
                                {
                                    troop->Terminate(true);
                                } 
                            }
                            
                        }
                    }else{
                        if(troop->getType() == Enemy::TANK)
                            TankNumber--;
                        troop->free();
                        troop = NULL;
                        enemy_troops.erase(enemy_troops.begin()+i);
                    }
                    
                }

                contra.Display();
                contra.Lives_display();
                contra.setMap(mapcontra.getPos().x,mapcontra.getPos().y);
                contra.Movement(game_map,mapcontra);
                contra.Fire();

                //GAMEOVER
                if(contra.Life <= 0)
                {   
                    Text gameover;
                    gameover.setText("GAME OVER");
                    gameover.SetColor(Text::RED);
                    gameover.LoadFromRenderText(font,window.erenderer());
                    gameover.RenderText(window.erenderer(),350,200);
                    if(delay2 < 55)
                    {   
                        contra.Respawn();
                        delay2++;
                    }else{
                        gameRunning = false;
                    }
                    
                }

                //VICTORY
                if(TankNumber == 0)
                {
                    Text Victory;

                    Victory.setText("VICTORY");
                    Victory.SetColor(Text::RED);
                    Victory.LoadFromRenderText(font,window.erenderer());
                    Victory.RenderText(window.erenderer(),400,200);
                    if(delay <80)
                    {
                        delay++;
                    }else{
                        int win = WinGame.RenderMenu(event,350,350);
                        if(win == 1)
                        {
                            Quit = true;
                            gameRunning = false;
                        }else{
                            gameRunning = false;
                        }
                    }
                }
                
                //Check contra's bullet collisions 
                Vector2f exp_hitbox = boom.get_endpos();
                vector <Bullet*> magazine = contra.get_magazine();
                for(int i = 0;i < magazine.size();i++)
                {
                    Bullet* armor = magazine[i];
                    if(armor != NULL)
                    {
                        for(int j = 0; j < enemy_troops.size();j++)
                        {
                            Enemy* troop = enemy_troops.at(j);
                            if(troop != NULL)
                            {   
                                SDL_Rect troop_hitbox = troop->getRect();
                                SDL_Rect armor_hitbox = {(int) armor->getPos().x,(int) armor->getPos().y,10,10};
                                if(Collisions::Collide(troop_hitbox,armor_hitbox))
                                {
                                    for(int e = 0; e < 21;e++)
                                    {
                                        Vector2f pos(troop_hitbox.x+troop_hitbox.w/2 - exp_hitbox.x*0.5,troop_hitbox.y+troop_hitbox.h/2 - exp_hitbox.y*0.5);
                                        boom.setFrame(e);
                                        boom.setPos(pos);
                                        boom.Display(window.erenderer());
                                    }
                                    Mix_PlayChannel(-1,exp_seffect,0);
                                    contra.removeBullet(i);
                                    troop->Life--;
                                    if(troop->Life <= 0)
                                        troop->Terminate(true);

                                }   
                            }
                        }
                    }
                }
                
                window.display();
                //FPS CONTROL
                int real_time = control_time.get_Ticks();   
                int time_per_frame = 1000/FRAME_PER_SECOND;
                if(real_time < time_per_frame);
                {
                    int delay_time = time_per_frame - real_time;
                    if(delay_time >=0)
                        SDL_Delay(delay_time);
                }

            }
            for(int i = 0; i < enemy_troops.size();i++)
            {
                Enemy* troop = enemy_troops[i];
                if(troop)
                {   
                    troop->free();
                    troop = NULL;
                }
            }
            enemy_troops.clear();
        }    
          
    }
    window.cleanUp();   
=======
                                Mix_PlayChannel(-1,exp_seffect,0);
                                contra.removeBullet(i);
                                troop->Life--;
                                if(troop->Life <= 0)
                                    troop->Terminate(true);
                            }   
                        }
                    }
                }
            }
            window.display();
            //FPS CONTROL
            int real_time = control_time.get_Ticks();   
            int time_per_frame = 1000/FRAME_PER_SECOND;
            if(real_time < time_per_frame);
            {
                int delay_time = time_per_frame - real_time;
                if(delay_time >=0)
                    SDL_Delay(delay_time);
            }

        }
        for(int i = 0; i < enemy_troops.size();i++)
        {
            Enemy* troop = enemy_troops[i];
            if(troop)
            {   
                troop->free();
                troop = NULL;
            }
        }
        enemy_troops.clear();
    }
    window.cleanUp();
>>>>>>> 27b7e42e2bd791de28fc9a352244f6b2f1541760
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

vector <Enemy*> MakeRandomTroopList(MainCharacter& contra)
{   
    vector <Enemy*> appendE;
    Enemy* kamikaze_troop = new Enemy[5];
    int enemy_pos = 8800-contra.getPos().x+500;
    double postroopy[11] = {170,170,170,170,254,254,254,254,340,340,410};
    for(int i = 0;i <5;i++)
    {
        Enemy* kamikaze = (kamikaze_troop+i);
        if(kamikaze != nullptr)
        {   
            kamikaze->set_enemy(Enemy::TROOP);
            kamikaze->LoadTexture(window.erenderer());
            kamikaze->animationConfig();
            kamikaze->setPos(rand()%enemy_pos + contra.getPos().x+500,postroopy[rand()%11]);
            appendE.push_back(kamikaze); 
        }

    }
    return appendE;
}
vector <Enemy*> MakeStandardTroopList(MainCharacter& contra)
{
    vector <Enemy*> appendE;
    Enemy* tank_army = new Enemy[8];
<<<<<<< HEAD
    double postankx[8] = {1050,2500,4300,4100,5300,7000,8300,8250};
=======
    double postankx[8] = {1050,2500,4300,4100,5300,7000,8100,8050};
>>>>>>> 27b7e42e2bd791de28fc9a352244f6b2f1541760
    double postanky[8] = {240,0,230,0,0,0,0,300};
    for(int i = 0;i < 8;i++ )
    {   
        Enemy* tank = (tank_army+i);
        if(tank !=NULL)
        {
            tank->set_enemy(Enemy::TANK);
            tank->LoadTexture(window.erenderer());  
            tank->animationConfig();
            tank->setPos(postankx[i],postanky[i]);
            appendE.push_back(tank);
        }
    }
    Enemy* kamikaze_troop = new Enemy[20];
<<<<<<< HEAD
=======
    //int enemy_pos = 8800-contra.getPos().x-500;
>>>>>>> 27b7e42e2bd791de28fc9a352244f6b2f1541760
    double postroopy[11] = {170,170,170,170,254,254,254,254,340,340,410};
    Enemy* kamikaze1 = (kamikaze_troop);
    kamikaze1->set_enemy(Enemy::TROOP);
    kamikaze1->LoadTexture(window.erenderer());
    kamikaze1->animationConfig();
    kamikaze1->setPos(800, 430);
    appendE.push_back(kamikaze1);
    for(int i = 1;i <20;i++)
    {
        Enemy* kamikaze = (kamikaze_troop+i);
        if(kamikaze != nullptr)
        {   
            kamikaze->set_enemy(Enemy::TROOP);
            kamikaze->LoadTexture(window.erenderer());
            kamikaze->animationConfig();
            kamikaze->setPos(rand()%8349+500, postroopy[rand()%11]);
            appendE.push_back(kamikaze); 
        }
    }
    return appendE;
}