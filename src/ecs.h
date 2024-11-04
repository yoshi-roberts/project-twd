// ecs.h
#ifndef ECS_H
#define ECS_H

#include <stdint.h>
#include "types/types.h"

// Define a generic Entity type
typedef uint32_t Entity;

// Structure for a component (you can expand based on actual components needed)
typedef struct {
    Entity entity;
    // Add component-specific data here
} Component;

// Function declarations for ECS management
void ecs_init();
void ecs_update(float delta_time);
Entity ecs_create_entity();
void ecs_destroy_entity(Entity entity);

// Component management functions
void add_movement_component(Entity entity, float x, float y, float velocity);
void add_enemy_component(Entity entity, int health, int attack);

#endif

