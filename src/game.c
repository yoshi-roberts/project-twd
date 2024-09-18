#include <stdbool.h>
#include "../lib/raylib/src/raylib.h"
#include "game.h"
#include "assets.h"
#include "log.h"
#include "canvas.h"

static Game game = {};
static bool initialized = false;

static Canvas canvas;

void game_init() {

	if (initialized) {
		log_error("Game already initialized.");
		return;
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 720, "Project Tower Defense");
	SetTargetFPS(60);

	assets_init();
	canvas = canvas_init(480, 270);

	initialized = true;
	log_info("Game initialized.");
}

void game_shutdown() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

	canvas_destroy(&canvas);
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
		canvas_update(&canvas);
		game_draw();
	}

}

void game_draw() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

	BeginDrawing();
	ClearBackground(WHITE);
	canvas_begin(&canvas);
	canvas_end(&canvas);
	canvas_draw(&canvas);
	EndDrawing();
}
