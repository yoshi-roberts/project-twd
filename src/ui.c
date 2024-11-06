#include "ui.h"
#include "../lib/raylib/src/raylib.h"

UI_Panel ui_panel_new(int x, int y) {

	UI_Panel panel;

	panel.x = x;
	panel.y = y;
	panel.w = 0;
	panel.h = 0;
	panel.label_count = 0;

	return panel;
}

void ui_panel_add_label(UI_Panel *panel, char *text) {

	UI_Label label = {};
	label.text = text;

	panel->labels[panel->label_count] = label;
	panel->label_count++;
}

void ui_panel_draw(UI_Panel *panel) {

	DrawRectangle(panel->x - 1, panel->y - 1, panel->w + 2, panel->h + 2, BLACK);
	DrawRectangle(panel->x, panel->y, panel->w, panel->h, GRAY);

	for (int i = 0; i < panel->label_count; i++) {
	
		UI_Label *label = &panel->labels[i];

		int size = MeasureText(label->text, 10);

		if (size > panel->w) {
			panel->w = size + 4; 
		}

		int y = panel->y + (10 * i);

		if (y >= panel->y + panel->h) {
			panel->h += 10;
		}

		DrawText(label->text, panel->x + 2, panel->y + (10 * i), 10, WHITE);
	}
}
