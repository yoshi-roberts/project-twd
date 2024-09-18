#ifndef CANVAS_H
#define CANVAS_H

#include "../lib/raylib/src/raylib.h"
#include "../lib/raylib/src/raymath.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

typedef struct {
	int width;
	int height;
	RenderTexture2D target;
	Rectangle dest;
} Canvas ;

Canvas canvas_init(int width, int height);
void canvas_destroy(Canvas *canvas);
void canvas_update(Canvas *canvas);
void canvas_begin(Canvas *canvas);
void canvas_end(Canvas *canvas);
void canvas_draw(Canvas *canvas);

#endif // CANVAS_H
