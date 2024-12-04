#ifndef SPAWNER_H
#define SPAWNER_H

typedef struct {
	int x; int y;
	int interval;
	int amount;
	int time;
} Spawner;

Spawner spawner_new(int interval, int x, int y);
void spawner_update(Spawner *spawner);
void spawner_spawn_enemy();

#endif // SPAWNER_H
