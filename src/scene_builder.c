#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

typedef struct {
	Asset* tileset;
	int tile_size;
	int tiles[128][128];
} Tilemap ;

typedef struct {
	int difficulty;
	int waves;
	Tilemap tilemap;
} Scene;

struct scene_initialize(int difficulty, int waves) {
	struct newScene;
	newScene.difficulty = difficulty;
	newScene.waves = waves;
	return newScene;
}
