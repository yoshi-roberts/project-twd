#include <stdbool.h>
#include <stdio.h>
#include "projectile.h"


Projectile new_projectile(Vector2 position, Vector2 end_position, int speed, int damage, int type) {

    Projectile proj;
    proj.type = type;
    proj.position = position;
    proj.end_position = end_position;
    proj.speed = speed;
    proj.damage = damage;
    proj.active = true;
    return proj;
}


void update_projectile(Projectile *proj) {
    if (proj->active) {
        // Calculate the direction vector from the current position to the end_position
        Vector2 direction = (Vector2){proj->end_position.x - proj->position.x, proj->end_position.y - proj->position.y};

        // Get the length of the direction vector (distance between current and target position)
        float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

        // If the distance is greater than zero, normalize the direction vector
        if (distance > 0) {
            direction.x /= distance;
            direction.y /= distance;

            proj->position.x += direction.x * proj->speed;
            proj->position.y += direction.y * proj->speed;

            if (distance <= proj->speed) {
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

void draw_projectile(Projectile *proj) {
    if (proj->active) {
        DrawCircleV(proj->position, 2, RED);
    }
}