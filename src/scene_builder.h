#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "tilemap.h"
#include "assets.h"
#include "unit.h"

typedef struct {
	int difficulty;
	int waves;
	Unit units[TILEMAP_HEIGHT][TILEMAP_WIDTH];
	Tilemap tilemap_layer1;
    Tilemap tilemap_layer2;
} Scene;

Scene scene_init(int difficulty, const char* path);
void scene_draw(Scene *scene);
void scene_randomize(Scene *scene);
void gen_treeline(Scene *scene);
void build_tree(Scene *scene, int anchor[]);

#endif
