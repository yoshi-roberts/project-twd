#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/raylib/src/raylib.h"
#include "scene_builder.h"
#include "assets.h"

void gen_random_path(Scene *scene, int difficulty){

int anchor[2]={8,1};
scene->tilemap.tiles[anchor[0]][anchor[1]]=5;

int UpOrDown = GetRandomValue(1,2);
int distance = GetRandomValue(1,8);
}

void path_right(Scene *scene, int *anchor, int distance){
if (scene->tilemap.tiles[anchor[0]+1][anchor[1]] > 3 || scene->tilemap.tiles[anchor[0]+1][anchor[1]] > 8 )

}