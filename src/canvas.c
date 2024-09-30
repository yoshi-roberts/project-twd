#include "canvas.h"
#include "log.h"

Canvas canvas_init(int width, int height, int filter) {

	Canvas canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.target = LoadRenderTexture(width, height);
	canvas.source.x = 0.0f;
	canvas.source.y = 0.0f;

	SetTextureFilter(canvas.target.texture, filter);

	log_info("Initialized canvas.");

	return canvas;
}

void canvas_destroy(Canvas *canvas) {
	UnloadRenderTexture(canvas->target);
	log_info("Destroyed canvas");
}

void canvas_update(Canvas *canvas) {

	float scale = MIN(
		(float)GetScreenWidth()/canvas->width,
		(float)GetScreenHeight()/canvas->height
	);

	canvas->source.width = (float)canvas->width;
	canvas->source.height = -(float)canvas->height;

	canvas->dest.x = (GetScreenWidth() - ((float)canvas->width*scale)) * 0.5f;
	canvas->dest.y = (GetScreenHeight() - ((float)canvas->height*scale)) * 0.5f;
	canvas->dest.width = (float)canvas->width * scale;
	canvas->dest.height= (float)canvas->height * scale;
}

void canvas_begin(Canvas *canvas) {
	BeginTextureMode(canvas->target);
}

void canvas_end() {
	EndTextureMode();
}

void canvas_draw(Canvas *canvas) {

	// ClearBackground(BLACK);
	DrawTexturePro(
		canvas->target.texture,
		canvas->source,	
		canvas->dest,
		(Vector2){0, 0},
		0.0f,
		WHITE
	);
}
