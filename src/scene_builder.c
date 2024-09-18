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

void scene_initialize(int difficulty, int waves) {
	Scene newScene;
	newScene.difficulty = difficulty;
	newScene.waves = waves;

}

void scene_populate()
{





}
