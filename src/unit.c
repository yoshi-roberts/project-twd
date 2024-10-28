#include "unit.h"
#include "assets.h"
#include <math.h>
#include <stdio.h>

Unit unit_new(UNIT_TYPE type, int x, int y) {
	Unit unit = {};

	unit.type = type;
	unit.selected = false;
	unit.x = x;
	unit.y = y;
	unit.asset = assets_get("assets/images/units.png");
	unit.range = 32;

	switch (type) {
		case UNIT_KNIGHT:
			unit.range = 2;
			unit.hp = 100;
			break;
		case UNIT_VILLAGER:
			unit.range = 1;
			unit.hp = 70;
			break;
	}

	return unit;
}

void unit_draw(Unit *unit) {


	asset_draw_tile(unit->asset, unit->type, unit->x * 16, unit->y * 16);


	if (unit->selected) {
		Color color = (Color){255, 75, 75, 128};
		DrawCircleLines((unit->x * 16) + 8, (unit->y * 16) + 8, (unit->range * 16) + 8, color);

		char hp[128];
		sprintf(hp, "HP: %d", unit->hp);

		int size = MeasureText(hp, 10);
		Vector2 pos = {
			floor(((unit->x * 16) + 8) - (size / 2)),
			floor((unit->y * 16) - 16),
		};

		DrawText(hp, pos.x, pos.y, 10, WHITE);
	}

	unit->selected = false;
}
