#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/raylib/src/raylib.h"
#include "scene_builder.h"
#include "scene_path.h"
#include "assets.h"

void tileval_from_file(const char *filename, int (*tiles)[TILEMAP_WIDTH]) {

	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		printf("Error opening file.\n");
	}

	int num;
	for(int y=0; y<TILEMAP_HEIGHT; y++) {

		for(int x=0; x<TILEMAP_WIDTH; x++) {

			fscanf(file, "%d,", &num);
			tiles[y][x] = num;
		}
	}

	fclose(file);
}



void scene_draw(Scene *scene)
{
	Vector2 tile_tex_coords[10] = {
		(Vector2){0,0},
		(Vector2){16,0},
		(Vector2){32,0},
		(Vector2){48,0},
		(Vector2){64,0},
		(Vector2){80,0},
		(Vector2){96,0},
		(Vector2){112,0},
		(Vector2){0,16},
		(Vector2){16,16}
	};

	for(int y=0; y<TILEMAP_HEIGHT; y++) {

		for(int x=0; x<TILEMAP_WIDTH; x++) {

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

	Scene scene;
	scene.difficulty = difficulty;
	// tileval_from_file("src/numbers.txt", NewScene.tilemap.tiles);

	scene_randomize(&scene);

	scene.tilemap.asset_ptr = assets_get(path);
	return scene;
}

void scene_randomize(Scene *scene) {

	for (int y = 0; y < TILEMAP_HEIGHT; y++) {
		for (int x = 0; x < TILEMAP_WIDTH; x++) {

			//if (y == 8) {
				//scene->tilemap.tiles[y][x] = 5;
			//} else {

				int r = GetRandomValue(0, 10);
				if (r <= 4) {
					scene->tilemap.tiles[y][x] = 0;
				} else if (r > 4 && r <= 8) {
					scene->tilemap.tiles[y][x] = 1;
				} else if (r > 8 && r <= 9) {
					scene->tilemap.tiles[y][x] = 2;
				} else if (r == 10) {
					scene->tilemap.tiles[y][x] = 3;
				}
			//}

		}
	}
	gen_random_path(scene);
}
