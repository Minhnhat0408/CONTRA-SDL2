#include<iostream>
#include<stdio.h>
#include "Map.hpp"

using namespace std;



Map::Map(Vector2f p_pos, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 8834;
    currentFrame.h = 640;
	direction = 0;

}

void Map::draw(SDL_Renderer* renderer)
{	
    SDL_Rect src; 
	src.x = currentFrame.x;
	src.y = currentFrame.y;
	src.w = currentFrame.w;
	src.h = currentFrame.h;

	SDL_Rect dst;
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = currentFrame.w;
	dst.h = currentFrame.h;
    SDL_RenderCopy(renderer,tex,&src,&dst);
}

void Map::LoadMap(const char* namefile)
{
	FILE* fp = NULL;
	fopen_s(&fp, namefile, "rb");
	if(fp == NULL) {
		return;
	}

	game_map.max_x = 0;
	game_map.max_y = 0;
	for(int i = 0; i < MAX_MAP_Y; i++) {
		for(int j = 0; j < MAX_MAP_X; j++) {
			fscanf(fp, "%d", &game_map.Tiles[i][j]);
			int val = game_map.Tiles[i][j];
			if(val > 0) {
				if(j > game_map.max_x) {
					game_map.max_x = j;
				}
				if(i > game_map.max_y) {
					game_map.max_y = i;
				}
			}
		}
	}
	game_map.max_x = (game_map.max_x + 1)*TILE_SIZE;
	game_map.max_y = (game_map.max_y + 1)*TILE_SIZE;

}




	

