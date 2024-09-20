#include "enemies.h"
#include <stdlib.h>

// Create a new enemy entity
GameEntity *create_enemy(Vector2 position, int speed, int damage) {
    GameEntity *enemy = create_entity(position, speed, 50); // Create a moving enemy
    EnemyComponent *enemyComp = malloc(sizeof(EnemyComponent));
    enemyComp->speed = speed;
    enemyComp->damage = damage;

    add_entity("enemy", enemy); // Add enemy to the ECS map

    return enemy;
}

// Update all enemy entities
void update_enemy_system(float deltaTime) {
    map_iter_t iter = map_iter_();
    const char *key;
    
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            // Enemy movement logic
            entity->position.position.x += entity->speed.speed * deltaTime; // Example movement logic
        }
    }
}

// Render enemies
void render_enemy_system(void) {
    map_iter_t iter = map_iter_();
    const char *key;
    
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            // Render the enemy (e.g., as a red circle)
            DrawCircleV(entity->position.position, 20, RED);
        }
    }
}

