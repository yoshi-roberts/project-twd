// ecs.c
#include "ecs.h"
#include "components/enemies.h"
#include "components/entity_movement.h"
#include <stdio.h>

void ecs_init() {
    // Initialize ECS, set up necessary components
}

void ecs_update(float delta_time) {
    // Update all entities with movement components
    update_movement_system(delta_time);
    
    // Update all entities with enemy components
    update_enemy_system();
}

Entity ecs_create_entity() {
    static Entity next_entity = 1;
    return next_entity++;
}

void ecs_destroy_entity(Entity entity) {
    // Clean up entity data
}

