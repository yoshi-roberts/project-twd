#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include "enemy.h"
#include "spawner.h"
#include "tilemap.h"
#include "assets.h"
#include "unit.h"
#include "projectile.h"

enum GameState {
	STATE_BUILD = 0,
	STATE_PLAY = 1,
	STATE_COMPLETE = 2,
	STATE_LOSE = 3,
	STATE_WIN = 4 
};

typedef struct {
	int difficulty;
	int waves;
	int scene_state;
	int first_enemy;
	int last_enemy;
	Spawner spawner;
	int projectile_count;
	Enemy **enemies;
	Unit units[TILEMAP_HEIGHT][TILEMAP_WIDTH];
	Projectile projectiles[MAX_PROJECTILES];
	int tower_hp;
	Healthbar tower_healthbar;
	Tilemap tilemap_layer1;
    Tilemap tilemap_layer2;
	Tilemap tilemap_layer3;
} Scene;

Scene scene_init(int difficulty, const char* path);
void scene_destroy(Scene *scene);
void scene_update(Scene *scene);
void scene_draw(Scene *scene);
void scene_randomize(Scene *scene);
void gen_treeline(Scene *scene);
void build_tree(Scene *scene, int anchor[], int layer);
void scene_state_set(Scene *scene, int state);
int scene_state_get(Scene *scene);

#endif
