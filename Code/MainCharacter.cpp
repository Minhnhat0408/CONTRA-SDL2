#include<iostream>
#include "MainCharacter.hpp"

using namespace std;


// MAIN CHARACTER SECTION
MainCharacter::MainCharacter(SDL_Renderer* renderer):screen(renderer)
{	
	posc.x = 50;
	posc.y = 0;
	show_pos.x = posc.x;
	show_pos.y = posc.y;
	move_val.x =0;
	move_val.y = 0;
	end_posc.x = 40;
	end_posc.y = 80;
	status = -1;
	user_input.left = 0;
	user_input.right = 0;
	user_input.down = 0;
	user_input.Jump = false;
	user_input.up = 0;
	user_input.shoot = false;
	shootimg = false;
	gun_hold_time = 0;
	on_ground = true;
	underwater = false;
	map_pos.x = 0;
	map_pos.y = 0;
	respawn_time = 0;
	Life = 3;
	running.tex = IMG_LoadTexture(renderer,"resources/gfx/MainChar2.png");running.frame = 0;
    standing.tex = IMG_LoadTexture(renderer,"resources/gfx/Standing.png");standing.frame = 0;
	jumping.tex = IMG_LoadTexture(renderer,"resources/gfx/Jumping.png");jumping.frame = 0;
	shooting.tex = IMG_LoadTexture(renderer,"resources/gfx/Shooting.png");shooting.frame = 0;
	shootup.tex = IMG_LoadTexture(renderer,"resources/gfx/Shootingupward.png");shootup.frame = 0;
	runshootup.tex = IMG_LoadTexture(renderer,"resources/gfx/Runningshotup.png");runshootup.frame = 0;
	diving.tex = IMG_LoadTexture(renderer,"resources/gfx/Diving.png");diving.frame = 0;
	fakewater = IMG_LoadTexture(renderer,"resources/gfx/fakewater2.png");
	life_icon = IMG_LoadTexture(renderer,"resources/gfx/LIFE.png");

}

MainCharacter::~MainCharacter(){
	SDL_DestroyTexture(running.tex);
	SDL_DestroyTexture(standing.tex);
	SDL_DestroyTexture(jumping.tex);
	SDL_DestroyTexture(shooting.tex);
	SDL_DestroyTexture(runshootup.tex);
	SDL_DestroyTexture(diving.tex);
	SDL_DestroyTexture(shootup.tex);
}

void MainCharacter::animationConfig()
{	
	if(end_posc.x >0 && end_posc.y > 0)
	{	
		for(int i = 0;i < 2;i++)
		{
			frame_clip_standing[i].x =end_posc.x*i;
			frame_clip_standing[i].y =0;
			frame_clip_standing[i].w =end_posc.x;
			frame_clip_standing[i].h =end_posc.y;
		}
		for(int i = 0;i < 6 ;i++)
		{
			frame_clip_running[i].x = end_posc.x*i;
			frame_clip_running[i].y = 0;
			frame_clip_running[i].w = end_posc.x;
			frame_clip_running[i].h = end_posc.y;
		}
		for(int i =0;i < 4;i++)
		{
			frame_clip_jumping[i].x = end_posc.x*i;
			frame_clip_jumping[i].y = 0;
			frame_clip_jumping[i].w = end_posc.x;
			frame_clip_jumping[i].h = 41;
		}
		for(int i =0 ; i< 3;i++)
		{
			frame_clip_shooting[i].x = end_posc.x*i;
			frame_clip_shooting[i].y = 0;
			frame_clip_shooting[i].w = end_posc.x;
			frame_clip_shooting[i].h = end_posc.y-5;
		}
		//LOAD shootup
		for(int i = 0;i < 2;i++)
		{
			frame_clip_shootup[i].x = end_posc.x*i;
			frame_clip_shootup[i].y = 0;
			frame_clip_shootup[i].w = end_posc.x;
			frame_clip_shootup[i].h = end_posc.y+20;
		}
		//LOAD run shootup
		for(int i = 0; i < 3;i++)
		{
			frame_clip_runshootup[i].x = end_posc.x*i;
			frame_clip_runshootup[i].y = 0;
			frame_clip_runshootup[i].w = end_posc.x;
			frame_clip_runshootup[i].h = end_posc.y;
		}
		
		for(int i =0;i < 4;i++)
		{
			frame_clip_diving[i].x = end_posc.x*i;
			frame_clip_diving[i].y = 0;
			frame_clip_diving[i].w = end_posc.x;
			frame_clip_diving[i].h = end_posc.y/2;
		}
		waterframe = {0,0,45,60};
		life_frame = {0,0,10,20};
	}
}

