#include <stdbool.h>
#include "../lib/raylib/src/raylib.h"
#include "scene_builder.h"
#include "game.h"
#include "assets.h"
#include "log.h"

const char* TilePaths[] = {
	"",
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

void scene_draw(Scene *scene, int x, int y)
{

Vector2 tile_tex_coords[6] = {
	(Vector2){0,0},
	(Vector2){32,0},
	(Vector2){64,0},
};

int xp = x * 32;
int yp = y * 32;
Vector2 tex_coords = tile_tex_coords[scene->tilemap.tiles[y][x]];

DrawTextureRec(
scene->tilemap.asset_ptr->data.texture,
(Rectangle){tex_coords.x, tex_coords.y,32,32},
(Vector2){xp, yp},
WHITE
);
}


void scene_populate(Scene NewScene)
{
for(int y=0; y<MAXHEIGHT; y++)
	{
	for(int x=0; x<MAXWIDTH; x++)
		{
		NewScene.tilemap.tiles[y][x] = GetRandomValue(1,9);
		int TileNumber = NewScene.tilemap.tiles[y][x];
		const char *path = get_tile_file_path(TileNumber);
		NewScene.tilemap.asset_ptr = assets_get(path);
		Scene *ptr;
		ptr = &NewScene;
		scene_draw(ptr, x, y);
		}
	}
}

void scene_initialize(int difficulty) {
	Scene NewScene;
	NewScene.difficulty = difficulty;
	scene_populate(NewScene);
}
