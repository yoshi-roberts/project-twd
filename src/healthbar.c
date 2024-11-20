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

    // Calculate the width of the current health
    float healthWidth = (healthbar->currentHealth / healthbar->maxHealth) * healthbar->width;

    // Draw the background (gray) for the full health bar
    DrawRectangle(healthbar->position.x, healthbar->position.y, healthbar->width, healthbar->height, GRAY);

    // Draw the current health (red)
    DrawRectangle(healthbar->position.x, healthbar->position.y, healthWidth, healthbar->height, RED);

    // Ensure a clean black border around the health bar
    DrawRectangleLinesEx(
        (Rectangle){healthbar->position.x, healthbar->position.y, healthbar->width, healthbar->height}, 
        1,  // Thickness of the border
        BLACK
    );
}


void update_healthbar_position(Healthbar *healthbar, Vector2 newPosition) {
    healthbar->position = newPosition;
}
