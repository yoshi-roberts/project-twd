#include "unit.h"
#include "assets.h"

Unit unit_new(UNIT_TYPE type, int x, int y) {
	Unit unit = {};

	unit.type = type;
	unit.x = x;
	unit.y = y;
	unit.asset = assets_get("assets/images/units.png");

	return unit;
}

void unit_draw(Unit *unit) {
	asset_draw_tile(unit->asset, 0, unit->x * 16, unit->y * 16);
}
