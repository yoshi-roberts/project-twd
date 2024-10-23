#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "wordlist.h"
#include "scene_builder.h"

#define GAME_MAX_SCENES 128

typedef struct {
	Scene scene;
	float dt;	// Delta Time.
	int difficulty;
	Canvas canvas;
	Canvas ui_canvas;
	WordList list;
} Game;

// Initializes the game struct.
void game_init();
// Deinitializes the game struct and frees any allocated memory.
void game_shutdown();
void game_update();
void game_draw();

Scene* game_get_scene();
int game_get_difficulty();

#endif // GAME_H
