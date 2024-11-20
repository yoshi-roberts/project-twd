#include <stdbool.h>
#include <stdio.h>
#include "projectile.h"
#include "healthbar.h"

Healthbar create_healthbar(Vector2 position, int width, int height, float maxHealth) {
    Healthbar healthbar;
    healthbar.position = position;
    healthbar.width = width;
    healthbar.height = height;
    healthbar.maxHealth = maxHealth;
    healthbar.currentHealth = maxHealth;
    healthbar.active = true;
    return healthbar;
}

void remove_health(Healthbar *healthbar, float amount) {
    if (!healthbar->active) return;

    healthbar->currentHealth -= amount;
    if (healthbar->currentHealth <= 0) {
        healthbar->currentHealth = 0;
        healthbar->active = false; // Deactivate if health reaches zero
    }
}

void restore_health(Healthbar *healthbar, float amount) {
    if (!healthbar->active) return;

    healthbar->currentHealth += amount;
    if (healthbar->currentHealth > healthbar->maxHealth) {
        healthbar->currentHealth = healthbar->maxHealth;
    }
}

void draw_healthbar(Healthbar *healthbar) {
    if (!healthbar->active || healthbar->currentHealth == healthbar->maxHealth) return;

    float healthWidth = (healthbar->currentHealth / healthbar->maxHealth) * healthbar->width;
    DrawRectangle(healthbar->position.x, healthbar->position.y, healthbar->width, healthbar->height, GRAY);
    DrawRectangle(healthbar->position.x, healthbar->position.y, healthWidth, healthbar->height, GREEN);
    DrawRectangleLines(healthbar->position.x, healthbar->position.y, healthbar->width, healthbar->height, BLACK);
}

void update_healthbar_position(Healthbar *healthbar, Vector2 newPosition) {
    healthbar->position = newPosition;
}
