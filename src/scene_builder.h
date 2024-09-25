#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#define MAXWIDTH  17
#define MAXHEIGHT  9

#include "assets.h"

enum TileTypes {
    GROUND_FLAT = 1,
    GROUND_ELEVATE = 2,
    GROUND_SHADOW = 3,
    WATER = 4,
    WATER_ROCK1 = 5,
    WATER_ROCK2 = 6,
    WATER_ROCK3 = 7,
	WATER_ROCK4 = 8,
	BRIDGE = 9
};

typedef struct {
	Asset *asset_ptr;
	int tiles[128][128];
} Tilemap;


typedef struct {
	int difficulty;
	int waves;
	Tilemap tilemap;
} Scene;

void scene_initialize(int difficulty);
void scene_populate(Scene NewScene);
const char* get_tile_file_path(int TileType);



#endif