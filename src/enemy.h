#ifndef ENEMIES_H
#define ENEMIES_H

#include "../lib/raylib/src/raylib.h"
#include "assets.h"
#include "healthbar.h"

typedef enum {
	ENEMY_SLIME,
	ENEMY_SKELETON,
	ENEMY_SPIDER,
} ENEMY_TYPE;

typedef struct {
	ENEMY_TYPE type;
	int hp;
	int x; int y;
	int xdir; int ydir;
	int next_waypoint_index;
	Vector2 next_waypoint;
	Asset *asset;
	Healthbar healthbar;
	bool active;
} Enemy;

void enemy_new(ENEMY_TYPE type);
void enemy_update(Enemy *enemy);
void enemy_draw(Enemy *enemy);
void enemy_get_waypoint(Enemy *enemy);

#endif // ENEMIES_H

