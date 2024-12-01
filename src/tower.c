#include "tower.h"
#include "assets.h"
#include "healthbar.h"

static Tower tower = {};

void tower_init() {

	tower.damage = 10;
	tower.hp = 100;

	tower.healthbar = create_healthbar(&tower.hp, 20, 4, GREEN);
	tower.asset = assets_get("assets/images/tower-wizard.png");
}

void tower_update() {

}

void tower_draw(int x, int y) {
	DrawTexture(tower.asset->data.sprite.texture, x, y, WHITE);
	draw_healthbar(&tower.healthbar, x + 16, y - 4, GREEN);
}

void tower_damage(int amount) {

	if (tower.hp > 0) {
		tower.hp -= amount;
	}
}

int tower_get_hp() {
	return tower.hp;
}