void MainCharacter::Display()
{
	if(user_input.left == 1 || user_input.right ==1)
	{
		if(shootimg == true && user_input.up == 0)
		{	
			shooting.frame++;
			running.frame = 0;
		}
		if(!shootimg && user_input.up == 0 )
		{
			running.frame++;
		}
		
		if(user_input.up ==1)
		{
			runshootup.frame++;
		}
	}else{
		if(user_input.up == 1)
		{
			shootup.frame++;
		}else{
			standing.frame++;
		}

	}
	if(underwater)
	{
		diving.frame++;
	}

	if(!on_ground)
	{	
		jumping.frame++;
	}
	if(running.frame >= 30)
		running.frame = 0;
	if(standing.frame >=28)
		standing.frame = 0;
	if(jumping.frame >= 16)
		jumping.frame = 0;
	if(shooting.frame>= 15)
		shooting.frame = 0;
	if(shootup.frame>=28 )
		shootup.frame = 0;
	if(runshootup.frame >= 15)
		runshootup.frame = 0;
	if(diving.frame >= 28)
		diving.frame = 0;
	//cout << shooting.frme << endl;
	if(move_val.x > 0)
	{	
		if(posc.x < gWinWidth/2)
		{
			show_pos.x = posc.x;
		}
		if(posc.x > 8300)
		{
			show_pos.x =  posc.x -7800;
		}
	}else if(move_val.x < 0){
		if(map_pos.x >= -10)
		{
			show_pos.x = posc.x;
		}
		if(posc.x > 8300)
		{
			show_pos.x =  posc.x -7800;
		}
		
	}
	if(respawn_time == 0)
	{
		SDL_Rect*	running_clip = &frame_clip_running[running.frame/5];
		SDL_Rect* stand_clip = &frame_clip_standing[standing.frame/14];
		SDL_Rect* jumping_clip = &frame_clip_jumping[jumping.frame/4];
		SDL_Rect* shooting_clip = &frame_clip_shooting[shooting.frame/5];
		SDL_Rect* shootup_clip = &frame_clip_shootup[shootup.frame/14];
		SDL_Rect* runshootup_clip = &frame_clip_runshootup[runshootup.frame/5];
		SDL_Rect* diving_clip = &frame_clip_diving[diving.frame/14+2];
		end_posc.y = (on_ground) ? 80:41;
		if(underwater)
		{	
			if(!shootimg)
			{
				show_pos.y = posc.y +10;
				showClip =  {(int) show_pos.x, (int) show_pos.y,(int) end_posc.x, (int)end_posc.y/2};
			}else{
				show_pos.y = posc.y;
				showClip =  {(int) show_pos.x, (int) show_pos.y,(int) end_posc.x, (int)end_posc.y};
			}

		}else{
			if(user_input.up == 1 && move_val.x == 0)
			{
				show_pos.y = posc.y-20;
				showClip  = {(int) show_pos.x,(int)show_pos.y,(int) end_posc.x, (int)end_posc.y+20};
			}else {
				show_pos.y = posc.y;
				showClip  = {(int)show_pos.x,(int)show_pos.y,(int) end_posc.x, (int)end_posc.y};
			}
		}
		
		if(status == WALK_RIGHT)
		{	
			if(on_ground)
			{	
				if(!underwater || shootimg)
				{
					if(move_val.x !=0)
					{	
						if(shootimg == true && user_input.up == 0 )
						{	
							SDL_RenderCopy(screen,shooting.tex,shooting_clip,&showClip);
						}
						if(!shootimg && user_input.up == 0 )
						{
							SDL_RenderCopy(screen,running.tex,running_clip,&showClip);
						}
						
						if(user_input.up ==1)
						{	
							SDL_RenderCopy(screen,runshootup.tex,runshootup_clip,&showClip);
						}
						
					}else{
						if(user_input.up == 1)
						{	
							SDL_RenderCopy(screen,shootup.tex,shootup_clip,&showClip);
						}else{
							SDL_RenderCopy(screen,standing.tex,stand_clip,&showClip);
						}
						
					}
					if(underwater)
					{
						SDL_Rect water = showClip;
						water.y+= water.h -45;
						water.x-=2;
						water.w+=2 ;
						SDL_RenderCopy(screen,fakewater,&waterframe,&water);
					}
				}else{
					SDL_RenderCopy(screen,diving.tex,diving_clip,&showClip);
					
				}
				
			}else{
				SDL_RenderCopy(screen,jumping.tex,jumping_clip,&showClip);
				
			}
			
		}else{
			if(on_ground)
			{	
				if( !underwater || shootimg)
				{
					if(move_val.x !=0)
					{	
						if(shootimg == true && user_input.up == 0 )
						{	
							
							SDL_RenderCopyEx(screen,shooting.tex,shooting_clip,&showClip,0,NULL,SDL_FLIP_HORIZONTAL);
						}
						if(!shootimg && user_input.up == 0 )
						{
							SDL_RenderCopyEx(screen,running.tex,running_clip,&showClip,0,NULL,SDL_FLIP_HORIZONTAL);
						}
						
						if(user_input.up == 1)
						{	
							SDL_RenderCopyEx(screen,runshootup.tex,runshootup_clip,&showClip,0,NULL,SDL_FLIP_HORIZONTAL);
						}
						
					}else{
						if(user_input.up == 1)
						{	
							SDL_RenderCopyEx(screen,shootup.tex,shootup_clip,&showClip,0,NULL,SDL_FLIP_HORIZONTAL);
						}else
						{
							SDL_RenderCopyEx(screen,standing.tex,stand_clip,&showClip,0,NULL,SDL_FLIP_HORIZONTAL);
						}
					}
					if(underwater)
					{
						SDL_Rect water = showClip;
						water.y+= water.h -45;
						water.x-=2;
						water.w+=2 ;
						SDL_RenderCopy(screen,fakewater,&waterframe,&water);
					}
				}else{
					SDL_RenderCopyEx(screen,diving.tex,diving_clip,&showClip,0,NULL,SDL_FLIP_HORIZONTAL);
					
				}
				
			}else{
				SDL_RenderCopyEx(screen,jumping.tex,jumping_clip,&showClip,0,NULL,SDL_FLIP_HORIZONTAL);
			}
			
		}
		// SDL_RenderDrawRect(screen,&showClip);
		
	}
	Lives_display();
	
}

