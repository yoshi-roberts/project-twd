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

	DrawRectangle(panel->x - 1, panel->y - 1, panel->w + 2, panel->h + 2, BLACK);
	DrawRectangle(panel->x, panel->y, panel->w, panel->h, DARKGRAY);

	for (int i = 0; i < panel->label_count; i++) {
	
		UI_Element *element = &panel->labels[i];

		int size = MeasureText(element->text, 10);

		if (size > panel->w) {
			panel->w = size + 4; 
		}

		int y = panel->y + (10 * i);

		if (y >= panel->y + panel->h) {
			panel->h += 10;
		}

		int ex = panel->x + 2;
		int ey = panel->y + (10 * i);

		bool selected = false;
		int mx = game_get_mouse_x();
		int my = game_get_mouse_y();

		if (element->button) {

			if (mx >= ex && mx <= ex + size) {
				if (my >= ey && my <= ey + 10) {

					selected = true;
				}
			}

			DrawRectangle(ex, ey, size, 10, GRAY);

			if (selected) {
				DrawText(element->text, panel->x + 2, panel->y + (10 * i), 10, WHITE);
			} else {
				DrawText(element->text, panel->x + 2, panel->y + (10 * i), 10, LIGHTGRAY);
			}
		} else {

			DrawText(element->text, panel->x + 2, panel->y + (10 * i), 10, WHITE);
		}
	}
}
