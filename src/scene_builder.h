#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "assets.h"
#include "tilemap.h"

Scene scene_init(int difficulty, const char* path);
void scene_draw(Scene *scene);
void scene_randomize(Scene *scene);
void gen_treeline(Scene *scene);
void build_tree(Scene *scene, int anchor[]);
#endif
