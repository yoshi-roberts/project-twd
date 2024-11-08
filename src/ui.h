#ifndef UI_H
#define UI_H

#include <stdbool.h>

#define UI_MAX_LABELS 32

typedef struct {
	char *text;
	bool button;
} UI_Element;

typedef struct {
	int x; int y;
	int w; int h;
	UI_Element labels[UI_MAX_LABELS];
	int label_count;
} UI_Panel;

UI_Panel ui_panel_new(int x, int y);
void ui_panel_draw(UI_Panel *panel);
void ui_panel_add_element(UI_Panel *panel, char *text, bool button);

#endif // UI_H
