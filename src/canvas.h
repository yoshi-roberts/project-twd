#ifndef CANVAS_H
#define CANVAS_H

#include "../lib/raylib/src/raylib.h"
#include "../lib/raylib/src/raymath.h"

// Returns the biggest value.
#define MAX(a, b) ((a)>(b)? (a) : (b))
// Returns the smallest value.
#define MIN(a, b) ((a)<(b)? (a) : (b))

typedef struct {
	int width;
	int height;
	RenderTexture2D target;
	Rectangle source;
	Rectangle dest;
} Canvas ;

// Create and initialize a new Canvas.
Canvas canvas_init(int width, int height);
// Destroy a canvas and any allocated memory.
void canvas_destroy(Canvas *canvas);
// Update a canvas and calculate its position and scale.
void canvas_update(Canvas *canvas);
// Prepare a canvas to begin drawing to it.
void canvas_begin(Canvas *canvas);
// Stop drawing to a canvas.
// Just calls EndTextureMode().
void canvas_end();
// Render the canvas to the screen.
void canvas_draw(Canvas *canvas);

#endif // CANVAS_H
