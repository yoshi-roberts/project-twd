#ifndef ANIMATION_H
#define ANIMATION_H

#include "assets.h"
#include <stdbool.h>

typedef struct {
	Asset *asset;	
	int fps;
	bool loop;
	bool finished;
	int frame;
	int frame_counter;
} Animation;

Animation animation_new(const char* path, int fps);
void animation_update(Animation *animation);
void animation_draw(Animation *animation, int x, int y);
void animation_play(Animation *animation);

#endif // ANIMATION_H
