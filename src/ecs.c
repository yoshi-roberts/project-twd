#include "ecs.h"
#include <stdlib.h>

// Map to hold all entities
map_base_t entity_map;

// Function to initialize the map for entities
void init_entities() {
    map_init_(&entity_map);
}

// Function to create a new entity
GameEntity *create_entity(Vector2 position, float speed, int health) {
    GameEntity *newEntity = malloc(sizeof(GameEntity));
    newEntity->entity.isActive = true;
    newEntity->position.position = position;
    newEntity->speed.speed = speed;
    newEntity->health.health = health;
    return newEntity;
}

// Function to add a new entity to the world
void add_entity(const char *key, GameEntity *entity) {
    if (entity != NULL) {
        map_set_(&entity_map, key, entity, sizeof(GameEntity));
    }
}

// Function to destroy an entity
void destroy_entity(const char *key) {
    GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
    if (entity) {
        entity->entity.isActive = false;
        free(entity); // Free memory
        map_remove_(&entity_map, key);
    }
}

// Function to update entity movement
void update_movement_system(float deltaTime) {
    map_iter_t iter = map_iter_();
    const char *key;
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            entity->position.position.x += entity->speed.speed * deltaTime;
        }
    }
}

// Function to render all active entities
void render_system(void) {
    map_iter_t iter = map_iter_();
    const char *key;
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            DrawCircleV(entity->position.position, 20, RED);
        }
    }
}

// Function to free all entities and destroy the entity map
void destroy_all_entities(void) {
    map_iter_t iter = map_iter_();
    const char *key;
    
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity) {
            free(entity);
        }
    }

    map_deinit_(&entity_map);

