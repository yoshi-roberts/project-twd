#include <stdbool.h>
#include <stdio.h>
#include "game.h"
#include "assets.h"
#include "animation.h"
#include "healthbar.h"
#include "log.h"
#include "scene_builder.h"
#include "placement.h"
#include "scene_builder.h"
#include "enemy.h"
#include "projectile.h"
#include "wordlist.h"

static Game game = {};
static bool initialized = false;

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
	game.money = START_MONEY;
	game.canvas = canvas_init(480, 270, TEXTURE_FILTER_POINT);

	assets_init();
	game.scene = scene_init(1, "assets/images/tiles.png");
	anim = animation_new("assets/animations/test-anim.png", 6);
	tower = assets_get("assets/images/tower-wizard.png");

	game.scene.tower_hp = 200;
	game.scene.tower_healthbar = create_healthbar(&game.scene.tower_hp, 20, 4, GREEN);

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

		animation_update(&anim);
		placement_update(game.canvas.mouse.x, game.canvas.mouse.y);

		// if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_R)) {
		// 	scene_randomize(&game.scene);
		// 	scene_state_set(STATE_BUILD);
		// }

		if (IsKeyPressed(KEY_SPACE)) {
			if (scene_state_get() == STATE_BUILD){
				scene_state_set(STATE_PLAY);
			}
		}
   

		// if (IsKeyPressed(KEY_S)) {
			// if (game.scene.projectile_count < MAX_PROJECTILES) {
			// 	Vector2 start_position = (Vector2){100, 200};
			// 	Vector2 end_position = (Vector2){300, 200};

			// 	game.scene.projectiles[game.scene.projectile_count] = new_projectile(start_position, end_position, 5, 10, 0);
			// 	game.scene.projectile_count++;
			//}
		// 		Scene *scn = game_get_scene();
		// 		for (int i = 0; i < scn->last_enemy; i++) {
		// 		Enemy *enemy = scn->enemies[i];
		// 		remove_health(&enemy->healthbar, 500);
		// 		}
		// }

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

	if (scene_state_get() == STATE_LOSE) {
        scene_ui_gameover();
	}
	else if (scene_state_get() == STATE_WIN) {
        scene_ui_gameover();
	}
	else{
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

	animation_draw(&anim, 64, 64);
	}
	canvas_end();
	canvas_draw(&game.canvas);
	EndDrawing();
	
}


void game_restart(void *data) {
    Scene *scene = game_get_scene();
    scene->tower_hp = 200;
    scene->tower_healthbar = create_healthbar(&scene->tower_hp, 20, 4, GREEN);
    game_set_money(START_MONEY);
    for (int i = 0; i < scene->last_enemy; i++) {
        free(scene->enemies[i]);
        scene->enemies[i] = NULL;
    }
    scene->last_enemy = 0;
    scene_randomize(scene);
    scene_state_set(STATE_BUILD);
}

void game_quit(void *data) {
    CloseWindow();
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
