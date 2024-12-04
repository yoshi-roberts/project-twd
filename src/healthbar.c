#include <stdbool.h>
#include "healthbar.h"
#include "game.h"

Healthbar create_healthbar(int *hp, int width, int height, Color color) {

    Healthbar healthbar;

	healthbar.hp = hp;
	healthbar.hp_max = *hp;
    healthbar.width = width;
    healthbar.height = height;
    healthbar.color = color;
    healthbar.active = true;
    return healthbar;
}

void remove_health(Healthbar *healthbar, float amount) {
    if (!healthbar->active) return;
    *healthbar->hp -= amount;
    if (*healthbar->hp <= 0) {
        *healthbar->hp = 0;
        healthbar->active = false; // Deactivate if health reaches zero
        scene_check_state();
    }
}

void restore_health(Healthbar *healthbar, float amount) {
    if (!healthbar->active) return;

    *healthbar->hp += amount;
    if (*healthbar->hp > healthbar->hp_max) {
        *healthbar->hp = healthbar->hp_max;
    }
}

void draw_healthbar(Healthbar *healthbar, int x, int y, Color color) {
    if (!healthbar->active) return;

	int xp = x - (healthbar->width / 2);
	float width = ((float)*healthbar->hp / (float)healthbar->hp_max) * healthbar->width;
    
	DrawRectangle(xp - 1, y - 1, healthbar->width + 2, healthbar->height + 2, BLACK);
	DrawRectangle(xp, y, width, healthbar->height, color);
}

