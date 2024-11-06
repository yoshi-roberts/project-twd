#include "enemies.h"
#include "assets.h"
#include <math.h>
#include <stdio.h>
#include "scene_builder.h"
#include "game.h"

void enemy_new(ENEMY_TYPE type, int x, int y) {
	Enemy enemy = {};
	enemy.type = ENEMY_KNIGHT;
	enemy.selected = false;
	enemy.x = x;
	enemy.y = y;
	enemy.asset = assets_get("assets/images/units.png");
	enemy.range = 32;
	enemy.hp = 100;

	Scene *scn = game_get_scene();
	enemy = scn->enemy[10][10];

}

void enemy_draw(Enemy *enemy) {


	asset_draw_tile(enemy->asset, enemy->type, enemy->x * 16, enemy->y * 16);


	if (enemy->selected) {
		Color color = (Color){255, 75, 75, 128};
		DrawCircleLines((enemy->x * 16) + 8, (enemy->y * 16) + 8, (enemy->range * 16) + 8, color);

		char hp[128];
		char defense[128];
	
		sprintf(hp, "HP: %d", enemy->hp);
		sprintf(defense, "Defense: %d", enemy->defense);

		int hp_size = MeasureText(hp, 10);
		int defense_size = MeasureText(defense, 10);

		Vector2 hp_pos = {
			floor(((enemy->x * 16) + 8) - ((float)hp_size / 2)),
			floor((enemy->y * 16) - 16) - 10,
		};
		Vector2 defense_pos = {
			floor(((enemy->x * 16) + 8) - ((float)defense_size / 2)),
			floor((enemy->y * 16) - 16),
		};

		DrawText(hp, hp_pos.x, hp_pos.y, 10, WHITE);
		DrawText(defense, defense_pos.x, defense_pos.y, 10, WHITE);
	}

	enemy->selected = false;
}

void enemy_update(Enemy *enemy) {
    // Move the enemy's x and y positions based on keyboard input
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) enemy->x += 1;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) enemy->x -= 1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) enemy->y += 1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) enemy->y -= 1;

    // Bound the enemy within the map limits (30x17 grid)
    if (enemy->x < 0) enemy->x = 0;
    if (enemy->x >= 30) enemy->x = 29;  // Max x position is 29 (30 tiles wide)
    if (enemy->y < 0) enemy->y = 0;
    if (enemy->y >= 17) enemy->y = 16;  // Max y position is 16 (17 tiles high)
}
