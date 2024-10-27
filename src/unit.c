#include "unit.h"
#include "assets.h"

Unit unit_new(UNIT_TYPE type, int x, int y) {
	Unit unit = {};

	unit.type = type;
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
			unit.range = 2;
			unit.hp = 70;
			break;
	}

	unit.range = unit.range * 16;

	return unit;
}

void unit_draw(Unit *unit) {
	Color color = (Color){255, 75, 75, 128};
	DrawCircle((unit->x * 16) + 8, (unit->y * 16) + 8, unit->range, color);
	asset_draw_tile(unit->asset, unit->type, unit->x * 16, unit->y * 16);
}
