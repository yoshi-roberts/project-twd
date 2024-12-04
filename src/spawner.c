#include "spawner.h"
#include "enemy.h"
#include "game.h"
#include "scene_builder.h"

Spawner spawner_new(int interval, int x, int y) {

	Spawner spawner = {};

	spawner.interval = interval * 60;
	spawner.time = interval;

	return spawner;
}

void spawner_update(Spawner *spawner) {

	spawner->time--;

	Scene *scn = game_get_scene();
	if (spawner->time <= 0 && scn->scene_state == STATE_PLAY) {

		int type = GetRandomValue(0, 2);
		enemy_new(type);

		spawner->time = spawner->interval;
	}
}
