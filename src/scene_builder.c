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
	"assets/Terrain/Water/Rocks/Rocks_04.png"
	"assets/Terrain/Bridge/Bridge_All.png"
};


const char* Get_Tile_File_Path(int TileType) {
    return TilePaths[TileType];
}


void scene_initialize(int difficulty) {
	Scene NewScene;
	NewScene.difficulty = difficulty;
	scene_populate(NewScene);
}


void scene_populate(Scene NewScene)
{
for(int i=0; i < MAXHEIGHT; i++)
	{
	for(int j=0; j < MAXWIDTH; j++)
		{
		BeginDrawing();
		NewScene.tilemap.AssetPtr = assets_get(Get_Tile_File_Path(NewScene.tilemap.tiles[i][j]));
		DrawTexture(NewScene.tilemap.AssetPtr->data.texture, i, j, WHITE);
		EndDrawing();
		}
	}
}
