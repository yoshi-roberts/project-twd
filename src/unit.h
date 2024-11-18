#ifndef UNIT_H
#define UNIT_H

#include "assets.h"

typedef enum {
	UNIT_VILLAGER,
	UNIT_KNIGHT,
} UNIT_TYPE;

typedef struct {
	UNIT_TYPE type;
	Asset *asset;
	int x; int y;
	int range;
	int hp;
	int defense;
	int cost;
	bool selected;
} Unit;

Unit unit_new(UNIT_TYPE type, int x, int y);
void unit_update(Unit *unit);
void unit_draw(Unit *unit);
int unit_get_cost(UNIT_TYPE type);

#endif // UNIT_H
