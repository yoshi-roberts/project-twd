#include <stdbool.h>
#include "../lib/raylib/src/raylib.h"
#include "game.h"
#include "assets.h"
#include "log.h"

static Game game = {};
static bool initialized = false;

void game_init() {

	if (initialized) {
		log_error("Game already initialized.");
		return;
	}

	InitWindow(1280, 720, "Project Tower Defense");
	SetTargetFPS(60);

	assets_init();
	initialized = true;

	log_info("Game initialized.");
}

void game_shutdown() {

	if (!initialized) {
		log_error("Game not initialized.");
		return;
	}

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
	EndDrawing();
}
