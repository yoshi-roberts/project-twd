#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/raylib/src/raylib.h"
#include "scene_builder.h"
#include "scene_path.h"
#include "assets.h"

void gen_random_path(Scene *scene){
    int anchor[2]={8,1};
    char last = 'L';
    char new = 'L';
    scene->tilemap.tiles[anchor[0]][anchor[1]] = 5;

    int UpOrDown = GetRandomValue(1,2);
    int distance = GetRandomValue(1,8);

    path_right(scene, anchor, distance, &last, &new);
    path_up(scene, anchor, distance, &last, &new);
    path_right(scene, anchor, distance, &last, &new);
    path_down(scene, anchor, distance, &last, &new);
    path_right(scene, anchor, distance, &last, &new);
}

void path_right(Scene *scene, int *anchor, int distance, char *last, char *new){
    *new = 'R';
    scene->tilemap.tiles[anchor[0]][anchor[1]] = anchor_turn(scene, anchor, last, new); 
        for(int i=0 ; i<=distance ; i++)
        {
        scene->tilemap.tiles[anchor[0]][anchor[1]+1] = 5;
        anchor[1] = anchor[1]+1;
        }
}

void path_up(Scene *scene, int *anchor, int distance, char *last, char *new){
    
    *new = 'U';
    scene->tilemap.tiles[anchor[0]][anchor[1]] = anchor_turn(scene, anchor, last, new);
    for(int i=0 ; i<=distance ; i++)
    {
    scene->tilemap.tiles[anchor[0]-1][anchor[1]] = 7;
    anchor[0] = anchor[0]-1;
    }
}

void path_down(Scene *scene, int *anchor, int distance, char *last, char *new){
    
    *new = 'D';
    scene->tilemap.tiles[anchor[0]][anchor[1]] = anchor_turn(scene, anchor, last, new);
    for(int i=0 ; i<=distance ; i++)
    {
    scene->tilemap.tiles[anchor[0]+1][anchor[1]] = 7;
    anchor[0] = anchor[0]+1;
    }
}

int anchor_turn(Scene *scene, int *anchor, char *last, char *new){
    int BendType;
        if (*last == 'L' && *new == 'R')
        {BendType = 5;}
        else if (*last == 'L' && *new == 'U')
        {BendType = 9;}
        else if (*last == 'L' && *new == 'D')
        {BendType = 6;}
        else if (*last == 'D' && *new == 'R')
        {BendType = 8;}
        else if (*last == 'U' && *new == 'R')
        {BendType = 4;}
        else
        {BendType = 3;}
        
        return BendType;
}
