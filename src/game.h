#ifndef GAME_H
#define GAME_H

#define GAME_MAX_SCENES 128

typedef struct {
	// Scene scenes[GAME_MAX_SCENES];
	// Scene *current_scene;
	float dt;	// Delta Time.
} Game;

// Initializes the game struct.
void game_init();
// Deinitializes the game struct and frees any allocated memory.
void game_shutdown();
void game_update();
void game_draw();

#endif // GAME_H
