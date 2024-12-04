#include <stdbool.h>
#include <stdio.h>
#include "projectile.h"
#include "enemy.h"
#include "healthbar.h"

Projectile new_projectile(Vector2 position, Enemy *target, int speed, int damage, int type) {
    Projectile proj;
    proj.type = type;
    proj.position = position;
	proj.target = target;
    proj.speed = speed;
    proj.damage = damage;
    proj.active = true;
    return proj;
}

void update_projectile(Projectile *proj) {
    if (proj->active) {
        Vector2 direction = (Vector2){proj->target->x - proj->position.x, proj->target->y - proj->position.y};

        float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

        if (distance > 0) {
            direction.x /= distance;
            direction.y /= distance;

            proj->position.x += direction.x * proj->speed;
            proj->position.y += direction.y * proj->speed;

            if (distance <= proj->speed) {
				enemy_damage(proj->target, 10, 0);
                proj->position = proj->end_position;
                proj->active = false;
            }
        }
    
        if (proj->position.x > GetScreenWidth() || proj->position.x < 0 ||
            proj->position.y > GetScreenHeight() || proj->position.y < 0) {
            proj->active = false;
        }
    }
}

void update_all_projectile(Projectile projectiles[MAX_PROJECTILES], int *projectile_count) {
    for (int i = 0; i < *projectile_count; i++) {
        update_projectile(&projectiles[i]);
        if (!projectiles[i].active) {
        
            for (int j = i; j < *projectile_count - 1; j++) {
                projectiles[j] = projectiles[j + 1];
            }
            (*projectile_count)--;
            i--; 
        }
    }
}


void draw_projectile(Projectile *proj) {
    if (proj->active) {
        DrawCircleV(proj->position, 2, RED);
    }
}
