#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "canvas.h"

typedef struct Projectile {
    int type;
    int damage;
    int speed;
    Vector2 position;
    Vector2 end_position;
    bool active;
} Projectile;

Projectile new_projectile(Vector2 position, Vector2 end_position, int speed, int damage, int type);
void update_projectile(Projectile *proj);
void draw_projectile(Projectile *proj);



#endif
