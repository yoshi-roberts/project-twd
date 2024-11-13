#include "ui.h"
#include "../lib/raylib/src/raylib.h"
#include "game.h"

UI_Panel ui_panel_new(int x, int y) {

	UI_Panel panel;

	panel.x = x;
	panel.y = y;
	panel.w = 0;
	panel.h = 0;
	panel.label_count = 0;

	return panel;
}

void ui_panel_add_element(UI_Panel *panel, char *text, bool button) {

	UI_Element label = {};
	label.text = text;
	label.button = button;

	panel->labels[panel->label_count] = label;
	panel->label_count++;
}

void ui_panel_draw(UI_Panel *panel) {

	DrawRectangle(panel->x - 1, panel->y - 1, panel->w + 2, panel->h + 2, UI_BLACK);
	DrawRectangle(panel->x, panel->y, panel->w, panel->h, UI_DARKGRAY);

	int padding = 2;

	for (int i = 0; i < panel->label_count; i++) {
	
		UI_Element *element = &panel->labels[i];

		int width = MeasureText(element->text, 10);
		int height = GetFontDefault().baseSize;

		if (width > panel->w) {
			panel->w = width + (padding * 2); 
		}

		int ex = panel->x + padding;
		int ey = panel->y + ((i * height) + padding);

		if (i != 0) {
			ey += ((padding) * i);
		}

		if (ey >= (panel->y + panel->h)) {
			panel->h = (ey - panel->y) + (height + padding);
		}


		bool selected = false;
		int mx = game_get_mouse_x();
		int my = game_get_mouse_y();

		if (element->button) {

			if (mx >= ex && mx <= ex + width) {
				if (my >= ey && my <= ey + 10) {

					selected = true;
				}
			}

			if (selected) {
				DrawRectangle(ex, ey, width, height, UI_LIGHTGRAY);
			} else {
				DrawRectangle(ex, ey, width, height, UI_GRAY);
			}
		}

		DrawText(element->text, ex, ey, height, UI_BLACK);
	}
}
