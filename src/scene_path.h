#ifndef SCENE_PATH_H
#define SCENE_PATH_H

#include "assets.h"
#include "scene_builder.h"

void gen_random_path(Scene *scene);
void path_right(Scene *scene, int *anchor, int distance, char *last, char *new);
int anchor_turn(Scene *scene, int *anchor, char *last, char *new);
void path_up(Scene *scene, int *anchor, int distance, char *last, char *new);
void path_down(Scene *scene, int *anchor, int distance, char *last, char *new);

#endif