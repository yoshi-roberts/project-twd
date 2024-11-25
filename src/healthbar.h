#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "canvas.h"
#define MAX_HEALTHBARS 50

typedef struct Healthbar {
	int *hp; int hp_max;
    int width;
    int height;
    bool active;
} Healthbar;

Healthbar create_healthbar(int *hp, int width, int height);
void remove_health(Healthbar *healthbar, float amount);
void draw_healthbar(Healthbar *healthbar, int x, int y);


#endif
