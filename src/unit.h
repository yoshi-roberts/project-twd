#ifndef UNIT_H
#define UNIT_H

#include "assets.h"
#include "enemy.h"
#include "text_input.h"

typedef enum {
	UNIT_VILLAGER,
	UNIT_KNIGHT,
} UNIT_TYPE;

typedef enum {
	UNIT_STATE_IDLE,
	UNIT_STATE_ATTACK,
	UNIT_STATE_TYPE,
} UNIT_STATE;

typedef struct {
	UNIT_TYPE type;
	UNIT_STATE state;
	Asset *asset;
	TextInput text_input;
	Enemy *target;
	int x; int y;
	int range;
	int hp;
	int defense;
	int cost;
	int energy;
	int attack_timer;
	int attack_cooldown;
	bool can_attack;
	bool selected;
} Unit;

Unit unit_new(UNIT_TYPE type, int x, int y);
void unit_update(Unit *unit);
void unit_draw(Unit *unit);
Enemy* unit_enemy_in_range(Unit *unit);
int unit_get_cost(UNIT_TYPE type);

#endif // UNIT_H