void MainCharacter::HandlingUser(SDL_Event event,Map& m,Mix_Chunk* gun_shot)
{	
	if(event.type == SDL_KEYDOWN)
	{	
		switch(event.key.keysym.sym)
		{
			case SDLK_a:
			{	
				status = WALK_LEFT;
				user_input.left =1;
				user_input.right =0;
			}
			break;
			case SDLK_d:
			{
				status = WALK_RIGHT;
				user_input.right =1;
				user_input.left =0;
				
			}
			break;
			case SDLK_s:
			{
				user_input.down = 1;
				
			}
			break;
			case SDLK_SPACE:
			{	
				if(!underwater)
					user_input.Jump = true;
			}
			break;
			case SDLK_w:
			{	
				if(on_ground)
					user_input.up = 1;
			}
			break;
			case SDLK_j:
			{	
				if(user_input.shoot == true && magazine.size() < BULLET_NUMBER )
				{	
					if(gun_hold_time <= 30)
						gun_hold_time+=10;
					shootimg = true;
					Bullet* armor = new Bullet();
					armor = Reload();
					magazine.push_back(armor);
					user_input.shoot = false;
					Mix_PlayChannel(-1,gun_shot,0);
				}
			}
			break;
		}
		
	}else if(event.type == SDL_KEYUP)
	{	
		switch(event.key.keysym.sym)
		{
			case SDLK_a:
			{
				user_input.left =0;
			}
			break;
			case SDLK_d:
			{
				user_input.right =0;
			}
			break;
			// case SDLK_s:
			// {
			// 	user_input.down = 0;
			// }
			// break;
			case SDLK_w:
			{
				user_input.up = 0;
			}
			break;
			case SDLK_j:
			{
				user_input.shoot = true;
				
			}
		}
	}
	
}

