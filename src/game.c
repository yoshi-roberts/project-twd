#include <stdbool.h>
#include <stdio.h>
#include "game.h"
#include "assets.h"
#include "animation.h"
#include "healthbar.h"
#include "log.h"
#include "text_input.h"
#include "scene_builder.h"
#include "placement.h"
#include "scene_builder.h"
#include "enemy.h"

static Game game = {};
static bool initialized = false;

static TextInput input;
static Animation anim;
static Asset *tower;

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
	game.scene.tower_hp = 100;
	game.money = 1000;
	game.canvas = canvas_init(480, 270, TEXTURE_FILTER_POINT);

	assets_init();
	game.scene = scene_init(1, "assets/images/tiles.png");

	anim = animation_new("assets/animations/test-anim.png", 6);
	tower = assets_get("assets/images/tower-wizard.png");

	game.scene.tower_healthbar = create_healthbar(&game.scene.tower_hp, 20, 4, GREEN);
	placement_init();

	game.list = wordlist_init();
	input = text_input_init(game.list.easy);

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
		
		text_input_update(&input);

		animation_update(&anim);
		placement_update(game.canvas.mouse.x, game.canvas.mouse.y);

		if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_R)) {
			text_input_reset(&input);
			input.target = wordlist_get(game.list.easy);
			scene_randomize(&game.scene);
		}

		if (IsKeyPressed(KEY_SPACE)) {

			if (game.scene.last_enemy < 128) {

				int type = GetRandomValue(0, 2);
				enemy_new(type);
			}
		}

		if (IsKeyPressed(KEY_R)) {
			for (int i = 0; i < game.scene.last_enemy; i++) {
				Enemy *enemy = game.scene.enemies[i];
				remove_health(&enemy->healthbar, 10);
			}
		}

		if (IsKeyPressed(KEY_S)) {
			if (game.scene.projectile_count < MAX_PROJECTILES) {
				Vector2 start_position = (Vector2){100, 200};
				Vector2 end_position = (Vector2){300, 200};

				game.scene.projectiles[game.scene.projectile_count] = new_projectile(start_position, end_position, 5, 10, 0);
				game.scene.projectile_count++;
			}
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

	DrawTexture(tower->data.sprite.texture, 0, 6 * 16, WHITE);
	draw_healthbar(&game.scene.tower_healthbar, 16, 145, GREEN);

	char money_str[128];
	sprintf(money_str, "Money: $%d", game.money);
	DrawText(money_str, 4, 4, 10, WHITE);

	for (int i = 0; i < game.scene.projectile_count; i++) {
    	draw_projectile(&game.scene.projectiles[i]);
	}

	placement_draw();
	text_input_draw(&input);

	animation_draw(&anim, 64, 64);

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

int game_get_mouse_x() {
	return game.canvas.mouse.x;
}

int game_get_mouse_y() {
	return game.canvas.mouse.y;
}
