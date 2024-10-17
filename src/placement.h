#ifndef PLACEMENT_H
#define PLACEMENT_H

typedef struct {
	int x; int y;
} Placement;

Placement placement_init();
void placement_update(Placement *placement, float mx, float my);
void placement_draw(Placement *placement);

#endif
