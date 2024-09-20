#include <stdbool.h>
#include "../lib/raylib/src/raylib.h"
#include "game.h"
#include "assets.h"
#include "log.h"

#define MAXWIDTH 128
#define MAXHEIGHT 128

#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H
#endif


enum tileTypes {
    GROUND_FLAT = 1,
    GROUND_ELEVATE = 2,
    GROUND_SHADOW = 3,
    WATER = 4,
    WATER_ROCK1 = 5,
    WATER_ROCK2 = 6,
    WATER_ROCK3 = 7,
	WATER_ROCK4 = 8
};


const char* tilePaths[] = {
	"",
    "assets/Terrain/Ground/Tilemap_Flat.png",
    "assets/Terrain/Ground/Tilemap_Elevation.png",
    "assets/Terrain/Ground/Shadows.png",
    "assets/Terrain/Water/Water.png",
    "assets/Terrain/Water/Rocks/Rocks_01.png",
    "assets/Terrain/Water/Rocks/Rocks_02.png",
    "assets/Terrain/Water/Rocks/Rocks_03.png",
	"assets/Terrain/Water/Rocks/Rocks_04.png"
};

typedef struct {
	int *AssetPtr;
	int tiles[128][128];
} Tilemap ;

typedef struct {
	int difficulty;
	int waves;
	Tilemap tilemap;
} Scene;

//================================================================================

const char[] getTilePath(int tileType) {
    return tilePaths[tileType];
}

//================================================================================

void scene_initialize(int difficulty, int waves) {
	Scene newScene;
	newScene.difficulty = difficulty;
	newScene.waves = waves;f
	scene_populate(newScene);
}
//================================================================================
void scene_populate(Scene newScene)
{
for(int i=0; i < MAXHEIGHT; i++)
	{
	for(int j=0; j < MAXWIDTH; j++)
		{
		BeginDrawing();
		newScene.tilemap.AssetPtr = assets_get(getTilePath(newScene.tilemap.tiles[i][j]));
		DrawTexture(newScene.tilemap.AssetPtr->data.texture, i, j, WHITE);
		EndDrawing();
		}
	}
}
//================================================================================