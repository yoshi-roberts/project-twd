#ifndef TOWERS_H
#define TOWERS_H

#include "ecs.h"

// Tower-specific components
typedef struct {
    float range;
    int damage;
    float reloadTime;
    float reloadTimer;
} TowerComponent;

// Function declarations
GameEntity *create_tower(Vector2 position, float range, int damage, float reloadTime);
void update_tower_system(float deltaTime);
void render_tower_system(void);

#endif

