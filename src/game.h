#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "wordlist.h"
#include "scene_builder.h"
#include "tilemap.h"

#define GAME_MAX_SCENES 128

typedef struct {
	Scene scene;
	float dt;	// Delta Time.
	Canvas canvas;
	Canvas ui_canvas;
	WordList list;
	int difficulty;
	int money;
} Game;

// Initializes the game struct.
void game_init();
// Deinitializes the game struct and frees any allocated memory.
void game_shutdown();
void game_update();
void game_draw();

Scene* game_get_scene();
int game_get_difficulty();
int game_get_money();

void game_set_money(int amount);

#endif // GAME_H
