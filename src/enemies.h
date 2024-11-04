// enemies.h
#ifndef ENEMIES_H
#define ENEMIES_H

#include "ecs.h"

typedef struct {
    int health;
    int attack;
} EnemyComponent;

void add_enemy_component(Entity entity, int health, int attack);
void update_enemy_system();

#endif

