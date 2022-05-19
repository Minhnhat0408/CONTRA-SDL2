#include"Enemy.hpp"
using namespace std;

Enemy::Enemy()
{
    pos.x = 0;
    pos.y = 0;
    move_val.x  = 0;
    move_val.y = 0;
	frequency = 0;
	end_pos.y = 75;
    on_ground = true;
    terminated = false;
	Status_type.left = 1;
	Status_type.Jump = 0;
	Status_type.right = 0;
	move_back = true;
	//head_back = true;
}
Enemy::~Enemy()
{
	SDL_DestroyTexture(Clips.tex);
}
void Enemy::LoadTexture(SDL_Renderer* renderer)
{	
	if(type_enemy == TROOP)
	{	
		Life = 1;
		Clips.frame = 0;
		Clips.tex = IMG_LoadTexture(renderer,"resources/gfx/TROOP.png");
		end_pos.x = 40;
    	end_pos.y = 76;
	}else if(type_enemy == TANK)
	{	
		Life = 6;
		Clips.frame = 0;
		Clips.tex = IMG_LoadTexture(renderer,"resources/gfx/TANK2.png");
		end_pos.x = 110;
    	end_pos.y = 80;
	}
	if(Clips.tex== NULL)
    {
        cout << SDL_GetError() << endl;
    }

}
void Enemy::animationConfig()
{	
	if(type_enemy == TROOP)
	{
		if(end_pos.x >0 && end_pos.y > 0)
		{
			for(int i  =0 ; i < 6;i++)
			{
				frame_clip_troop[i].x = i*end_pos.x;
				frame_clip_troop[i].y = 0;
				frame_clip_troop[i].w = end_pos.x;
				frame_clip_troop[i].h = end_pos.y;
			}
		}
	}else{
		if(end_pos.x >0 && end_pos.y > 0)
		{
			for(int i  =0 ; i < 4;i++)
			{
				frame_clip_tank[i].x = i*end_pos.x;
				frame_clip_tank[i].y = 0;
				frame_clip_tank[i].w = end_pos.x;
				frame_clip_tank[i].h = end_pos.y;
			}
		}
	}
    
}

void Enemy::Display(SDL_Renderer* renderer)
{
	Clips.frame++;
	if(Clips.frame >= 16)
	{
		Clips.frame = 0;
	}
	SDL_Rect* clip;
	if(type_enemy == TROOP)
	{
		clip = &frame_clip_troop[Clips.frame/4];
	}else{
		clip = &frame_clip_tank[Clips.frame/4];
		
	}
	showClip = {(int) (pos.x+map_pos.x),(int) pos.y,(int) end_pos.x,(int) end_pos.y };
	if(Status_type.right == 1)
	{
		SDL_RenderCopy(renderer,Clips.tex,clip,&showClip);
	}else{
		SDL_RenderCopyEx(renderer,Clips.tex,clip,&showClip,0,NULL,SDL_FLIP_HORIZONTAL);
	}
	
}


void Enemy::Movement(map& map_data,Map& map)
{

	move_val.x = 0;
	move_val.y+= 2;
	if(move_val.y >= MAX_FALL_SPEED)
	{
		move_val.y = MAX_FALL_SPEED;
	}
	if(type_enemy == TROOP)
	{
		if(Status_type.left == 1)
		{
			move_val.x-= SPEED;
		}else if(Status_type.right == 1)
		{
			move_val.x += SPEED;
		}
		if(Status_type.Jump)
		{
			if(on_ground)
			{
				move_val.y -= (JUMPPXL);
			}
			on_ground = false;
			Status_type.Jump = false;
		}
	}
	frequency++;
	if(frequency >9)
	{
		frequency = 0;
	}
	HandleMoveandMap(map_data,map);

}