void MainCharacter::Movement(map& map_data,Map& map)
{	
	if(respawn_time == 0)
	{
		move_val.x = 0;
		move_val.y += 2;
		if (move_val.y >= MAX_FALL_SPEED)
			move_val.y = MAX_FALL_SPEED;
		
		if(user_input.left == 1)
		{
			move_val.x -=SPEED;
		}else if(user_input.right == 1)
		{
			move_val.x+=SPEED;
		}
		if(user_input.Jump)
		{	
			user_input.up = false;
			if(on_ground)
			{
				move_val.y = -JUMPPXL;
			}
			on_ground = false;
			user_input.Jump = false;
		}
		if(user_input.down == 1)
		{	
			posc.y+=move_val.y+1;
		}
		HandleMoveandMap(map_data,map);
	}
	if(respawn_time > 0)
	{
		respawn_time--;
		
		if(respawn_time ==0)
		{
			posc.y = 0;
			move_val.x = 0;
			move_val.y = 0;
		}
	}
	
	
}


void MainCharacter::HandleMoveandMap(map& map,Map& mapfull)
{
	int x1;
	int x2;
	int y1;
	int y2;
	int minWidth = end_posc.x < TILE_SIZE ? end_posc.x: TILE_SIZE;
	x1 = posc.x/TILE_SIZE;
	x2 = (posc.x+minWidth	)/TILE_SIZE;
	y1 = (posc.y + move_val.y)/TILE_SIZE;
	y2 = (posc.y + move_val.y + end_posc.y-1)/TILE_SIZE;
	// CHECK VERTICAL
	int standard_height = 80;

	if(x1 >= 0 && x2 < MAX_MAP_X && y1 >=0 && y2 < 8)
	{	
		if(move_val.y > 0)
		{	
			if(map.Tiles[y2][x1] == 1 || map.Tiles[y2][x2] == 1)
			{	
				int top_tile = y2*TILE_SIZE;
				if(posc.y + end_posc.y <= top_tile|| map.Tiles[y2][x1] == 3 || map.Tiles[y2][x2] == 3)
				{	
					posc.y = top_tile;
					posc.y -= standard_height+1;
					move_val.y = 0;
					on_ground = true;
					underwater = false;
				}
				
			}else if(map.Tiles[y2][x1] == 2 || map.Tiles[y2][x2] == 2)
			{	
				int top_tile = y2*TILE_SIZE+TILE_SIZE/2;
				if(posc.y + end_posc.y <= top_tile)
				{	
					
					posc.y = top_tile;
					posc.y -= standard_height + 1;
					move_val.y = 0;
					on_ground = true;
					underwater = false;
				}
			}else if(map.Tiles[y2][x1] == 3 || map.Tiles[y2][x2] == 3 )
			{
				int top_tile = y2*TILE_SIZE + TILE_SIZE/2;
				if(posc.y + end_posc.y + move_val.y>= top_tile)
				{	
					
					posc.y = top_tile;
					posc.y -= standard_height ;
					move_val.y = 0;
					on_ground = true;
					underwater = true;
				}
			}
		}
	}
	if(respawn_time == 0)
	{
		posc.x += move_val.x;
		posc.y += move_val.y;
	}

	// centering map around char
	if(move_val.x < 0)
	{
		if(mapfull.getPos().x < -10 && posc.x <= 8300)
		{	
			mapfull.getPos().x += SPEED;
		}
	}else if( move_val.x > 0)
	{
		if(posc.x >= gWinWidth/2 && mapfull.getPos().x >= -7800 )
		{
			mapfull.getPos().x -= SPEED;
		}
	}
	//cout << posc.x << " " << show_pos.x << " " << mapfull.getPos().x << endl;

	if(posc.x < 0)
	{
		posc.x = 0;
	}else if(posc.x + end_posc.x > map.max_x){
		posc.x = map.max_x - end_posc.x;

	}
	if( posc.y >map.max_y)
	{
		respawn_time = 50;
		Life--;
		//move_val.x = 0;
	}
	if(on_ground)
	{
		user_input.down = 0;
	}
	
}  


