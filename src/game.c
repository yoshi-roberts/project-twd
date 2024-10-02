#include <stdbool.h>
#include "game.h"
#include "assets.h"
#include "log.h"
#include "canvas.h"
#include "wordlist.h"
#include "text_input.h"
#include "scene_builder.h"

static Game game = {};
static bool initialized = false;
static Scene scene;

static WordList list;
static TextInput input;

void game_init() {

	if (initialized) {
		log_error("Game already initialized.");
		return;
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(1280, 720, "Project Tower Defense");
	SetTargetFPS(60);

	game.dt = 0.0f;
	game.canvas = canvas_init(480, 270, TEXTURE_FILTER_POINT);

	assets_init();
	scene = scene_init(1, "assets/images/tiles.png");

	list = wordlist_init();
	input = text_input_init(list.easy);

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

		if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_R)) {
			text_input_reset(&input);
			input.target = wordlist_get(list.easy);
			_scene_randomize(&scene);
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
	scene_draw(&scene);
	text_input_draw(&input);
	canvas_end();

	canvas_draw(&game.canvas);
	DrawRectangle(4, 4, 128, 26, WHITE);
	DrawFPS(8, 8);
	EndDrawing();
}
