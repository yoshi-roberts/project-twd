#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "canvas.h"
#define MAX_HEALTHBARS 50

typedef struct Healthbar {
    Vector2 position;
    int width;
    int height;
    float currentHealth;
    float maxHealth;
    bool active;
} Healthbar;

Healthbar create_healthbar(Vector2 position, int width, int height, float maxHealth);
void remove_health(Healthbar *healthbar, float amount);
void draw_healthbar(Healthbar *healthbar, int x, int y);
void update_healthbar_position(Healthbar *healthbar, Vector2 newPosition);


#endif