void MainCharacter::Fire()
{
	gun_hold_time--;

	if(gun_hold_time < 0)
		gun_hold_time = 0;
	if(gun_hold_time <= 0)
		shootimg = false;

	for(int i =0;i < magazine.size();i++)
	{
		Bullet* armor = magazine[i];
		if(armor != NULL)
		{	
			if(armor->getStatus())
			{	
				armor->HandleBullet(gWinWidth,gWinHeight,move_val.x,posc.x);
				armor->Draw(screen);
			}else
			{	
				magazine.erase(magazine.begin()+i);
				
				if(armor != NULL)
				{
					delete armor;
					armor = NULL;
				}
			}
			
		}
	}
}
void MainCharacter::removeBullet(const int& indx)
{
	int size = magazine.size();
	if(size >0 && indx < size)
	{	

		Bullet* armor = magazine[indx];
		magazine.erase(magazine.begin()+indx);
		if(armor)
		{
			delete armor;
			armor = NULL;
		}
	
	}
}
Bullet* MainCharacter::Reload()
{	
	Bullet* armor;
	if(user_input.up == 1 && on_ground)
	{	
		if(move_val.x > 0)
		{
			armor->set_bullet_dir(Bullet::DIR_UP_RIGHT);
			armor->setPos(show_pos.x + end_posc.x-10,show_pos.y+5);
		}else if(move_val.x <0)
		{
			armor->set_bullet_dir(Bullet::DIR_UP_LEFT);
			armor->setPos(show_pos.x,show_pos.y+5);
		}else{
			armor->set_bullet_dir(Bullet::DIR_UP);
			armor->setPos(show_pos.x + end_posc.x/2-5,show_pos.y+5);
		}
		
	}
	if(status == WALK_LEFT && user_input.up == 0)
	{
		armor->set_bullet_dir(Bullet::DIR_LEFT);
		armor->setPos(show_pos.x,posc.y+end_posc.y*0.3);
	}else if(status ==WALK_RIGHT && user_input.up == 0)
	{
		armor->set_bullet_dir(Bullet::DIR_RIGHT);
		armor->setPos(show_pos.x+end_posc.x,posc.y+end_posc.y*0.3);
	}
	armor->setType(Bullet::RED_BULLET,screen);
	armor->setX(BULLET_SPEED);
	armor->setY(BULLET_SPEED);
	armor->shoot(true);
	return armor;
}

void MainCharacter::Lives_display()
{
	for(int i = 1 ; i < Life;i++)
	{
		SDL_Rect showLife = {i*30,30,15,30};
		SDL_RenderCopy(screen,life_icon,&life_frame,&showLife);
	}
}