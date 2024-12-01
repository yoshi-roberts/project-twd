#ifndef TOWER_H
#define TOWER_H

#include "healthbar.h"
#include "assets.h"

typedef struct {
	int damage;
	int hp;
	Healthbar healthbar;	
	Asset *asset;
} Tower;

void tower_init();
void tower_update();
void tower_draw(int x, int y);

int tower_get_hp();
void tower_damage(int amount);

#endif // TOWER_H
