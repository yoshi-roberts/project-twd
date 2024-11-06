#include <stdbool.h>
#include <stdio.h>
#include "game.h"
#include "assets.h"
#include "animation.h"
#include "log.h"
#include "text_input.h"
#include "scene_builder.h"
#include "placement.h"
#include "scene_builder.h"
#include "ui.h"

static Game game = {};
static bool initialized = false;

static TextInput input;
static Animation anim;
static UI_Panel panel;

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

	anim = animation_new("assets/animations/test-anim.png", 6);
	placement_init();

	game.list = wordlist_init();
	input = text_input_init(game.list.easy);

	panel = ui_panel_new(64, 64);
	ui_panel_add_label(&panel, "Hello, World!");
	ui_panel_add_label(&panel, "More text.");

	initialized = true;
	log_info("Game initialized.");
}

void game_shutdown() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

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
		
		text_input_update(&input);

		animation_update(&anim);
		placement_update(game.canvas.mouse.x, game.canvas.mouse.y);

		if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_R)) {
			text_input_reset(&input);
			input.target = wordlist_get(game.list.easy);
			scene_randomize(&game.scene);
		}

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
	placement_draw();

	char money_str[128];
	sprintf(money_str, "Money: $%d", game.money);
	DrawText(money_str, 4, 4, 10, WHITE);

	text_input_draw(&input);

	animation_draw(&anim, 64, 64);

	ui_panel_draw(&panel);

	canvas_end();

	canvas_draw(&game.canvas);
	EndDrawing();
}

Scene* game_get_scene() {
	return &game.scene;
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
