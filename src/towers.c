#include "towers.h"
#include <stdlib.h>

// Create a new tower entity
GameEntity *create_tower(Vector2 position, float range, int damage, float reloadTime) {
    GameEntity *tower = create_entity(position, 0, 100); // Towers don't move, hence speed = 0
    TowerComponent *towerComp = malloc(sizeof(TowerComponent));
    towerComp->range = range;
    towerComp->damage = damage;
    towerComp->reloadTime = reloadTime;
    towerComp->reloadTimer = 0.0f;

    add_entity("tower", tower); // Add tower to the ECS map

    return tower;
}

// Update all tower entities
void update_tower_system(float deltaTime) {
    map_iter_t iter = map_iter_();
    const char *key;
    
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            // Tower-specific logic here (like shooting cooldown)
            TowerComponent *tower = (TowerComponent *)map_get_(&entity_map, key);
            tower->reloadTimer -= deltaTime;
            if (tower->reloadTimer <= 0) {
                // Tower is ready to shoot (add shooting logic here)
                tower->reloadTimer = tower->reloadTime;
            }
        }
    }
}

// Render towers
void render_tower_system(void) {
    map_iter_t iter = map_iter_();
    const char *key;
    
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            // Render the tower (e.g., as a square or circle)
            DrawCircleV(entity->position.position, 20, BLUE);
        }
    }
}

