#include <stdio.h>
#include "../lib/raylib/src/raylib.h"

int main(int argc, char** argv) {

	InitWindow(1280, 720, "Project Tower Defense");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
	
		BeginDrawing();
			ClearBackground(WHITE);
		EndDrawing();
	}

	CloseWindow();

    return 0;
}
