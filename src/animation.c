#include "animation.h"
#include "assets.h"

Animation animation_new(const char *path, int fps) {

	Animation anim = {};

	anim.asset = assets_get(path);
	anim.fps = fps;
	anim.loop = false;
	anim.finished = true;

	return anim;
}

void animation_update(Animation *animation) {

	if (animation->finished) return;

	animation->frame_counter++;

	if (animation->frame_counter >= 60/animation->fps) {
		animation->frame_counter = 0;
		animation->frame++;

		if (animation->frame > animation->asset->data.sprite.atlas.width) {

			animation->frame = 0;

			if (!animation->loop) {
				animation->finished = true;
			}
		}
	}
}

void animation_play(Animation *animation) {
	animation->finished = false;
}

void animation_draw(Animation *animation, int x, int y) {
	if (animation->finished) return;
	asset_draw_tile(animation->asset, animation->frame, x, y);
}
