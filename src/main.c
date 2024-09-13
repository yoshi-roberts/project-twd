#include "../lib/raylib/src/raylib.h"
#include "assets.h"

int main(int argc, char** argv) {

	InitWindow(1280, 720, "Project Tower Defense");
	SetTargetFPS(60);

	assets_init();

	while (!WindowShouldClose()) {
	
		BeginDrawing();
			ClearBackground(WHITE);
		EndDrawing();
	}

	assets_destory();
	CloseWindow();

    return 0;
}
