#ifndef ANIMATION_H
#define ANIMATION_H

#include "assets.h"

typedef struct {
	Asset *asset;	
	int fps;
	int frame;
	int frame_counter;
} Animation;

Animation animation_new(const char* path, int fps);
void animation_update(Animation *animation);
void animation_draw(Animation *animation, int x, int y);

#endif // ANIMATION_H
