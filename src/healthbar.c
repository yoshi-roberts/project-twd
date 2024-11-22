#include <stdbool.h>
#include "healthbar.h"

Healthbar create_healthbar(Vector2 position, int width, int height, int *health) {
    Healthbar healthbar;
    healthbar.position = position;
    healthbar.width = width;
    healthbar.height = height;
    healthbar.currentHealth = health;
    healthbar.maxHealth = *health;
    healthbar.active = true;
    return healthbar;
}

void remove_health(Healthbar *healthbar, float amount) {
    if (!healthbar->active) return;

    *healthbar->currentHealth -= amount;
    if (healthbar->currentHealth <= 0) {
        *healthbar->currentHealth = 0;
        healthbar->active = false; // Deactivate if health reaches zero
    }
}

void restore_health(Healthbar *healthbar, float amount) {
    if (!healthbar->active) return;

    *healthbar->currentHealth += amount;
    if (*healthbar->currentHealth > healthbar->maxHealth) {
        *healthbar->currentHealth = healthbar->maxHealth;
    }
}

void draw_healthbar(Healthbar *healthbar, int x, int y) {
    if (!healthbar->active) return;

    // Calculate the width of the current health
    int healthWidth = (*healthbar->currentHealth / healthbar->maxHealth) * healthbar->width;

	int xp = x - (healthbar->width / 2);

    // Draw the background (gray) for the full health bar
    DrawRectangle(xp, y, healthbar->width, healthbar->height, GRAY);

    // Draw the current health (red)
    DrawRectangle(xp, y, healthWidth, healthbar->height, RED);

    // Ensure a clean black border around the health bar
    DrawRectangleLinesEx(
        (Rectangle){xp, y, healthbar->width, healthbar->height}, 
        1,  // Thickness of the border
        BLACK
    );
}
