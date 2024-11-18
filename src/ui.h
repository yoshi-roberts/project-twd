#ifndef UI_H
#define UI_H

#include <stdbool.h>

#define UI_MAX_LABELS 32
#define UI_BLACK (Color){24, 20, 37, 255}
#define UI_DARKGRAY (Color){90, 105, 136, 255}
#define UI_GRAY (Color){139, 155, 180, 255}
#define UI_LIGHTGRAY (Color){192, 203, 220, 255}

typedef void (*UI_Button_Callback)(void *data);

typedef struct {
	char *text;
	bool button;
	UI_Button_Callback callback;
	void *data;
} UI_Element;

typedef struct {
	int x; int y;
	int w; int h;
	UI_Element labels[UI_MAX_LABELS];
	int label_count;
} UI_Panel;

UI_Panel ui_panel_new(int x, int y);
void ui_panel_draw(UI_Panel *panel);
void ui_panel_add_label(UI_Panel *panel, char *text);
void ui_panel_add_button(UI_Panel *panel, char *text, UI_Button_Callback callback, void *data);

#endif // UI_H
