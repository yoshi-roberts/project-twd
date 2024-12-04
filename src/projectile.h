#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "canvas.h"
#include "enemy.h"
#define MAX_PROJECTILES 50

typedef struct Projectile {
    int type;
    int damage;
    int speed;
    Vector2 position;
    Vector2 end_position;
	Enemy *target;
    bool active;
} Projectile;

Projectile new_projectile(Vector2 position, Enemy *target, int speed, int damage, int type);
void update_projectile(Projectile *proj);
void update_all_projectile(Projectile projectiles[MAX_PROJECTILES], int *projectile_count);
void draw_projectile(Projectile *proj);



#endif
