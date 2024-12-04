#ifndef GAME_H
#define GAME_H

#include "canvas.h"
#include "wordlist.h"
#include "scene_builder.h"
#include "tilemap.h"
#include "projectile.h"
#include "healthbar.h"
#include "ui.h"

#define GAME_MAX_SCENES 128

typedef struct {
	Scene scene;
	float dt;	// Delta Time.
	Canvas canvas;
	Canvas ui_canvas;
	WordList list;
	bool text_input_active;
	int difficulty;
	int money;
} Game;

void game_init();
void game_shutdown();
void game_update();
void game_draw();

void game_restart(void *data);
void game_quit(void *data);

Scene* game_get_scene();
WordList* game_get_wordlist();
bool game_get_text_input_active();
int game_get_difficulty();
int game_get_money();
int game_get_mouse_x();
int game_get_mouse_y();

void game_set_money(int amount);
void game_set_text_input_active(bool active);

#endif
