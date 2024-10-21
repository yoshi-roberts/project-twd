#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "assets.h"

#define TILEMAP_WIDTH 30
#define TILEMAP_HEIGHT 17
#define MAXTILES (MAXWIDTH * MAXHEIGHT)
#define TILESIZE 16

enum TileTypes {
	TILE_GRASS = 0,
	TILE_GRASS_TALL = 1,
	TILE_GRASS_ROCK = 2,
	TILE_ROCK = 3,
	TILE_PATH_UP_RIGHT = 4,
	TILE_PATH_H = 5,
	TILE_PATH_RIGHT_DOWN = 6,
	TILE_PATH_V = 7,
	TILE_PATH_DOWN_RIGHT = 8,
	TILE_PATH_RIGHT_UP = 9,
};

typedef struct {
	Asset *asset_ptr;
	int tiles[TILEMAP_HEIGHT][TILEMAP_WIDTH];
} Tilemap;


typedef struct {
	int difficulty;
	int waves;
	Tilemap tilemap;
} Scene;

Scene scene_init(int difficulty, const char* path);
void scene_draw(Scene *scene);
void tileval_from_file(const char *filename, int (*arr)[TILEMAP_WIDTH]);
void scene_randomize(Scene *scene);

#endif
