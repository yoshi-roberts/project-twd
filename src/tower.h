#ifndef TOWER_H
#define TOWER_H

#define TOWER_MAX_PROJECTILES 128

#include "healthbar.h"
#include "assets.h"
#include "projectile.h"
#include "text_input.h"
#include <stdbool.h>

typedef struct {
	int damage;
	int hp;
	bool typing;
	Healthbar healthbar;	
	TextInput text_input;
	Projectile projectiles[TOWER_MAX_PROJECTILES];
	int last_projectile;
	Asset *asset;
} Tower;

void tower_init();
void tower_update();
void tower_draw(int x, int y);
int tower_get_hp();
void tower_damage(int amount);

bool tower_is_typing();

#endif // TOWER_H
