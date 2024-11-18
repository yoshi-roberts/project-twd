#ifndef ENEMIES_H
#define ENEMIES_H

typedef enum {
	ENEMY_SLIME,
} ENEMY_TYPE ;

// Enemy-specific components
typedef struct {
	ENEMY_TYPE type;
	int x; int y;
} Enemy;

Enemy enemy_new(ENEMY_TYPE type, int x, int y);
void enemy_update(Enemy *enemy);
void enemy_draw(Enemy *enemy);

#endif // ENEMIES_H

