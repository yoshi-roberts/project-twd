#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "assets.h"

#define MAXWIDTH 30
#define MAXHEIGHT 17
#define MAXTILES (MAXWIDTH * MAXHEIGHT)
#define TILESIZE 16

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
	int tiles[MAXHEIGHT][MAXWIDTH];
} Tilemap;


typedef struct {
	int difficulty;
	int waves;
	Tilemap tilemap;
} Scene;

Scene scene_initialize(int difficulty, const char* path);
void scene_draw(Scene *scene);
void tileval_from_file(const char *filename, int (*arr)[MAXWIDTH]);



#endif