void Enemy::HandleMoveandMap(map& map,Map& mapfull)
{
	int x1;
	int x2;
	int y1;
	int y2;
	int minWidth = end_pos.x < TILE_SIZE ? end_pos.x: TILE_SIZE;
	x1 = (pos.x - move_val.x)/TILE_SIZE;
	x2 = (pos.x+minWidth +move_val.x	)/TILE_SIZE;
	y1 = (pos.y + move_val.y)/TILE_SIZE;
	y2 = (pos.y + move_val.y + end_pos.y-1)/TILE_SIZE;
	// CHECK VERTICAL
	int standard_height = end_pos.y;

	if(x1 >= 0 && x2 < MAX_MAP_X && y1 >=0 && y2 < 8)
	{	
		if(move_val.y > 0)
		{	
			if(map.Tiles[y2][x1] == 1 && map.Tiles[y2][x2] == 1)
			{	
				
				int top_tile = y2*TILE_SIZE;
				if(pos.y + end_pos.y <= top_tile)
				{	
					pos.y = top_tile;
					pos.y -= standard_height+1;
					move_val.y = 0;
					on_ground = true;
					head_back = true;

				}
				
			}else if((map.Tiles[y2][x1] != 1 && map.Tiles[y2][x2] == 1) || (map.Tiles[y2][x1] == 1 && map.Tiles[y2][x2] != 1)   )
			{	
				int top_tile = y2*TILE_SIZE;
				if(pos.y + end_pos.y <= top_tile)
				{	
					pos.y = top_tile;
					pos.y -= standard_height+1;
					move_val.y = 0;
					on_ground = true;
				}
				if(type_enemy == TROOP)
				{	
					if(move_back == false)
					{
						Status_type.Jump = 1;
					}else if(move_back == true && head_back)
					{
						
						if(Status_type.left == 1 && Status_type.right == 0 )
						{
							Status_type.right = 1;
							Status_type.left = 0;
						}else if(Status_type.right == 1 && Status_type.left == 0)
						{
							Status_type.right = 0;
							Status_type.left = 1;
						}
						head_back = false;

					}
				}
			}
			else if(map.Tiles[y2][x1] == 2 && map.Tiles[y2][x2] == 2)
			{	
				int top_tile = y2*TILE_SIZE+TILE_SIZE/2;
				if(pos.y + end_pos.y <= top_tile)
				{	
					
					pos.y = top_tile;
					pos.y -= standard_height + 1;
					move_val.y = 0;
					on_ground = true;
					head_back = true;
				}
			}else if((map.Tiles[y2][x1] != 2 && map.Tiles[y2][x2] == 2) || (map.Tiles[y2][x1] == 2 && map.Tiles[y2][x2] != 2))
			{	
				int top_tile = y2*TILE_SIZE + TILE_SIZE/2;
				if(pos.y + end_pos.y <= top_tile)
				{	
					pos.y = top_tile;
					pos.y -= standard_height+1;
					move_val.y = 0;
					on_ground = true;
				}
				if(type_enemy == TROOP)
				{	
					
					if(move_back == false)
					{
						Status_type.Jump = 1;
					}else if(move_back == true && head_back)
					{
						
						if(Status_type.left == 1 && Status_type.right == 0)
						{
							Status_type.right = 1;
							Status_type.left = 0;
						}
						if(Status_type.left == 0 && Status_type.right == 1)
						{
							Status_type.right = 0;
							Status_type.left = 1;
						}
						head_back = false;

					}
				}
			}
		}
	}
	
	pos.x += move_val.x;
	pos.y += move_val.y;

	if(pos.x < 0)
	{	
		terminated = true;
	}else if(pos.x + end_pos.x > map.max_x){
		terminated = true;

	}
	if( pos.y > 500)
	{
		terminated = true;
		move_val.x = 0;
	}
	
}

void Enemy::PathGuidance(MainCharacter& contra)
{
	if(type_enemy == TROOP)
	{	
		if( pos.x - contra.getPos().x < 300 && pos.x - contra.getPos().x > -300 )
			move_back = false;
		if(move_back == false)
		{	
			if(pos.x - contra.getPos().x < 300 && contra.getPos().x  - pos.x >=0)
			{
				Status_type.right = 0;
				Status_type.left = 1;
			}// }else if(pos.x - contra.getPos().x >= 0 && contra.getPos().x  - pos.x < 300)
			// {
			// 	Status_type.right = 0;
			// 	Status_type.left = 1;
			// }
		}
	}
}


void Enemy::Init_armor(SDL_Renderer* renderer,Bullet* armor,MainCharacter& contra)
{	if(armor != NULL)
	{	
		Vector2f pos_center_player= contra.getShowPos() + 20;
		armor->setType(Bullet::WHITE_BULLET,renderer);
		armor->shoot(true);
		armor->setPos(pos.x +end_pos.x/2 + map_pos.x,pos.y );
		armor->set_bullet_dir(Bullet::AUTO);
		armor->AutoAim(pos_center_player);
		magazine.push_back(armor);
	}
	
}

void Enemy::MakeBullet(SDL_Renderer* renderer,const int& x_limit,const int& y_limit,const double& move_VAL,Vector2f& posc)
{	
	for(int i = 0;i < magazine.size();i++)
	{
		Bullet* armor = magazine[i];
		if(armor != NULL)
		{
			if(armor->getStatus())
			{ 	
				double bullet_distance = pos.x + end_pos.x/2 - posc.x ;
				if(abs(bullet_distance) <= 1000 && abs(bullet_distance) >=0)
				{
					armor->HandleBullet(x_limit+50,y_limit,move_VAL,posc.x);
					armor->Draw(renderer);
				}else{
					armor->shoot(false);
				}
				
			}else{
				
				delete armor;
				armor = NULL;
				magazine.erase(magazine.begin()+i);
			}
		}
	}
}

void Enemy::removeBullet(const int& indx)
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
		//cerr << size << " " << indx << endl;
	}
}
