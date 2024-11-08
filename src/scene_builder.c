#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/raylib/src/raylib.h"
#include "scene_builder.h"
#include "scene_path.h"
#include "assets.h"
#include "unit.h"
#include "tilemap.h"

void scene_draw(Scene *scene) {

	for(int y=0; y<TILEMAP_HEIGHT; y++) {

		for(int x=0; x<TILEMAP_WIDTH; x++) {

            int tile1 = scene->tilemap_layer1.tiles[y][x];
            int tile2 = scene->tilemap_layer2.tiles[y][x];
			int xp = x * TILESIZE;
			int yp = y * TILESIZE;

            asset_draw_tile(scene->tilemap_layer1.asset_ptr, tile1, xp, yp);  // Draw layer 1
            asset_draw_tile(scene->tilemap_layer2.asset_ptr, tile2, xp, yp);  // Draw layer 2 (trees)
		}
	}

	for(int y=0; y<TILEMAP_HEIGHT; y++) {
		for(int x=0; x<TILEMAP_WIDTH; x++) {

			Unit *unit = &scene->units[y][x];

			if (unit->asset != NULL) {
				unit_draw(unit);
			}
		}
	}
}

Scene scene_init(int difficulty, const char* path) {

	Scene scene;
	scene.difficulty = difficulty;
    scene.scene_state = STATE_BUILD;

	memset(scene.units, 0, sizeof(scene.units));

	scene.tilemap_layer1.asset_ptr = assets_get(path);
    scene.tilemap_layer2.asset_ptr = assets_get(path);
    
    for (int y = 0; y < TILEMAP_HEIGHT; y++) {
        for (int x = 0; x < TILEMAP_WIDTH; x++) {
            scene.tilemap_layer2.tiles[y][x] = -1;  // Replace TILE_EMPTY with your empty tile value
        }
    }

	scene_randomize(&scene);
	return scene;
}

void scene_randomize(Scene *scene) {

	memset(scene->units, 0, sizeof(scene->units));

	for (int y = 0; y < TILEMAP_HEIGHT; y++) {

		for (int x = 0; x < TILEMAP_WIDTH; x++) {
				int r = GetRandomValue(0, 100);
				if (r <= 40) {
					scene->tilemap_layer1.tiles[y][x] = TILE_GRASS;
				} else if (r > 40 && r <= 85) {
					scene->tilemap_layer1.tiles[y][x] = TILE_GRASS_TALL; 
				} else if (r > 85 && r <= 99) {
					scene->tilemap_layer1.tiles[y][x] = TILE_GRASS_ROCK;
				} else if (r > 99 && r <= 100) {
					scene->tilemap_layer1.tiles[y][x] = TILE_ROCK;
				}
			//}

		}
	}
    gen_treeline(scene);
	gen_random_path(scene);
}

void gen_treeline(Scene *scene) {
    int anchor[2];

    // Generate trees across the top of the screen
    for (int i = 1; i < TILEMAP_WIDTH; i += 2) {  // Increment by 2 to avoid overlapping trees
        if (scene->tilemap_layer1.tiles[0][i] != TILE_TREE_6) {  // Check if no tree already exists
            anchor[0] = -1;  // Set to -1 so the tree is partially out of the map
            anchor[1] = i;
            build_tree(scene, anchor);
        }
    }

    // Generate trees across the bottom of the screen
    for (int i = 1; i < TILEMAP_WIDTH; i += 2) {  // Increment by 2 to avoid overlapping trees
        int bottom_row = TILEMAP_HEIGHT - 2;  // Set to -2 so the tree is partially out of the map
        if (scene->tilemap_layer1.tiles[bottom_row][i] != TILE_TREE_6) {  // Check if no tree already exists
            anchor[0] = bottom_row;
            anchor[1] = i;
            build_tree(scene, anchor);
        }
    }
}

void build_tree(Scene *scene, int anchor[]) {
    int base_row = anchor[0];
    int base_col = anchor[1];

    // Ensure each tile is within map boundaries before placing it
    if (base_row >= 0 && base_row < TILEMAP_HEIGHT && base_col >= 0 && base_col < TILEMAP_WIDTH) {
        scene->tilemap_layer2.tiles[base_row][base_col] = TILE_TREE_1;  // Top-right part of the tree
    }
    if (base_row >= 0 && base_row < TILEMAP_HEIGHT && base_col - 1 >= 0 && base_col - 1 < TILEMAP_WIDTH) {
        scene->tilemap_layer2.tiles[base_row][base_col - 1] = TILE_TREE_2;  // Top-left part of the tree
    }
    if (base_row + 1 >= 0 && base_row + 1 < TILEMAP_HEIGHT && base_col >= 0 && base_col < TILEMAP_WIDTH) {
        scene->tilemap_layer2.tiles[base_row + 1][base_col] = TILE_TREE_3;  // Middle row, right
    }
    if (base_row + 1 >= 0 && base_row + 1 < TILEMAP_HEIGHT && base_col - 1 >= 0 && base_col - 1 < TILEMAP_WIDTH) {
        scene->tilemap_layer2.tiles[base_row + 1][base_col - 1] = TILE_TREE_4;  // Middle row, left
    }
    if (base_row + 2 >= 0 && base_row + 2 < TILEMAP_HEIGHT && base_col >= 0 && base_col < TILEMAP_WIDTH) {
        scene->tilemap_layer2.tiles[base_row + 2][base_col] = TILE_TREE_5;  // Bottom row, right
    }
    if (base_row + 2 >= 0 && base_row + 2 < TILEMAP_HEIGHT && base_col - 1 >= 0 && base_col - 1 < TILEMAP_WIDTH) {
        scene->tilemap_layer2.tiles[base_row + 2][base_col - 1] = TILE_TREE_6;  // Bottom row, left
    }
}

void scene_state_set(Scene *scene, int state){
    scene->scene_state = state;
}

int scene_state_get(Scene *scene){
    int scene_state = scene->scene_state;
    return scene_state;
}