#include "tower.h"
#include "assets.h"
#include "game.h"
#include "healthbar.h"
#include "text_input.h"

static Tower tower = {};

void tower_init() {

	tower.damage = 10;
	tower.typing = false;
	tower.hp = 100;

	tower.healthbar = create_healthbar(&tower.hp, 20, 4, GREEN);
	tower.asset = assets_get("assets/images/tower-wizard.png");

	tower.text_input = text_input_new(game_get_wordlist()->easy);
}

void tower_update() {
	
	if (!game_get_text_input_active()) {

		if (text_input_update(&tower.text_input)) {

			text_input_reset(&tower.text_input);
		}
	}
}

void tower_draw(int x, int y) {

	DrawTexture(tower.asset->data.sprite.texture, x, y, WHITE);
	draw_healthbar(&tower.healthbar, x + 16, y + 56, GREEN);

	if (!game_get_text_input_active()) {

		text_input_draw(&tower.text_input, x + 16, y - 4);
	}
}

void tower_damage(int amount) {

	if (tower.hp > 0) {
		tower.hp -= amount;
	}
}

int tower_get_hp() {
	return tower.hp;
}

bool tower_is_typing() {
	return tower.typing;
}
