#ifndef TILEMAP_H
#define TILEMAP_H

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
    TILE_TREE_1 = 16,
    TILE_TREE_2 = 17,
    TILE_TREE_3 = 24,
    TILE_TREE_4 = 25,
    TILE_TREE_5 = 32,
    TILE_TREE_6 = 33
};

typedef struct {
	Asset *asset_ptr;
	int tiles[TILEMAP_HEIGHT][TILEMAP_WIDTH];
	Vector2 waypoints[30];
    int last_waypoint_index;
} Tilemap;

#endif
