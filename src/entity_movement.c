#include "../lib/raylib/src/raylib.h"
#include "dummy_entity.h"

// Function to move multiple entities based on input
void move_entities(DummyEntity entities[], int num) {
    for (int i = 0; i < num; i++) {
        if (IsKeyDown(KEY_W)) entities[i].y -= 2;
        if (IsKeyDown(KEY_A)) entities[i].x -= 2;
        if (IsKeyDown(KEY_S)) entities[i].y += 2;
        if (IsKeyDown(KEY_D)) entities[i].x += 2;
    }
}
