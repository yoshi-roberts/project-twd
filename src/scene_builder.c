#include <stdbool.h>
#include "../lib/raylib/src/raylib.h"
#include "scene_builder.h"
#include "game.h"
#include "assets.h"
#include "log.h"

const char* TilePaths[] = {
    "assets/Terrain/Ground/Tilemap_Flat.png",
    "assets/Terrain/Ground/Tilemap_Elevation.png",
    "assets/Terrain/Ground/Shadows.png",
    "assets/Terrain/Water/Water.png",
    "assets/Terrain/Water/Rocks/Rocks_01.png",
    "assets/Terrain/Water/Rocks/Rocks_02.png",
    "assets/Terrain/Water/Rocks/Rocks_03.png",
	"assets/Terrain/Water/Rocks/Rocks_04.png",
	"assets/Terrain/Bridge/Bridge_All.png"
};


const char* get_tile_file_path(int TileType) 
{
	return TilePaths[TileType];
}		

void scene_draw(Scene *scene)
{
Vector2 tile_tex_coords[6] = {
	(Vector2){0,0},
	(Vector2){32,0},
	(Vector2){64,0},
};

	for(int y=0; y<MAXHEIGHT; y++)
	{
	for(int x=0; x<MAXWIDTH; x++)
		{
		int tile = scene->tilemap.tiles[y][x];
		int xp = x * 32;
		int yp = y * 32;
		Vector2 tex_coords = tile_tex_coords[tile];
			DrawTextureRec(
			scene->tilemap.asset_ptr->data.texture,
			(Rectangle){tex_coords.x, tex_coords.y,32,32},
			(Vector2){xp, yp},
			WHITE
			);
		}
	}

}


Scene scene_initialize(int difficulty, const char* path) {

	Scene NewScene;
	NewScene.difficulty = difficulty;

	for(int y=0; y<MAXHEIGHT; y++)
	{
	for(int x=0; x<MAXWIDTH; x++)
		{
		NewScene.tilemap.tiles[y][x] = GetRandomValue(0,8);
		}
	}
	NewScene.tilemap.asset_ptr = assets_get(path);
	return NewScene;
}
