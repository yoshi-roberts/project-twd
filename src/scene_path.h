#ifndef SCENE_PATH_H
#define SCENE_PATH_H

#include "assets.h"
#include "scene_builder.h"

void gen_random_path(Scene *scene);
void gen_section(Scene *scene, int *anchor, char *last, char *new);
int check_for_edge(int *anchor, int distance, int UpOrDown);
void path_right(Scene *scene, int *anchor, int distance, char *last, char *new);
void path_up(Scene *scene, int *anchor, int distance, char *last, char *new);
void path_down(Scene *scene, int *anchor, int distance, char *last, char *new);
int anchor_turn(char *last, char *new);
char set_last(char *last, char *new);

#endif