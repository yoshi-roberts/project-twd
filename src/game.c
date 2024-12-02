#include <stdbool.h>
#include <stdio.h>
#include "game.h"
#include "assets.h"
#include "log.h"
#include "scene_builder.h"
#include "placement.h"
#include "scene_builder.h"
#include "projectile.h"
#include "wordlist.h"
#include "tower.h"

static Game game = {};
static bool initialized = false;

void game_init() {

	if (initialized) {
		log_error("Game already initialized.");
		return;
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(1280, 720, "Project Tower Defense");
	SetTargetFPS(60);

	game.dt = 0.0f;
	game.difficulty = 0;
	game.money = 1000;
	game.canvas = canvas_init(480, 270, TEXTURE_FILTER_POINT);

	assets_init();
	game.scene = scene_init(1, "assets/images/tiles.png");

	tower_init();
	placement_init();

	game.list = wordlist_init();

	initialized = true;
	log_info("Game initialized.");
}

void game_shutdown() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

	scene_destroy(&game.scene);
	canvas_destroy(&game.canvas);

	assets_destory();
	CloseWindow();

	initialized = false;
	log_info("Game shutdown.");
}

void game_update() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

	while (!WindowShouldClose()) {
		game.dt = GetFrameTime();	// Update delta time.
		
		scene_update(&game.scene);

		placement_update(game.canvas.mouse.x, game.canvas.mouse.y);
		tower_update();

		if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_R)) {
			scene_randomize(&game.scene);
		}

		update_all_projectile(game.scene.projectiles, &game.scene.projectile_count);
		canvas_update(&game.canvas);
		game_draw();
	}
}

void game_draw() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

	BeginDrawing();
	ClearBackground(BLACK);

	canvas_begin(&game.canvas);
	scene_draw(&game.scene);

	tower_draw(0, 5 * 16);

	char money_str[128];
	sprintf(money_str, "Money: $%d", game.money);
	DrawText(money_str, 4, 4, 10, WHITE);

	for (int i = 0; i < game.scene.projectile_count; i++) {
    	draw_projectile(&game.scene.projectiles[i]);
	}

	placement_draw();

	canvas_end();

	canvas_draw(&game.canvas);
	EndDrawing();
}

void game_check_state(Scene *scene){
	// if (*scene->tower_healthbar.hp <= 0){
	// 	for (int i = 0; i < scene->last_enemy; i++) {
	// 		Enemy *enemy = scene->enemies[i];
	// 		remove_health(&enemy->healthbar, 500);
	// 	}
	// 	//scene->last_enemy = 128;
	// }
}

Scene* game_get_scene() {
	return &game.scene;
}

WordList* game_get_wordlist() {
	return &game.list;
}

int game_get_difficulty() {
	return game.difficulty;
}

int game_get_money() {
	return game.money;
}

void game_set_money(int amount) {
	game.money = amount;
}

int game_get_mouse_x() {
	return game.canvas.mouse.x;
}

int game_get_mouse_y() {
	return game.canvas.mouse.y;
}

bool game_get_text_input_active() {
	return game.text_input_active;
}

void game_set_text_input_active(bool active) {
	game.text_input_active = active;
}
