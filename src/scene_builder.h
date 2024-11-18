#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "tilemap.h"
#include "assets.h"
#include "unit.h"

enum GameState {
	STATE_BUILD = 0,
	STATE_PLAY = 1,
	STATE_COMPLETE = 2,
	STATE_LOSE = 3,
	STATE_WIN = 4 
};

typedef struct {
	int difficulty;
	int waves;
	int scene_state;
	Unit units[TILEMAP_HEIGHT][TILEMAP_WIDTH];
	Tilemap tilemap_layer1;
    Tilemap tilemap_layer2;
} Scene;

Scene scene_init(int difficulty, const char* path);
void scene_draw(Scene *scene);
void scene_randomize(Scene *scene);
void gen_treeline(Scene *scene);
void build_tree(Scene *scene, int anchor[]);
void scene_state_set(Scene *scene, int state);
int scene_state_get(Scene *scene);

#endif
