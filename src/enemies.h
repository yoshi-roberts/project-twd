#ifndef ENEMIES_H
#define ENEMIES_H

#include "ecs.h"

// Enemy-specific components
typedef struct {
    int damage;
    int speed;
} EnemyComponent;

// Function declarations
GameEntity *create_enemy(Vector2 position, int speed, int damage);
void update_enemy_system(float deltaTime);
void render_enemy_system(void);

#endif

