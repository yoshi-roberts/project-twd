#ifndef PLACEMENT_H
#define PLACEMENT_H

#include "../lib/raylib/src/raylib.h"
#include "assets.h"
#include "unit.h"
#include "ui.h"
#include "scene_builder.h"

typedef enum {
	PLACEMENT_IDLE,
	PLACEMENT_BUILD,
} PlacementState;

typedef struct {
	int x; int y;
	int gx; int gy;
	int current_tile;
	Unit *selected_unit;
	Color normal;
	Color blocked;
	Asset *border;

	PlacementState state;
	UI_Panel build_menu;
} Placement;

void placement_init();
void placement_update(float mx, float my);
void placement_draw();
int placement_get_tile(Scene *scene);
bool placement_can_place();

#endif
