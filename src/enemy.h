#ifndef ENEMIES_H
#define ENEMIES_H

#include "../lib/raylib/src/raylib.h"

typedef enum {
	ENEMY_SLIME,
} ENEMY_TYPE;

// Enemy-specific components
typedef struct {
	ENEMY_TYPE type;
	int x; int y;
	int xdir; int ydir;
	int next_waypoint_index;
	Vector2 next_waypoint;
} Enemy;

Enemy enemy_new(ENEMY_TYPE type);
void enemy_update(Enemy *enemy);
void enemy_draw(Enemy *enemy);
void enemy_get_waypoint(Enemy *enemy);

#endif // ENEMIES_H

