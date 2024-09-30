#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/raylib/src/raylib.h"
#include "scene_builder.h"
#include "game.h"
#include "assets.h"
#include "log.h"	



void tileval_from_file(const char *filename, int (*tiles)[MAXWIDTH]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
    }

	int num;
	for(int y=0; y<MAXHEIGHT; y++)
	{
	for(int x=0; x<MAXWIDTH; x++)
		{
		fscanf(file, "%d,", &num);
		tiles[y][x] = num;
		}
	}
    fclose(file);
}



void scene_draw(Scene *scene)
{
Vector2 tile_tex_coords[6] = {
	(Vector2){0,0},
	(Vector2){16,0},
	(Vector2){32,0},
	(Vector2){48,0},
};

	for(int y=0; y<MAXHEIGHT; y++)
	{
	for(int x=0; x<MAXWIDTH; x++)
		{
		int tile = scene->tilemap.tiles[y][x];
		int xp = x * TILESIZE;
		int yp = y * TILESIZE;
		Vector2 tex_coords = tile_tex_coords[tile];
			DrawTextureRec(
			scene->tilemap.asset_ptr->data.texture,
			(Rectangle){tex_coords.x, tex_coords.y,TILESIZE,TILESIZE},
			(Vector2){xp, yp},
			WHITE
			);
		}
	}
}


Scene scene_initialize(int difficulty, const char* path) {
	Scene NewScene;
	NewScene.difficulty = difficulty;
	//NewScene.tilemap.tiles[y][x] = GetRandomValue(0,3); // If you want to randomize
	tileval_from_file("src/numbers.txt", NewScene.tilemap.tiles);
	NewScene.tilemap.asset_ptr = assets_get(path);
	return NewScene;
}
